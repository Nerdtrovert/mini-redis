#include "Parser.h"

Command Parser::parse(const std::string &line){
    std::string command;
    std::optional<std::string> arg, value;
    std::stringstream ss(line);
    ss >> command;
    std::string temp;
    if(ss>>temp) arg = temp;
    if(getline(ss >> std::ws,temp))  value = temp;
    return Command(command,arg,value);
}
