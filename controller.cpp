#include "controller.h"
#include <QDebug>
#include <QFile>
#include <QTextStream>

Controller::Controller(QObject *parent) : QObject(parent)
{
    receiver = new Receiver();
    beginEdgeList = "";
    endEdgeList = "";
    connect(receiver,
            SIGNAL(sendStr(QString)),
            this,
            SLOT(receiveStr(QString)));
}

void Controller::createBeginEdgeList()
{
    //этот метод вызывается один раз, после задания пользователем информации о состояниях
    //последующие разы вызывается, если пользователь меняет эти данные
    //beginEdgeList = "digraph G {\n rankdir=LR;\n";
    beginEdgeList = "digraph G {\n";
    for( int i = 0; i < states.size(); i ++)
    {
        QVector <int> toStates;
        toStates = states[i] -> getToStates();
        for( int j = 0; j < toStates.size(); j ++)
        {
            beginEdgeList += QString::number(states[i]->getNumberState()) + "->" + QString::number(toStates[j]) + ";\n";
        }
        beginEdgeList += QString::number(states[i] -> getNumberState()) +
                "[label=\"" +
                QString::number(states[i] -> getNumberState()) +
                " (" +
                states[i] -> getNameState() +
                ")\"];\n";

    }
    endEdgeList = "}";
    //создание графа
    createGraph();
}

void Controller::createEndEdgeList(bool pressedElement)
{
    QString oldEndList;
    oldEndList = endEdgeList;
    endEdgeList = "";

    if(pressedElement == false)
       { //добавление строк для окраски текущего и предыдущего состояний
        for( int i = 0; i < states.size(); i ++)
        {

            if(states[i] -> getNumberState() == transitions[transitions.size() - 1])
                endEdgeList += QString::number(transitions[transitions.size() - 1]) + "[color=\"#00FF00\"];\n";

            if(transitions.size() > 1)
                if(states[i] -> getNumberState() == transitions[transitions.size() - 2])
                    endEdgeList += QString::number(transitions[transitions.size() - 2]) + "[color=\"#AAFFAA\"];\n";
        }
        endEdgeList += "}";
    }
    else
        endEdgeList += oldEndList;

    //создание графа
    createGraph();
    //создание текста для вывода
    createText(pressedElement);

}

void Controller::createGraph()
{
    //путь к картинке и файлу, с которого будет грузиться граф
    QString path = "edg.dot";

    //запись сформированного текста в файл для graphviza
    QFile file(path);
    file.open(QIODevice::WriteOnly);
    QTextStream stream(&file);
    stream << beginEdgeList + endEdgeList << endl;
    file.close();

    //создаем картинку
    QString command = "dot -Tpng " + path + " -o " + path + ".png";
    system(command.toStdString().c_str());


    QImage img;
    img.load(path + ".png");
    //отправляем картинку для вывода на экран
    imageReady(img);
}

void Controller::createText(bool pressedElement)
{
    State * current = nullptr;//текущее состояния
    State * previous = nullptr;//предыдущее состояние


    QString tempStr = "";

    if(pressedElement == true)
    {
        tempStr += "Нажатие на \"" + elements[elements.size() - 1] + "\" \n" ;
    }
    else
    {
        if(transitions.size() >= 1)
            //поиск в списке состояний состояний с номерами, которые пришли от приложения
            for (int i = 0; i < states.size(); i ++)
            {
                if(states[i] -> getNumberState() == transitions[transitions.size() - 1])
                    current = states[i];

                if(transitions.size() > 1)
                    if(states[i] -> getNumberState() == transitions[transitions.size() - 2])
                        previous = states[i];
            }

        //начало формирования строки для вывода в текстедит
        tempStr += "Переход: \n";
        //если состояний в списке больше одного
        if(transitions.size() > 1)
        {
            tempStr += QString::number(transitions[transitions.size() - 2]);
            if(previous != nullptr)
                tempStr += " (" + previous -> getNameState() + ")";
            else
                tempStr += " (состояние не задано)";
        }

        tempStr += "  ->  " + QString::number(transitions[transitions.size() - 1]);
        if(current != nullptr)
            tempStr += " (" + current -> getNameState() + ")";
        else
            tempStr += " (состояние не задано)";

        bool allowTransition = false;//флаг на разрешенность перехода
        if(current != nullptr && previous != nullptr)
        {
            if(previous == current)//если предыдущее состояние равно текущему, то переход считается разрешенным
                allowTransition = true;
            else
            {
                QVector <int> tempVector;
                tempVector = previous -> getToStates();
                for (int i = 0; i < tempVector.size(); i ++)
                {
                    if(tempVector[i] == current -> getNumberState())//флаг меняется, если такой переход найден
                        allowTransition = true;
                }
            }
        }
        else if(current != nullptr && transitions.size() == 1)//если состояние только одно в списке, то переход считается разрешенным
            allowTransition = true;

        //если переход не был разрешен, к тексту добавляется об этом запись
        if(allowTransition == false)
            tempStr += "\nошибка! запрещенный переход!";
    }
    tempStr += "\n";

    //текст готов к отправке для вывода на экран
    textReady(tempStr);

}


//создание состояний. вызывается после заполнения окошка с информацией о состояниях
void Controller::createStates(QVector<int> numbers, QVector<QString> names, QVector<QVector<int>> transition)
{
    //очистка памяти
    if(states.size() != 0)
    {
        for(int i = 0; i < states.size(); i ++)
        {
            delete states[i];
        }
    }
    states.clear();
    transitions.clear();

    //создание состояний
    for(int i = 0; i < numbers.size(); i ++)
    {
        states.push_back(new State (numbers[i], names[i], transition[i]));
    }

    //создается граф без окраски
    createBeginEdgeList();
}

//посылается приемнику адрес и порт для коннекта
void Controller::setNetworkSettings(QString IP, int port)
{
    receiver -> setNetworkSettings(IP, port);
}


void Controller::receiveStr(QString str)
{
    //если список состояний пуст, ничего не делать
    if(states.size() == 0)
        return;

    if(str[0] == "#")//если пришло состояние
    {
        QStringList tempStr = str.split("#");//принятая строка бьется по #
        transitions.push_back(tempStr[1].toInt());//запись номера пришедшего состояния в список
        createEndEdgeList(false);
    } else
        if(str[0] == "!")//если пришло нажатие на элемент
        {
            QStringList tempStr = str.split("!");//принятая строка бьется по !
            elements.push_back(tempStr[1]);//запись нажатого элемента в список
            createEndEdgeList(true);
        }
}
