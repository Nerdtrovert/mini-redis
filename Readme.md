**Mini Redis (C++)**

A Redis-inspired key-value store built from scratch in Modern C++ as part of my Systems Software Engineering learning roadmap.

Current Status: Phase 0 – CLI Key-Value Store

**Overview**

This project is not intended to be a feature-complete Redis clone. Instead, it is a step-by-step implementation to understand the core ideas behind in-memory databases, networking, operating systems, and systems software.

The project will gradually evolve from a simple command-line application into a TCP-based server supporting multiple clients, persistence, and concurrency.

Current Features

* In-memory key-value storage
* SET command
* GET command
* DEL command
* LIST command
* Built using std::unordered_map
* Encapsulated storage through a dedicated Storage class
* Uses std::optional to safely represent missing keys
* Separation between the storage layer and presentation (CLI)

Project Structure

mini-redis/
│
├── src/
│   ├── main.cpp
│   ├── Storage.h
│   ├── Storage.cpp
|   ├── CLI.h
│   └── CLI.cpp
| 
└── README.md

Technologies

* C++17
* STL
* std::unordered_map
* std::optional

Learning Goals

This project is designed to build practical understanding of:

* Modern C++
* Data structures
* API design
* Object-oriented design
* Memory management
* Linux development workflow
* Networking
* TCP sockets
* Distributed systems
* Systems software engineering

Roadmap

✅ Phase 0 – CLI Key-Value Store

* SET
* GET
* DEL
* LIST

⏳ Phase 1 – Command Parser

* Parse commands like:
    * SET key value
    * GET key
    * DEL key
    * LIST
* Remove menu-driven interface

⏳ Phase 2 – TCP Server

* socket()
* bind()
* listen()
* accept()
* recv()
* send()
* Single client support

⏳ Phase 3 – Persistence & Improvements

* Save and load data
* Logging
* Better command parsing
* Error handling
* Benchmarking

⏳ Phase 4 – Concurrency

* Multi-client support
* Thread-safe storage
* Synchronization
* Performance improvements

Build

Compile using g++:

g++ -std=c++17 src/main.cpp src/Storage.cpp -o mini-redis

Run:

./mini-redis

Why This Project?

The objective is not just to recreate Redis, but to understand why it is designed the way it is.

Each phase introduces one new systems concept at a time, allowing the project to grow naturally while building a strong foundation in systems programming.

⸻

Author: Prajwal Navada G P