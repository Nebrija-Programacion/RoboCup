#include "parsedata.h"
#include <iostream>

Command extractCommand(const std::string &receivedMsg)
{
    Command command;
    std::string msg = receivedMsg;

    command.command.clear();
    command.content.clear();

    if(msg.at(0) != '('){
        command.command.clear();
        command.content.clear();
    }else{
        msg = msg.substr(1);
        unsigned long pos = msg.find(' ');
        if(pos != std::string::npos){
            command.command = trim(msg.substr(0,pos));
            command.content = trim(msg.substr(pos));
        }else {
            pos = msg.find(')');
            if(pos != std::string::npos){
                command.command = trim(msg.substr(0,pos));
                command.content = trim(msg.substr(pos));
                return command;
            }
        }
    }

    return command;
}

std::string trim(const std::string &str, char t)
{
    std::string trimmed = str;
    while(trimmed.back() == t){
        trimmed.pop_back();
    }

    while(trimmed.front() == t){
        trimmed.erase(0,1);
    }

    return trimmed;
}
