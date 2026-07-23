#include "Command.h"
#include "CommandExecutor.h"
#include "Parser.h"

#include<iostream>
#include<string>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
#include <netinet/in.h>

using std::cout;
using std::cin;
using std::endl;
using std::cerr;

namespace {
constexpr int kPort = 8080;
constexpr int kBacklog = 5;
constexpr std::size_t kBufferSize = 1024;
}

int main() {
    Parser parser;
    CommandExecutor executor;

    cout << "Mini redis" << endl;
    const int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == -1){
        perror("socket");
        return 1;
    }

    const int reuse_address = 1;
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &reuse_address, sizeof(reuse_address)) == -1) {
        perror("setsockopt");
        close(server_fd);
        return 1;
    }

    cerr << "Server started..." << endl;
    sockaddr_in server_addr{};

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(kPort);

    if (bind(server_fd, reinterpret_cast<sockaddr *>(&server_addr), sizeof(server_addr)) == -1){
        perror("bind");
        close(server_fd);
        return 1;
    }

    if (listen(server_fd, kBacklog) == -1){
        perror("listen");
        close(server_fd);
        return 1;
    }
    cout << "Server listening on port " << kPort << "...\n";
    cerr << "Server listening..." << endl;
    sockaddr_in client_addr{};

    while (true) {
        socklen_t client_len = sizeof(client_addr);
        const int client_fd = accept(
            server_fd,
            reinterpret_cast<sockaddr *>(&client_addr), &client_len);
        if (client_fd == -1){
            perror("accept");
            continue;
        }

        char ip_string[INET_ADDRSTRLEN]{};
        if (inet_ntop(AF_INET, &client_addr.sin_addr, ip_string, sizeof(ip_string)) != nullptr) {
            cout << "Client connected: " << ip_string << endl;
        }
        cerr << "Client connected..." << endl;

        while (true) {
            char buffer[kBufferSize + 1]{};
            const ssize_t bytes = recv(
                client_fd,
                buffer,
                kBufferSize,
                0);
            if (bytes == 0) {
                cerr << "Client disconnected..." << endl;
                break;
            }

            if (bytes > 0) {
                buffer[bytes] = '\0';
                const Command cmd = parser.parse(buffer);
                const std::string response = executor.execute(cmd);

                if (response == "SESSION TERMINATED") {
                    break;
                }

                if (send(client_fd, response.c_str(), response.size(), 0) == -1) {
                    perror("send");
                    break;
                }

            } else {
                perror("recv");
                break;
            }
        }
        close(client_fd);
        cerr << "Client connection closed..." << endl;
    }
}
