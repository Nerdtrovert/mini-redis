# Mini Redis (C++)

## Overview

### What is it?

Mini Redis is a Redis-inspired, in-memory key-value database written in modern C++. It exposes a TCP server that accepts commands from clients such as `netcat`, keeps data in memory for fast access, and supports simple file persistence through `SAVE` and `LOAD`.

I built Mini Redis to understand how in-memory databases work before exploring the Redis source code. The project focuses on the core ideas behind a small database server: hash-based storage, command parsing, socket programming, and persistence.

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
Client
  |
  v
Socket Server (main.cpp)
  |
  v
Parser
  |
  v
CommandExecutor
  |
  v
Storage ----> redis.txt
```

The socket server receives a client command and passes it to the parser. The parser creates a `Command` object, the executor chooses the operation, and storage reads or updates the in-memory map. `SAVE` and `LOAD` connect storage to `redis.txt`.

- `main.cpp`: accepts TCP connections and sends responses.
- `Parser`: splits a text request into a command, key, and optional value.
- `CommandExecutor`: validates commands and coordinates each operation.
- `Storage`: owns the in-memory key-value data and file persistence.

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

Build the server with CMake:

```bash
cmake -S . -B build
cmake --build build
```

## How to Run

Start the server from the project root:

```bash
./build/mini-redis
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
