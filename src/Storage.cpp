#include "Storage.h"

void Storage::set(const std::string &key, const std::string &value){
    internal_map[key]=value;
}

std::optional<std::string> Storage::get(const std::string &key) const {
    auto it = internal_map.find(key);
    if(it != internal_map.end()){
        return it->second;
    }
    return std::nullopt;
}

const std::unordered_map<std::string, std::string>& Storage::getAll() const{
    return internal_map;
};

void Storage::del(const std::string &key) {
    auto it = internal_map.find(key);
    if (it != internal_map.end()) {
        internal_map.erase(it);
    }
}

void Storage::save(){
    std::ofstream file("redis.txt");
    if (!file){
        file_operation_successful = false;
        return;
    }
    file_operation_successful = true;
    for (const auto &[key, value] : internal_map){
        file << key << "," << value << "\n";
    }
    if (!file) {
        file_operation_successful = false;
    }
}

void Storage::load(){
    internal_map.clear();
    std::ifstream file("redis.txt");
    if (!file){
        file_operation_successful = false;
        return;
    }

    file_operation_successful = true;
    std::string line;
    while(getline(file, line)){
        std::stringstream ss(line);
        std::string get_key, get_val;
        getline(ss,get_key,',');
        getline(ss,get_val);
        set(get_key,get_val);
    }
}

size_t Storage::size() const{
    return internal_map.size();
}

bool Storage::file_operation_succeeded() const {
    return file_operation_successful;
}

void Storage::clear(){
    internal_map.clear();
}
