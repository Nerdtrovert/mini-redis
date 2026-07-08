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

void Storage::save(){
    std::ofstream file("redis.txt");
    if (!file){
        file_load=false;
        return;
    }
    std::string line;
    for (const auto &[key, value] : internal_map){
        file << key << "," << value << "\n";
    }
    file.close();
}

void Storage::load(){
    internal_map.clear();
    std::ifstream file("redis.txt");
    if (!file){
        file_load=false;
    }
    std::string line;
    while(getline(file, line)){
        std::stringstream ss(line);
        std::string get_key, get_val;
        getline(ss,get_key,',');
        getline(ss,get_val);
        set(get_key,get_val);
    }
    file.close();
}

size_t Storage::size() const{
    return internal_map.size();
}

bool Storage::load_status(){
    return file_load;
}