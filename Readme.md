# Mini Redis (C++)

A Redis-inspired in-memory key-value store built from scratch in Modern C++ as part of my Systems Software Engineering learning roadmap.

> **Current Status:** Phase 2 – Single-Threaded TCP Server

---

## Overview

Mini Redis is a learning project focused on understanding how an in-memory database works internally rather than cloning Redis feature-for-feature.

The project is being developed incrementally to explore concepts in:

- Modern C++
- Linux System Programming
- TCP Networking
- Data Structures
- Operating Systems
- Systems Software Design

Each phase introduces one major systems concept while keeping the codebase simple and easy to understand.

---

# Features

### Storage

- In-memory key-value store
- `SET`
- `GET`
- `DEL`
- `LIST`

### Persistence

- `SAVE`
- `LOAD`
- File-based storage
- Simple serialization format

### Networking

- TCP server
- Single-threaded architecture
- Multiple commands per client connection
- Request-response communication using sockets

### Architecture

- Separate Storage layer
- Parser for command processing
- CLI utilities
- TCP transport independent of storage logic

---

# Project Structure

```text
mini-redis/
│
├── src/
│   ├── main.cpp
│   ├── Storage.h
│   ├── Storage.cpp
│   ├── Parser.h
│   ├── Parser.cpp
│   ├── CLI.h
│   └── CLI.cpp
│
├── redis.txt
└── README.md
```

---

# Supported Commands

```text
SET <key> <value>

GET <key>

DEL <key>

LIST

SAVE

LOAD

EXIT
```

---

# Technologies

- C++17
- STL
- `std::unordered_map`
- `std::optional`
- POSIX Socket API
- Linux System Calls

---

# Concepts Learned

## Modern C++

- Classes
- References
- `std::optional`
- `std::unordered_map`
- File I/O
- String Streams

## Systems Programming

- Command Parsing
- REPL Design
- Layered Architecture
- TCP Socket Programming
- Client-Server Communication
- Serialization
- Persistent Storage

---

# Development Roadmap

## ✅ Phase 0 — Storage Engine

- In-memory key-value store
- SET
- GET
- DEL
- LIST

---

## ✅ Phase 1 — CLI & Command Parser

- Menu removed
- Command parser
- REPL interface
- Input validation

---

## ✅ Phase 2 — TCP Server

- socket()
- bind()
- listen()
- accept()
- recv()
- send()
- Persistent client connection
- Request-response communication

---

## ⏳ Phase 3 — Improvements

- Better command execution architecture
- Improved parser
- Logging
- Configuration
- Benchmarking
- Better error handling

---

## ⏳ Phase 4 — Concurrency

- Multiple clients
- Multithreading
- Thread-safe storage
- Synchronization
- Performance improvements

---

# Build

Compile using g++:

```bash
g++ -std=c++17 src/*.cpp -o mini-redis
```

Run:

```bash
./mini-redis
```

---

# Why This Project?

The goal of this project is not simply to recreate Redis, but to understand the engineering decisions behind it.

Rather than building everything at once, each version introduces one systems programming concept:

- Data structures
- Parsing
- Persistence
- Networking
- Concurrency

This incremental approach mirrors how production systems evolve while providing a practical way to learn modern C++ and systems software engineering.

---

## Future Features

- Command dispatcher
- RESP (Redis Serialization Protocol)
- Thread pool
- Configurable server port
- TTL support
- Transactions
- Publish/Subscribe
- Benchmarking

---

# Author

**Prajwal Navada G P**