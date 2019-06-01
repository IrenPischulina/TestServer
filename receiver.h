#ifndef RECEIVER_H
#define RECEIVER_H

#include <QObject>
#include <QUdpSocket>
#include <QString>
#include <QDataStream>

const QString defaultIP = "192.168.1.131";
const int defaultPort = 9002;

class Receiver : public QObject
{
    Q_OBJECT
public:
    Receiver();

    void setNetworkSettings(QString IP, int port);
    static QString getDefaultIP();
    static int getDefaultPort();

signals:
    void sendStr(QString str);

public slots:
    void readSlot();

private:
    QUdpSocket * socket;
};

#endif // RECEIVER_H
