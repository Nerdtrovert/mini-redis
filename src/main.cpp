#include "Storage.h"
#include "CLI.h"
#include "Parser.h"
#include<iostream>
#include<string>
#include<optional>

using std::cout;
using std::cin;
using std::endl;

int main(){
    Storage db;
    CLI cli;
    Parser parser;
    cout << "Mini redis" << endl;
    while(true){
        cout<<"\n>> ";
        std::string line;
        getline(cin,line);
        parser.parse(line);
        if(parser.command == "SET"){
            if (parser.arg && parser.value){
                db.set(*parser.arg, *parser.value);
            }else{
                cout<<"INVALID COMMAND. \n \n Usage: \n SET <key> <value>"<<endl;
            }
        }else if(parser.command == "GET"){
            if(parser.arg) {
                auto it=db.get(*parser.arg); cout << it.value_or("NOT FOUND.")<<endl;
            }else{
                cout<<"INVALID COMMAND. \n \n Usage: \n GET <key>"<<endl;
            }
        }else if(parser.command == "LIST"){
            cli.display(db.getAll());
        }
        else if(parser.command == "DEL"){
            if(parser.arg) db.del(*parser.arg);
            else
            {
                cout << "INVALID COMMAND. \n \n Usage: \n DEL <key>" << endl;
            }
        }else if(parser.command=="LOAD"){ 
            db.load();
        }
        else if (parser.command == "SAVE"){
            db.save();
        }
        else if(parser.command == "EXIT") return 0;
        else cout<<"INVALID COMMAND"<<endl; 
    }
    return 0;
}