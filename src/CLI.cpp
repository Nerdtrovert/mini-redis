#include "CLI.h"

void CLI::display(const std::unordered_map<std::string, std::string> &display_map, int client_fd){
    std::string response_buffer;

    if (display_map.empty()){
        response_buffer = "No keys found.\n";
    }
    else{
        for (const auto &pair : display_map){
            response_buffer += pair.first + " : " + pair.second + "\n";
        }
        response_buffer += "\n";
    }
    send(
        client_fd,
        response_buffer.c_str(),
        response_buffer.size(),
        0
    );
}