#ifndef RECEIVER_H
#define RECEIVER_H

#include <QObject>
#include <QUdpSocket>
#include <QString>
#include <QDataStream>

class Receiver : public QObject
{
    Q_OBJECT
public:
    Receiver();

    void setNetworkSettings(QString IP, int port);

signals:
    void sendStr(QString str);

public slots:
    void readSlot();

private:
    QUdpSocket * socket;
};

#endif // RECEIVER_H
