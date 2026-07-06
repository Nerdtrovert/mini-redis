#include "Parser.h"

void Parser::parse(const std::string &line){
        reset();
        std::stringstream ss(line);
        ss >> command;
        std::string temp;
        if(ss>>temp) arg = temp;
        if(getline(ss >> std::ws,temp))  value = temp;
}

void Parser::reset(){
    command = "";
    arg = value = std::nullopt;
}