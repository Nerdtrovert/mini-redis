#include "Storage.h"

void Storage::set(const std::string &key, const std::string &value){
    internal_map[key]=value;
}

std::optional<std::string> Storage::get(const std::string &key){
    auto it = internal_map.find(key);
    if(it != internal_map.end()){
        return it->second;
    }
    return std::nullopt;
}

const std::unordered_map<std::string, std::string>& Storage::getAll() const{
    return internal_map;
};


void Storage::del(const std::string &key){
    auto it = internal_map.find(key);
    if(it != internal_map.end())
        internal_map.erase(it);
}