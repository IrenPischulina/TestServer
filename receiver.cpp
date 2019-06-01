#include "receiver.h"
#include <string.h>

#include <QDebug>

Receiver::Receiver()
{
    socket = new QUdpSocket();
    socket -> bind(QHostAddress("10.0.183.148"), 9002);
    connect(socket, SIGNAL(readyRead()), SLOT(readSlot()));
}

void Receiver::setNetworkSettings(QString IP, int port)
{
    socket -> bind(QHostAddress(IP), port);
}

void Receiver::readSlot()
{

    //для приема сигналов с андроида
    QByteArray datagram;
    datagram.resize(socket -> pendingDatagramSize());
    QHostAddress *address = new QHostAddress();
    socket -> readDatagram(datagram.data(), datagram.size(), address);

    QString str = QString::fromUtf8(datagram);//принятая строка

    qDebug() << str;

    sendStr(str);

    //для приема сигналов с кьюта
//    QByteArray datagram;
//    datagram.resize(socket->pendingDatagramSize());
//    QHostAddress *address = new QHostAddress();
//    socket->readDatagram(datagram.data(), datagram.size(), address);

//    QDataStream in(&datagram, QIODevice::ReadOnly);

//    qint64 size = -1;
//    if(in.device()->size() > sizeof(qint64)) {
//    in >> size;
//    } else return;
//    if (in.device()->size() - sizeof(qint64) < size) return;

//    QString str;
//    in >> str;

//    qDebug() << str;
//    sendStr(str);
}