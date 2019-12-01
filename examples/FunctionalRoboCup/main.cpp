#include <iostream>
#include <map>
#include <memory>

#include "playercommands.h"
#include "udpfunctions.h"
#include "parsedata.h"
#include "playerdata.h"


/******* parse data functions ***********************************************/

/** Examples
 * init command
 * l 9 before_kick_off)
 * r 11 before_kick_off)
 */
auto initCommand  = [](std::string const & msg, PlayerData & playerData) -> PlayerData {
    std::cout << msg << "--" << std::endl;
    playerData.side = msg.at(0);
    playerData.number = std::stoi(msg.substr(2,2));

    if(playerData.number < 10){
        playerData.status = msg.substr(4, msg.length() - 5 - 1);
    }else{
        playerData.status = msg.substr(5, msg.length() - 6 - 1);
    }

    return playerData;
};

/******* end parse data functions ***********************************************/


void print(PlayerData const & playerData){
    std::cout << "Team Name:\t" << playerData.teamName << "\n";
    std::cout << "Number:\t" << playerData.number << "\n";
    std::cout << "Position:\t" << playerData.x << ", " << playerData.y << "\n";
    std::cout << "Side:\t" << playerData.side << "\n";
    std::cout << "Game Status:\t" << playerData.status << "\n";
}

int main(int argc, char *argv[])
{
    /*** config */
    const std::string host = "127.0.0.1";
    const unsigned short port = 6000;
    const std::string teamName = "AlberTeam";

    /*** functions map */
    std::map<std::string, std::function<PlayerData (std::string const &, PlayerData &)> > functionsMap
    {
        {"init", initCommand}
    };


    /*** required variables */
    std::string command{""};
    std::string receivedData{""};
    QNetworkDatagram datagram;
    PlayerData playerData;
    playerData.teamName = teamName;

    // Connect to socket
    std::unique_ptr<QUdpSocket> socket = createSocket(host, port);
    // connect to robocup server command
    command = connectToServerCommand(teamName);
    // connect so robocup server
    sendData(command, socket, host, port);

    // main loop
    while(true){
        if(socket->hasPendingDatagrams()){
            // receive data from robocup server
            datagram = receiveData(socket);
            std::string receivedString = datagram.data().toStdString();
            // extract command
            Command command = extractCommand(receivedString);
            // parse command
            if(functionsMap.find(command.command) != functionsMap.end()){
                playerData = functionsMap[command.command](command.content, playerData);
            }

            // compute playerData
            playerData = computePlayerData(playerData);

            // send commands to robocup server
            sendData(playerData,socket,datagram);

            // clear command to send
            playerData.toSend.clear();
        }
    }

}
