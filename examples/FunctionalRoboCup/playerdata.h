#ifndef PLAYERDATA_H
#define PLAYERDATA_H

#include <string>

struct PlayerData {
    std::string teamName;
    char side;
    std::string status;
    int number;
    float x;
    float y;
    std::string toSend;
};

#endif // PLAYERDATA_H
