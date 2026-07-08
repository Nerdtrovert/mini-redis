#include "CommandExecutor.h"

std::string CommandExecutor::execute(const Command& cmd){
    if (cmd.command == "SET"){
        if (cmd.arg && cmd.value){
            db.set(*cmd.arg, *cmd.value);
            return "OK";
        }
        else{
            return "ERROR Usage: SET <key> <value>";
        }
    }
    else if (cmd.command == "GET"){
        if (cmd.arg){
            auto reply = db.get(*cmd.arg);
            if(!reply) return "ERROR Missing key";
            return "OK " + db.get(*cmd.arg).value_or(" ");
        }
        else{
            return "ERROR Usage: GET <key>";
        }
    }
    else if(cmd.command == "EXISTS"){
        if (cmd.arg)
        {
            std::string reply = db.get(*cmd.arg).value_or("NOT FOUND.");
            if (reply == "NOT FOUND")
                return "Does not Exist.";
            return "OK Exists";
        }
        else{
            return "ERROR Usage: EXSISTS <key>";
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
            return "OK";
        }
        else{
            return "ERROR Key not found";
        }
    }
    else if (cmd.command == "LOAD"){
        db.load();
        if(!db.load_status()) return "ERROR File not found";
        return "LOADED";
    }
    else if (cmd.command == "SAVE"){
        db.save();
        if (!db.load_status())
            return "ERROR File not found";
        return "SAVED";
    }
    else if (cmd.command == "COUNT"){
        size_t count = db.size();
        return "OK "+std::to_string(count);
    }
    else if(cmd.command == "HELP"){
        std::string cmds="Available commands:\nSET <key> <value>\nGET <key>\nDEL <key>\nEXISTS <key>\nLIST\nSAVE\nLOAD\nCLEAR\nCOUNT\nEXIT";
        return cmds;
    }
    else if (cmd.command == "EXIT"){
        return "SESSION TERMINATED";
    }
    else if(cmd.command == "CLEAR"){
        db.clear();
        return "OK Cleared";
    }

    else return "ERROR Unknown command: "+ cmd.command;
}