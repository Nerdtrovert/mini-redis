#include "Storage.h"
#include "CLI.h"
#include "Parser.h"
#include<iostream>
#include<string>
#include<optional>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
#include <netinet/in.h>

using std::cout;
using std::cin;
using std::endl;
using std::cerr;

int main(){
    Storage db;
    CLI cli;
    Parser parser;
    std::string invalid_reply = "INVALID COMMAND";
    std::string success_status = "OK";

    cout << "Mini redis" << endl;
    int server_fd = socket(AF_INET, SOCK_STREAM, 0); 
    if (server_fd == -1){
        cout << "Socket failed." << endl;
        return 1;
    }
    cerr<<"Server started..."<<endl;
    sockaddr_in server_addr{};

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(8080);

    if (bind(server_fd, reinterpret_cast<sockaddr *>(&server_addr), sizeof(server_addr)) == -1){
        std::cerr << "Bind failed\n";
        return 1;
    }

    if (listen(server_fd, 5) == -1){
        cerr << "Listen failed" << endl;
        return 1;
    }
    cout << "Server listening on port 8080...\n";
    cerr<<"Server listening..."<<endl;
    sockaddr_in client_addr{};
    socklen_t client_len = sizeof(client_addr);

    while(true){
        int client_fd = accept(
            server_fd,
            reinterpret_cast<sockaddr *>(&client_addr), &client_len);
        if (client_fd == -1){
            cerr << "Accept failed\n";
            return 1;
        }
        else{
            char ip_string[INET_ADDRSTRLEN];
            inet_ntop(
                AF_INET,
                &(client_addr.sin_addr),
                ip_string,
                sizeof(ip_string));
            std::string print_address(ip_string);
            cout << "Client connected: " << print_address << endl;
            cerr<<"Client connected..."<<endl;
        }
        while (true){
            char buffer[1025];
            int bytes = recv(
                client_fd,
                buffer,
                sizeof(buffer),
                0);
            if (bytes==0){
                cerr << "Client disconnected..." << endl;
                break;
            }
            if (bytes > 0)
            {
                buffer[bytes] = '\0';
                std::string line(buffer);

                parser.parse(line);
                if (parser.command == "SET")
                {
                    if (parser.arg && parser.value){
                        db.set(*parser.arg, *parser.value);
                        send(
                            client_fd, success_status.c_str(),success_status.size(), 0);
                    }
                    else
                    {
                        send(
                            client_fd, invalid_reply.c_str(), invalid_reply.size(), 0);
                    }
                }
                else if (parser.command == "GET")
                {
                    if (parser.arg)
                    {
                        std::string reply = db.get(*parser.arg).value_or("NOT FOUND.");
                        send(
                            client_fd,
                            reply.c_str(),
                            reply.size(),
                            0);
                    }
                    else
                    {
                        send(
                            client_fd, invalid_reply.c_str(), invalid_reply.size(), 0);
                    }
                }
                else if (parser.command == "LIST")
                {
                    cli.display(db.getAll(), client_fd);
                }
                else if (parser.command == "DEL")
                {
                    if (parser.arg){
                        db.del(*parser.arg);
                        send(
                            client_fd, success_status.c_str(), success_status.size(), 0);
                        }else{
                        send(
                            client_fd, invalid_reply.c_str(), invalid_reply.size(), 0);
                }
            }else if(parser.command=="LOAD"){ 
                std::string loaded = "LOADED";
                send(
                    client_fd, loaded.c_str(), loaded.size(), 0);
                db.load();
            }
            else if (parser.command == "SAVE"){
                std::string saved = "SAVED";
                send(
                    client_fd, saved.c_str(), saved.size(), 0);
                db.save();
            }
            else if(parser.command == "EXIT") break;
            else
                send(
                    client_fd, invalid_reply.c_str(), invalid_reply.size(), 0);
        }else{
            send(
                client_fd, invalid_reply.c_str(), invalid_reply.size(), 0);
        }
        }
        close(client_fd); cerr<<"Client disconnected..."<<endl;
    }cerr<<"Server closed..."<<endl;
    close(server_fd);
    return 0;
}