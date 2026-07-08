#pragma once
#include <iostream>
#include <unordered_map>
#include <string>
#include<sys/socket.h>

class CLI{
    public:
    void display(const std::unordered_map<std::string, std::string> &display_map, int client_fd);
};