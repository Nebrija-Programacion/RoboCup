#include "player.h"
#include <QNetworkDatagram>
#include <string>
#include <iostream>

Player::Player(std::string const & teamName, QObject *parent) :
    QObject(parent),
    receivedData{""},
    dataToSend{""}
{


    /** Lambda Functions definitions ************************************************/
    initFunction  = [&](std::string const & msg) -> void {
        std::cout << msg << std::endl;
        playerData.side = msg.at(5);
        playerData.number = std::stoi(msg.substr(7,2));

        if(playerData.number < 10)
            playerData.status = msg.substr(9, msg.length() - 1 - 9);
        else
            playerData.status = msg.substr(10, msg.length() - 1 - 10);

        printPlayerData();
    };
    /** End Lambda Functions definitions ************************************************/


    /** Insert lambda functions in map ***********************************************/
    functionsMap["init"] = initFunction;

    /** End Insert lambda functions in map *******************************************/


    /* DO NOT TOUCH THIS ********************************************************************/
    udpSocket = new QUdpSocket(this);
    udpSocket->bind(QHostAddress::LocalHost, 6000);
    connect(udpSocket, SIGNAL(readyRead()),
            this, SLOT(readPendingDatagrams()));
    std::string init = "(init " + teamName + " (version 15))";
    udpSocket->writeDatagram(QByteArray().fromStdString(init), QHostAddress::LocalHost, 6000);
    playerData.teamName = teamName;
    playerData.positioned = false;
    /* END DO NOT TOUCH THIS ********************************************************************/
}

void Player::processMsg(const std::string &msg)
{

    if(msg.at(0) != '(') return;

    std::string submsg = msg.substr(1);
    std::string command = extractCommand(submsg);
    if(functionsMap.find(command) != functionsMap.end()){
        functionsMap[command](submsg);
    }
}

std::string Player::extractCommand(const std::string &msg)
{
    unsigned long pos = msg.find(' ');
    if(pos != std::string::npos){
        return msg.substr(0,pos);
    }

    pos = msg.find(')');
    if(pos != std::string::npos){
        return msg.substr(0,pos);
    }

    return "error";
}

void Player::readPendingDatagrams()
{
    while (udpSocket->hasPendingDatagrams()) {
        QNetworkDatagram datagram = udpSocket->receiveDatagram();
        if(!datagram.data().isEmpty()){
            processDatagram(datagram);
            computePlayerData();
            if(!dataToSend.empty()){
                std::cout << dataToSend << std::endl;
                udpSocket->writeDatagram(datagram.makeReply(QString().fromStdString(dataToSend).toUtf8()));
                dataToSend.clear();
            }
        }
    }
}

void Player::processDatagram(QNetworkDatagram datagram)
{
    receivedData = datagram.data();
    processMsg(receivedData.toStdString());
}

void Player::printPlayerData() const
{

    std::cout << "side: "<< playerData.side << "\n";
    std::cout << "number: "<< playerData.number << "\n";
    std::cout << "status: "<< playerData.status << std::endl;
}

void Player::computePlayerData()
{
    if(playerData.status == "before_kick_off" && !playerData.positioned){
        playerData.positioned = true;
        switch(playerData.number){
        case 2:
            dataToSend += "(move -1 -1)";
            playerData.x = 0;
            playerData.y = 0;
            break;
        case 3:
            dataToSend += "(move -10 10)";
            playerData.x = 10;
            playerData.y = 10;
            break;
        default:
            dataToSend += "(move -20 10)";
            playerData.x = 20;
            playerData.y = 10;
       }
    }
}
