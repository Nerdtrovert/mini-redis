#pragma once
#include<unordered_map>
#include<string>
#include<iostream>
#include<optional>

class Storage{
    private:
        std::unordered_map<std::string, std::string> internal_map;
    public:
        std::string key;
        std::string value;

    void set(const std::string &key, const std::string &value);
    std::optional<std::string> get(const std::string &key);
    void del(const std::string &key);
    const std::unordered_map<std::string, std::string> &getAll() const;
};