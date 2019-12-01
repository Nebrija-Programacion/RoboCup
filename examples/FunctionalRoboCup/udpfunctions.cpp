#include "udpfunctions.h"
#include <iostream>


std::unique_ptr<QUdpSocket> createSocket(const std::string &hostAddres, unsigned short port)
{
    std::unique_ptr<QUdpSocket> udpSocket(new QUdpSocket());
    udpSocket->bind(QHostAddress(QString().fromStdString(hostAddres)), port);
    return udpSocket;
}

QNetworkDatagram receiveData(const std::unique_ptr<QUdpSocket> &udpSocket)
{
    if (udpSocket->hasPendingDatagrams()) {
        QNetworkDatagram datagram = udpSocket->receiveDatagram();
        return datagram;
    }

    throw new std::string("No data available to read");
}

void sendData(const PlayerData &playerData, const std::unique_ptr<QUdpSocket> & updSocket, QNetworkDatagram const & datagram)
{
    updSocket->writeDatagram(datagram.makeReply(QByteArray().fromStdString(playerData.toSend)));
    std::cout << playerData.toSend << std::endl;
}

void sendData(const std::string &dataToSend, std::unique_ptr<QUdpSocket> const & udpSocket, const std::string &hostAddres, unsigned short port)
{
    udpSocket->writeDatagram(QByteArray().fromStdString(dataToSend), QHostAddress(QString().fromStdString(hostAddres)), port);
}
