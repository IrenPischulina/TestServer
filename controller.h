#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <QVector>
#include <QString>
#include <QImage>

#include "state.h"
#include "receiver.h"

class Controller : public QObject
{
    Q_OBJECT
public:
    explicit Controller(QObject *parent = nullptr);

    //создает начало списка переходов
    void createBeginEdgeList();

    //добавляет к списку переходов окраску
    void createEndEdgeList();

    //из списка переходов graphviz делает картинку(граф)
    void createGraph();

    //из списка переходов формируется текст
    void createText();


signals:
    void imageReady(QImage image);//когда картинка с графом готова, посылается сигнал в mainwindow, чтобы он вывел ее на сцену
    void textReady(QString text);//когда текст готов, посылается сигнал в mainwindow, чтобы он его вывел в текстедит

public slots:
    //после заполнения пользователем информации о состояниях создаются объекты-состояния, строится граф
    void createStates(QVector <int> numbers, QVector <QString> names, QVector <QVector <int>> transition);

    //пользователь задает адрес и порт для подключения
    void setNetworkSettings(QString IP, int port);

    //обработка пришедшей от приложения строки
    void receiveStr(QString str);

private:
    QVector <State*> states;//массив с состояниями

    //массив с переходами. в него записываются по порядку
    //номера состояний, которые приходят от мобильного приложения
    QVector <int> transitions;

    //если тестировщик дополнительно указывает элемент, при нажатии на который
    //произошел переход, то он записывается сюда. если нет, записывается пустая строка
    QVector <QString> elements;

    //класс-приемник сообщений от тестируемого приложения
    //передает в контроллер полученную строку
    Receiver * receiver;

    //начало списка переходов. оно не меняется, так как по нему
    //рисуется граф
    QString beginEdgeList;

    //конец списка переходов. в него записывается дополнительная
    //информация об окраске текущего и предыдущего состояний
    QString endEdgeList;
};

#endif // CONTROLLER_H
