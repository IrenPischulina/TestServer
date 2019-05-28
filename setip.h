#ifndef SETIP_H
#define SETIP_H

#include <QWidget>
#include <QString>

namespace Ui {
class SetIP;
}

class SetIP : public QWidget
{
    Q_OBJECT

public:
    explicit SetIP(QWidget *parent = 0);
    ~SetIP();

public slots:
    void okaySlot();
    void cancelSlot();

signals:
    void okaySignal(QString IP, int port);

private:
    Ui::SetIP *ui;
    QString oldIP;
    int oldPort;
};

#endif // SETIP_H
