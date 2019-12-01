#ifndef PARSEDATA_H
#define PARSEDATA_H

#include <string>

struct Command {
    std::string command;
    std::string content;
};

Command extractCommand(std::string const & msg);

std::string trim(std::string const & str, char t=' ');

#endif // PARSEDATA_H
