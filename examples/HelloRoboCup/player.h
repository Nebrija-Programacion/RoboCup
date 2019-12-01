#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QUdpSocket>
#include <string>
#include <functional>
#include <map>


struct PlayerData {
    std::string teamName;
    char side;
    std::string status;
    int number;
    float x;
    float y;
    bool positioned;
};


class Player : public QObject
{
    Q_OBJECT
public:
    explicit Player(std::string const & teamName, QObject *parent = nullptr);

    // Your Functions
    void processMsg(std::string const & msg);
    std::string extractCommand(std::string const & msg);


public slots:
    void readPendingDatagrams();

private:
    void processDatagram(QNetworkDatagram datagram);
    PlayerData playerData;

    QString receivedData;
    std::string dataToSend;
    QUdpSocket * udpSocket;

    void printPlayerData();
    void computePlayerData();

    // functions map
    std::map<std::string, std::function<void (std::string)> > functionsMap;

    // lambda functions declaration
    std::function<void (std::string)> initFunction;

};

#endif // CLIENT_H
