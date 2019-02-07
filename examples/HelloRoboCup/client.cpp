#include "client.h"
#include <QNetworkDatagram>

Client::Client(QObject *parent) :
    QObject(parent),
    receivedData{""},
    dataToSend{""}
{
    udpSocket = new QUdpSocket(this);
    udpSocket->bind(QHostAddress::LocalHost, 6000);

    connect(udpSocket, SIGNAL(readyRead()),
            this, SLOT(readPendingDatagrams()));

    udpSocket->writeDatagram("(init MyTeam (version 15))", QHostAddress::LocalHost, 6000);
}

void Client::readPendingDatagrams()
{
    while (udpSocket->hasPendingDatagrams()) {
        QNetworkDatagram datagram = udpSocket->receiveDatagram();
        processDatagram(datagram);
        udpSocket->writeDatagram(datagram.makeReply(dataToSend.toUtf8()));
    }
}

void Client::processDatagram(QNetworkDatagram datagram)
{
    receivedData = datagram.data();
    // TODO
    dataToSend = "(move 0 0)";
}

QString Client::getReceivedData() const
{
    return receivedData;
}

void Client::setReceivedData(const QString &value)
{
    receivedData = value;
}

QString Client::getDataToSend() const
{
    return dataToSend;
}

void Client::setDataToSend(const QString &value)
{
    dataToSend = value;
}
