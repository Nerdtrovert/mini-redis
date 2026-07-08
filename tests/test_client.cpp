#include <iostream>
#include <string>
#include <vector>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>

struct Test
{
    std::string command;
    std::string expected;
    bool is_list_command = false;
};

// Helper function to check if all expected map entries exist in the LIST output (ignores order)
bool verify_unordered_list(const std::string &received, const std::vector<std::string> &expected_pairs)
{
    for (const auto &pair : expected_pairs)
    {
        if (received.find(pair) == std::string::npos)
        {
            return false;
        }
    }
    return true;
}

void run_test(int sock, const Test &t, bool &overall_pass)
{
    // Send command
    if (send(sock, t.command.c_str(), t.command.size(), 0) == -1)
    {
        std::cout << "Command  : " << t.command << "\nFAIL\nExpected : " << t.expected << "\nReceived : SEND FAILED\n\n";
        overall_pass = false;
        return;
    }

    // Receive response
    char buffer[2048];
    memset(buffer, 0, sizeof(buffer));
    int bytes = recv(sock, buffer, sizeof(buffer) - 1, 0);

    if (bytes <= 0)
    {
        std::cout << "Command  : " << t.command << "\nFAIL\nExpected : " << t.expected << "\nReceived : DISCONNECTED\n\n";
        overall_pass = false;
        return;
    }

    buffer[bytes] = '\0';
    std::string received(buffer);

    bool is_match = false;
    if (t.is_list_command)
    {
        // Unordered map verification safely avoids order mismatches
        std::vector<std::string> expected_pairs = {"city : Bengaluru", "name : Prajwal"};
        is_match = verify_unordered_list(received, expected_pairs);
    }
    else
    {
        is_match = (received == t.expected);
    }

    // Output formatted results without cascading drops
    if (is_match)
    {
        std::cout << "Command  : " << t.command << "\nExpected : " << t.expected << "\nReceived : " << (t.is_list_command ? "[Valid Unordered Map Data]" : received) << "\nPASS\n\n";
    }
    else
    {
        std::cout << "Command  : " << t.command << "\nFAIL\nExpected : " << t.expected << "\nReceived : " << received << "\n\n";
        overall_pass = false;
    }
}

int main()
{
    // Setup socket connection
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(8080);
    inet_pton(AF_INET, "127.0.0.1", &addr.sin_addr);

    if (connect(sock, reinterpret_cast<sockaddr *>(&addr), sizeof(addr)) == -1)
    {
        std::cerr << "Failed to connect to server on port 8080.\n";
        return 1;
    }

    // Configured suite matching updated behaviors
    std::vector<Test> suite = {
        {"SET name Prajwal", "OK"},
        {"GET name", "OK Prajwal"},
        {"SET city Bengaluru", "OK"},
        {"GET city", "OK Bengaluru"},
        {"COUNT", "OK 2"}, // Updated format
        {"EXISTS name", "OK Exists"},
        {"EXISTS age", "Does not Exist."},
        {"LIST", "city : Bengaluru\nname : Prajwal\n\n", true}, // Handled safely via boolean flag
        {"SAVE", "SAVED"},
        {"CLEAR", "OK Cleared"},
        {"COUNT", "OK 0"}, // Updated format
        {"LOAD", "LOADED"},
        {"GET name", "OK Prajwal"},
        {"DEL name", "OK"},
        {"GET name", "ERROR Missing key"},
        {"INVALID", "ERROR Unknown command: INVALID"},
        {"HELP", "Available commands:\nSET <key> <value>\nGET <key>\nDEL <key>\nEXISTS <key>\nLIST\nSAVE\nLOAD\nCLEAR\nCOUNT\nEXIT"}, // Explicit line break / whitespace verification
        {"EXIT", "SESSION TERMINATED"}                                                                                                // Catches the stream transmission cleanly before breakdown
    };

    bool overall_pass = true;

    for (const auto &t : suite)
    {
        run_test(sock, t, overall_pass);
    }

    close(sock);

    std::cout << "----------------------------------------\n";
    std::cout << "FINAL TEST SUITE STATUS: " << (overall_pass ? "PASSED" : "FAILED") << "\n";
    std::cout << "----------------------------------------\n";

    return overall_pass ? 0 : 1;
}