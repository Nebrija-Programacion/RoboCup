#include <QCoreApplication>
#include <QUdpSocket>
#include "player.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Player client("TeamAlberto");
    return a.exec();
}
