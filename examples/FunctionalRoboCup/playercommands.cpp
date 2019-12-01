#include <sstream>
#include <array>
#include "playercommands.h"

std::string connectToServerCommand(const std::string &teamName)
{
    return "(init " + teamName + " (version 15))";
}

std::string moveCommand(float x, float y)
{
    std::stringstream ss;
    ss << "(move " << x << " " << y << ")";
    return ss.str();
}

PlayerData & computePlayerData(PlayerData &playerData)
{
    if(playerData.status == "before_kick_off"){
        playerData.toSend = placePlayerInPosition(playerData).toSend;
    }

    return playerData;
}

PlayerData & placePlayerInPosition(PlayerData &playerData)
{
    struct Position{
        float x;
        float y;
    };

    std::array<Position, 11> pos{
        Position{-45,0},
        Position{-30,10},
        Position{-30,-10},
        Position{-30,20},
        Position{-30,-20},
        Position{-5,10},
        Position{-5,-10},
        Position{-5,20},
        Position{-5,-20},
        Position{-1,-1},
        Position{-1,1}
    };

    playerData.toSend = moveCommand(
                pos.at(playerData.number -1).x,
                pos.at(playerData.number -1).y
                );


    return playerData;
}
