# Mini Redis (C++)

## Overview

### What is it?

Mini Redis is a Redis-inspired, in-memory key-value database written in modern C++. Designed as a substantial systems-programming project, it exposes a TCP server that accepts commands from standard clients such as `netcat` and maintains data in memory for fast access. The project implements a focused command set for creating, reading, deleting, listing, and managing keys, alongside simple file-based persistence through `SAVE` and `LOAD` operations. Its codebase is deliberately separated into parsing, command-execution, storage, and networking layers, making the flow from a client request to a database response easy to follow and extend. Rather than reproducing Redis feature-for-feature, Mini Redis concentrates on the core engineering ideas that make an in-memory database possible: efficient hash-based storage, protocol handling, serialization, socket programming, and persistent client connections. I built it to move beyond isolated C++ exercises and develop practical experience designing, implementing, and evolving a complete networked systems application from the ground up.

## Features

- In-memory key-value storage backed by `std::unordered_map`
- Commands for creating, reading, deleting, listing, counting, and clearing keys
- Simple file persistence with `SAVE` and `LOAD` using `redis.txt`
- TCP server on port `8080`
- Persistent client sessions that accept multiple commands per connection
- Helpful responses for invalid or unknown commands

### Supported commands

```text
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

## Architecture

```text
TCP client (nc / telnet)
          |
          v
  TCP server (main.cpp)
          |
          v
      Parser
          |
          v
  CommandExecutor
       |       |
       v       v
   Storage   redis.txt
  (memory)  (SAVE/LOAD)
```

The TCP layer receives a command, the parser converts it into a command object, and the executor applies it to the storage layer or persistence file.

## Tech Stack

- C++17
- C++ Standard Library (`std::unordered_map`, `std::optional`, file streams, string streams)
- POSIX socket APIs (`socket`, `bind`, `listen`, `accept`, `recv`, `send`)
- Linux/macOS-compatible command-line tools such as `nc`

## Project Structure

```text
mini-redis/
├── src/
│   ├── main.cpp                # TCP server and client connection loop
│   ├── Command.h               # Command data model
│   ├── Parser.h / Parser.cpp   # Text command parsing
│   ├── CommandExecutor.h/.cpp  # Command dispatch and responses
│   └── Storage.h / Storage.cpp # In-memory store and persistence
├── tests/
│   └── test_client.cpp         # Client test scaffold
├── redis.txt                   # Created/used by SAVE and LOAD
└── Readme.md
```

## How to Build

Use a C++17-compatible compiler:

```bash
g++ -std=c++17 src/*.cpp -o mini-redis
```

## How to Run

Start the server from the project root:

```bash
./mini-redis
```

The server listens on `localhost:8080`. In another terminal, connect with netcat:

```bash
nc localhost 8080
```

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

For a quick non-interactive check:

```bash
printf "SET foo bar\nGET foo\nEXIT\n" | nc localhost 8080
```

## Future Improvements

- Add unit and integration tests
- Use the Redis Serialization Protocol (RESP)
- Support configurable ports and persistence paths
- Improve validation and error handling
- Add concurrency, thread-safe storage, and a thread pool
- Add TTL expiration, transactions, and publish/subscribe
- Add logging, benchmarking, and configuration support

## Learning Outcomes

- Designing a small layered C++ application
- Using hash maps and `std::optional` for in-memory storage
- Parsing command-line-style input
- Reading and writing a simple serialized file format
- Building a TCP server with POSIX sockets
- Managing a request-response protocol and persistent client connections
- Incrementally evolving a systems project from storage to networking

## Author

Prajwal Navada G P
