#ifndef PLAYERCOMMANDS_H
#define PLAYERCOMMANDS_H

#include <string>
#include "playerdata.h"

std::string connectToServerCommand(std::string const & teamName);
std::string moveCommand(float x, float y);
PlayerData  & placePlayerInPosition(PlayerData & playerData);
PlayerData  & computePlayerData(PlayerData  & playerData);

#endif // PLAYERCOMMANDS_H
