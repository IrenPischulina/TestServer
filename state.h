#ifndef STATE_H
#define STATE_H

#include <QString>
#include <QVector>

class State
{
public:
    State(int numb, QString nam, QVector <int> toState);

    int getNumberState();
    QString getNameState();
    QVector<int> getToStates();

private:
    int numberState;
    QString nameState;
    QVector <int> toStates;
};

#endif // STATE_H
