#include "CommandExecutor.h"

std::string CommandExecutor::execute(const Command& cmd){
    if (cmd.command == "SET"){
        if (cmd.arg && cmd.value){
            db.set(*cmd.arg, *cmd.value);
            return success;
        }
        else{
            return invalid_format;
        }
    }
    else if (cmd.command == "GET"){
        if (cmd.arg){
            std::string reply = db.get(*cmd.arg).value_or("NOT FOUND.");
            return reply;
        }
        else{
            return invalid_format;
        }
    }
    else if (cmd.command == "LIST"){
        std::string response_buffer;
        if (db.size()==0){
            return "EMPTY. NO VALUES FOUND";
        }
        else
        {
            for (const auto &pair : db.getAll()){
                response_buffer += pair.first + " : " + pair.second + "\n";
            }
            response_buffer += "\n";
            return response_buffer;
        }
    }
    else if (cmd.command == "DEL")
    {
        if (cmd.arg){
            db.del(*cmd.arg);
            return success;
        }
        else{
            return invalid_format;
        }
    }
    else if (cmd.command == "LOAD"){
        db.load();
        if(!db.load_status()) return "FILE NOT FOUND...";
        return "LOADED";
    }
    else if (cmd.command == "SAVE"){
        db.save();
        if (!db.load_status()) return "FILE NOT FOUND...";
        return "SAVED";
    }
    else if (cmd.command == "EXIT"){
        return "SESSION TERMINATED"; 
    }
    else
        return "INVALID COMMAND";
}