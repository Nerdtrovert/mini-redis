#pragma once
#include "Command.h"
#include "Storage.h"
#include "sys/socket.h"

#include <iostream>
#include <optional>
#include <string>
#include <sys/socket.h>


class CommandExecutor{ 
    private:
    Storage db;

    public:
    std::string execute (const Command& cmd);
};
