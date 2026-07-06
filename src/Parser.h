#pragma once
#include<string>
#include<iostream>
#include<sstream>
#include <optional>

class Parser{
    public:
        std::string command;
        std::optional<std::string> arg, value;
        void parse(const std::string &line);
        void reset();
};