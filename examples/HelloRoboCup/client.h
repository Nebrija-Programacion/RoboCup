#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QUdpSocket>

class Client : public QObject
{
    Q_OBJECT
public:
    explicit Client(QObject *parent = nullptr);

    QString getReceivedData() const;
    void setReceivedData(const QString &value);

    QString getDataToSend() const;
    void setDataToSend(const QString &value);

signals:

public slots:
    void readPendingDatagrams();

private:

    void processDatagram(QNetworkDatagram datagram);

    QString receivedData;
    QString dataToSend;
    QUdpSocket * udpSocket;
};

#endif // CLIENT_H
