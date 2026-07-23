#pragma once
#include<string>
#include<iostream>
#include<sstream>
#include <optional>
#include "Command.h"

class Parser{
    public:
        Command parse(const std::string &line) const;
};
