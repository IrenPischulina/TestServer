#include "state.h"

State::State(int numb, QString nam, QVector<int> toState)
{
    numberState = numb;
    nameState = nam;
    toStates = toState;
}

int State::getNumberState()
{
    return numberState;
}

QString State::getNameState()
{
    return nameState;
}

QVector <int> State::getToStates()
{
    return toStates;
}
