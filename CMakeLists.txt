cmake_minimum_required(VERSION 3.16)

project(mini_redis LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(mini-redis
    src/main.cpp
    src/Parser.cpp
    src/CommandExecutor.cpp
    src/Storage.cpp
)

target_include_directories(mini-redis PRIVATE src)
