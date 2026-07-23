#pragma once
#include<unordered_map>
#include<string>
#include<iostream>
#include<optional>
#include<fstream>
#include<sstream>

class Storage{
    private:
        std::unordered_map<std::string, std::string> internal_map;
        bool file_operation_successful = true;
    public:
    void set(const std::string &key, const std::string &value);
    std::optional<std::string> get(const std::string &key) const;
    void del(const std::string &key);
    const std::unordered_map<std::string, std::string> &getAll() const;
    void save();
    void load();
    bool file_operation_succeeded() const;
    std::size_t size() const;
    void clear();
};
