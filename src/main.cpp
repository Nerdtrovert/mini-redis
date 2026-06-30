#include "Storage.h"
#include "CLI.h"
#include<iostream>
#include<string>
#include<unordered_map>

using std::cout;
using std::cin;
using std::endl;


int main(){
    Storage db;
    CLI cli;
    while(true){
        cout<<"Mini redis (key value)" <<endl;
        cout<<"1. SET"<<endl;
        cout<<"2. GET"<<endl;
        cout<<"3. LIST"<<endl;
        cout<<"4. DEL"<<endl;
        cout<<"5. Exit"<<endl;
        cout<<"Enter choice: ";
        int ch; cin>>ch;
        switch(ch){
            case 1:{ 
                std::string key,val;
                cout<<"SET key value" <<endl;    cin>>key>>val;
                db.set(key,val);
                cout<<"OK"<<endl;
                break;
            }
            case 2:{
                std::string src_key;
                cout<<"GET ";   cin>>src_key;
                auto res = db.get(src_key);
                cout<< res.value_or("NOT FOUND")<<endl;
                break;
            }
            case 3:{
                cout<<"LIST"<<endl;
                cli.display(db.getAll());
                break;
            }
            case 4:{
                cout<<"DEL ";
                std::string del_key;
                cin>>del_key;
                db.del(del_key);
                cout<<"OK"<< endl;
                break;
            }
            case 5:{
                return 0;
            }
        }
    }
    return 0;
}