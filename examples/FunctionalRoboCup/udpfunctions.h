#ifndef UDPFUNCTIONS_H
#define UDPFUNCTIONS_H

#include <QUdpSocket>
#include <QNetworkDatagram>
#include <string>
#include <memory>
#include "playerdata.h"

std::unique_ptr<QUdpSocket> createSocket(std::string const & hostAddres, unsigned short port);
QNetworkDatagram receiveData(std::unique_ptr<QUdpSocket> const & udpSocket);
void sendData(PlayerData const & playerData, std::unique_ptr<QUdpSocket> const & updSocket, const QNetworkDatagram &datagram);
void sendData(std::string const & dataToSend, const std::unique_ptr<QUdpSocket> &udpSocket, std::string const & hostAddres, unsigned short port);


#endif // UDPFUNCTIONS_H
