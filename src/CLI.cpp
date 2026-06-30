#include "CLI.h"

void CLI::display(const std::unordered_map<std::string, std::string> &display_map){
    if (display_map.empty()){
        std::cout << "No keys found." << std::endl;
        return;
    }
    for (const auto &pair : display_map)
        std::cout << pair.first << " : " << pair.second << std::endl;
    std::cout << std::endl;
}