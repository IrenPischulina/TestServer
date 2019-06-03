#include "receiver.h"
#include <string.h>

#include <QDebug>

Receiver::Receiver()
{
    socket = new QUdpSocket();
    socket -> bind(QHostAddress(defaultIP), defaultPort);
    connect(socket, SIGNAL(readyRead()), SLOT(readSlot()));
}

void Receiver::setNetworkSettings(QString IP, int port)
{
    socket -> bind(QHostAddress(IP), port);
}

QString Receiver::getDefaultIP()
{
    return defaultIP;
}

int Receiver::getDefaultPort()
{
    return defaultPort;
}

void Receiver::readSlot()
{

    //для приема сигналов с андроида
    QByteArray datagram;
    datagram.resize(socket -> pendingDatagramSize());
    QHostAddress *address = new QHostAddress();
    socket -> readDatagram(datagram.data(), datagram.size(), address);

    QString str = QString::fromUtf8(datagram);//принятая строка

    sendStr(str);
}
