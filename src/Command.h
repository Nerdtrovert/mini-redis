#pragma once
#include<string>
#include<optional>

class Command{
    public: 
        std::string command;
        std::optional<std::string> arg, value;
    Command(std::string command, std::optional<std::string> arg, std::optional<std::string> value) 
    : command(command) , arg(arg) , value(value) {}
};
