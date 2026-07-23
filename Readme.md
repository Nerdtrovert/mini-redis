# Mini Redis (C++)

## Overview

Mini Redis is a Redis-inspired, in-memory key-value database written in modern C++. It runs as a TCP server, accepts commands from clients over a network socket, stores data in memory for fast access, and supports simple file persistence using `SAVE` and `LOAD`.

This project was built to understand how an in-memory database works before exploring the Redis source code. The focus is on the core building blocks of a database server: socket programming, command parsing, hash-based storage, request processing, and persistence.

---

## Features

- In-memory key-value storage using `std::unordered_map`
- TCP server that accepts client connections on port **8080**
- Persistent client sessions supporting multiple commands per connection
- File persistence using `SAVE` and `LOAD` with `redis.txt`
- Graceful handling of invalid or unknown commands
- Simple, modular architecture separating networking, parsing, execution, and storage

---

## Supported Commands

```
SET <key> <value>
GET <key>
DEL <key>
EXISTS <key>
LIST
COUNT
CLEAR
SAVE
LOAD
HELP
EXIT
```

---

## Architecture

```
                Client (netcat)
                      │
                      ▼
                TCP Socket Server
                 (main.cpp)
                      │
                      ▼
                 Parser.cpp
                      │
                      ▼
              Command Structure
                      │
                      ▼
           CommandExecutor.cpp
                      │
          ┌───────────┴───────────┐
          ▼                       ▼
     Storage.cpp            Response Builder
          │
          ▼
   std::unordered_map
          │
          ▼
      redis.txt
```

The server accepts a client connection, receives a text command, and passes it to the parser. The parser converts the request into a `Command` object, which is processed by the command executor. The executor performs operations on the in-memory storage and generates a response. `SAVE` and `LOAD` synchronize the database with `redis.txt`.

---

## Tech Stack

### Language

- C++17

### Platform

- POSIX (Linux/macOS)

### Core Libraries

- `std::unordered_map`
- `std::optional`
- File Streams
- String Streams

### Core APIs

- `socket()`
- `bind()`
- `listen()`
- `accept()`
- `recv()`
- `send()`
- `close()`

### Build

- CMake
- GCC / Clang

---

## Project Structure

```
mini-redis/
├── src/
│   ├── main.cpp
│   ├── Command.h
│   ├── Parser.h
│   ├── Parser.cpp
│   ├── CommandExecutor.h
│   ├── CommandExecutor.cpp
│   ├── Storage.h
│   └── Storage.cpp
│
├── tests/
│   └── test_client.cpp
│
├── redis.txt
├── CMakeLists.txt
└── README.md
```

---

## How to Build

From the project root:

```bash
cmake -S . -B build
cmake --build build
```

---

## How to Run

Start the server:

```bash
./build/mini-redis
```

The server listens on **localhost:8080**.

Connect from another terminal:

```bash
nc localhost 8080
```

---

## Example Usage

```text
SET language cpp
OK

GET language
OK cpp

COUNT
OK 1

LIST
language : cpp

SAVE
SAVED

EXIT
```

Or test non-interactively:

```bash
printf "SET foo bar\nGET foo\nEXIT\n" | nc localhost 8080
```

---

## Concepts Practiced

- TCP socket programming
- Client-server architecture
- Request-response protocol design
- Command parsing
- Hash-based in-memory storage
- File persistence
- Layered software architecture
- Modular C++ project organization

---

## Future Improvements

- Support the Redis Serialization Protocol (RESP)
- Add configurable ports and persistence paths
- Improve command validation and error handling
- Add unit and integration tests
- Support concurrent clients with thread-safe storage
- Implement a thread pool
- Add TTL expiration for keys
- Support transactions
- Add publish/subscribe messaging
- Add logging, benchmarking, and configuration support

---

## Learning Outcomes

- How an in-memory database stores and retrieves data efficiently
- How TCP servers accept and manage client connections
- How socket APIs (`socket`, `bind`, `listen`, `accept`, `recv`, `send`) work together
- How command parsing and execution are separated using a layered architecture
- How simple persistence can be implemented using file serialization
- How modular C++ design improves maintainability and extensibility
- How networking and storage components interact to build a small database server

---

## Author

**Prajwal Navada G P**
