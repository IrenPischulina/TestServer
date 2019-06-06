#include "settransitions.h"
#include "ui_settransitions.h"
#include <QDebug>

SetTransitions::SetTransitions(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SetTransitions)
{
    ui->setupUi(this);

    connect(ui -> addStateButton,
            SIGNAL(clicked(bool)),
            this,
            SLOT(addLineEdit()));
    connect(ui -> okayButton,
            SIGNAL(clicked(bool)),
            this,
            SLOT(okaySlot()));
    connect(ui -> deleteButton,
            SIGNAL(clicked(bool)),
            this,
            SLOT(deleteAllSlot()));

    signalMapper = new QSignalMapper(this);
    // передаём номер кнопки из маппера в слот
    connect(signalMapper, SIGNAL(mapped(int)), this, SLOT(deleteStateSlot(int)));

    addLineEdit();
}

SetTransitions::~SetTransitions()
{
    delete ui;
}

void SetTransitions::openFile(QString fileName)
{
    //очистка памяти
    for(int i = 0; i < numberLineEdits.size(); i ++)
    {
        delete numberLineEdits[i];
        delete nameLineEdits[i];
        delete toStatesLineEdits[i];
        delete deleteButtons[i];
    }
    numberLineEdits.clear();
    nameLineEdits.clear();
    toStatesLineEdits.clear();
    deleteButtons.clear();

    //открытие файла
    QFile file(fileName);
    QString strNumb, strName, strToStates;

    QTextStream in(&file);
    file.open(QIODevice::ReadOnly);


    //считывание данных из файла
    while (!(in.atEnd())) {

        //считывается номер состояния
        in >> strNumb;
        in >> strName;//название
        in >> strToStates;//переходы

        addLineEdit();//на форму добавляется строка с лайнедитами

        //запись данных в лайнедиты
        numberLineEdits[numberLineEdits.size() - 1] -> setText(strNumb);
        nameLineEdits[nameLineEdits.size() - 1] -> setText(strName.replace("_", " "));
        toStatesLineEdits[toStatesLineEdits.size() - 1] -> setText(strToStates);

    }
    file.close();//закрытие файла
    deleteSlot();//удаление лишней строки
    okaySlot();//нажатие кнопки ок
}

void SetTransitions::saveFile(QString fileName)
{
    QFile file(fileName);

    QTextStream stream(&file);
    file.open(QIODevice::WriteOnly);


    for( int i = 0; i < numberLineEdits.size(); i ++)
    {
        QString tempStr = nameLineEdits[i] -> text().replace(" ", "_");//перед записью в файл заменяем все пробелы на нижние подчеркивания
        stream << numberLineEdits[i] -> text() +
                  " " +
                  tempStr +
                  " " +
                  toStatesLineEdits[i] -> text() +
                  "\n";
        stream.flush();
    }
    file.close();
}

void SetTransitions::addLineEdit()
{
    //добавление поля под номер состояния
    QLineEdit *editNumb = new QLineEdit(this);
    editNumb -> setGeometry(40, 50 + (40 * numberLineEdits.size()), 150, 30);
    editNumb -> show();
    numberLineEdits.push_back(editNumb);

    //добавление поля под имя состояния
    QLineEdit *editName = new QLineEdit(this);
    editName -> setGeometry(200, 50 + (40 * nameLineEdits.size()), 200, 30);
    editName -> show();
    nameLineEdits.push_back(editName);

    //добавление поля под разрешенные переходы
    QLineEdit *editToStates = new QLineEdit(this);
    editToStates -> setGeometry(410, 50 + (40 * toStatesLineEdits.size()), 200, 30);
    editToStates -> show();
    toStatesLineEdits.push_back(editToStates);

    //добавление кнопки удаления
    QPushButton *pushButton = new QPushButton(this);
    pushButton -> setGeometry(620, 50 + (40 * deleteButtons.size()), 100, 30);
    pushButton -> setText("Удалить");
    pushButton -> show();
    deleteButtons.push_back(pushButton);

    // подключаем сигнал клика кнопки к мапперу
    connect(pushButton, SIGNAL(clicked(bool)), signalMapper, SLOT(map()));
    signalMapper -> setMapping(pushButton, deleteButtons.size() - 1); // по клику кнопки будем передавать номер этой кнопки

}

void SetTransitions::okaySlot()
{
    //три вектора под данные о состояниях
    QVector <int> numbers;
    QVector <QString> names;
    QVector <QVector <int>> transitions;
    //заполнение их данными, которые передадутся в контроллер для создания объектов-состояний
    for (int i = 0; i < numberLineEdits.size(); i ++)
    {
        numbers.push_back(numberLineEdits[i] -> text().toInt());
        names.push_back(nameLineEdits[i] -> text());
        QString strWithoutSpaces = toStatesLineEdits[i] -> text().remove(" ");//удаляем проблелы
        QStringList tempList = strWithoutSpaces.split(',');//делим строку по запятым
        QVector <int> tempVector;
        for( int j = 0; j < tempList.size(); j ++)
        {
            tempVector.push_back(tempList[j].toInt());
        }
        transitions.push_back(tempVector);
    }
    hide();
    okaySignal(numbers, names, transitions);

}

//удаление последнего состояния
void SetTransitions::deleteSlot()
{
    if(numberLineEdits.size() == 0)
        return;
    //удаление поля под номер состояния
    delete numberLineEdits[numberLineEdits.size() - 1];
    numberLineEdits.pop_back();

    //удаление поля под имя состояния
    delete nameLineEdits[nameLineEdits.size() - 1];
    nameLineEdits.pop_back();

    //удаление поля под разрешенные переходы
    delete toStatesLineEdits[toStatesLineEdits.size() - 1];
    toStatesLineEdits.pop_back();

    //удаление кнопки удаления
    delete deleteButtons[deleteButtons.size() - 1];
    deleteButtons.pop_back();

    //переопределяем номера, отправляемые при клике
    for( int i = 0; i < numberLineEdits.size(); i ++)
    {
        connect(deleteButtons[i], SIGNAL(clicked(bool)), signalMapper, SLOT(map()));
        signalMapper -> setMapping(deleteButtons[i], i); // по клику кнопки будем передавать номер этой кнопки
    }

}


//очистка списка состояний
void SetTransitions::deleteAllSlot()
{
    if(numberLineEdits.size() == 0)
        return;
    for( int i = numberLineEdits.size() - 1; i >= 0; i --)
    {
        //удаление поля под номер состояния
        delete numberLineEdits[i];
        numberLineEdits.pop_back();

        //удаление поля под имя состояния
        delete nameLineEdits[i];
        nameLineEdits.pop_back();

        //удаление поля под разрешенные переходы
        delete toStatesLineEdits[i];
        toStatesLineEdits.pop_back();

        //удаление кнопки удаления
        delete deleteButtons[i];
        deleteButtons.pop_back();

    }

    addLineEdit();
}

void SetTransitions::deleteStateSlot(int buttonId)
{
    for( int i = numberLineEdits.size() - 1; i > buttonId; i --)
    {
        numberLineEdits[i] -> setGeometry(numberLineEdits[i - 1] -> x(),
                                              numberLineEdits[i - 1] -> y(),
                                              numberLineEdits[i - 1] -> width(),
                                              numberLineEdits[i - 1] -> height());

        nameLineEdits[i] -> setGeometry(nameLineEdits[i - 1] -> x(),
                                            nameLineEdits[i - 1] -> y(),
                                            nameLineEdits[i - 1] -> width(),
                                            nameLineEdits[i - 1] -> height());

        toStatesLineEdits[i] -> setGeometry(toStatesLineEdits[i - 1] -> x(),
                                                toStatesLineEdits[i - 1] -> y(),
                                                toStatesLineEdits[i - 1] -> width(),
                                                toStatesLineEdits[i - 1] -> height());

        deleteButtons[i] -> setGeometry(deleteButtons[i - 1] -> x(),
                                            deleteButtons[i - 1] -> y(),
                                            deleteButtons[i - 1] -> width(),
                                            deleteButtons[i - 1] -> height());
    }

    //удаление поля под номер состояния
    delete numberLineEdits[buttonId];
    numberLineEdits.remove(buttonId);

    //удаление поля под имя состояния
    delete nameLineEdits[buttonId];
    nameLineEdits.remove(buttonId);

    //удаление поля под разрешенные переходы
    delete toStatesLineEdits[buttonId];
    toStatesLineEdits.remove(buttonId);

    //удаление кнопки удаления
    delete deleteButtons[buttonId];
    deleteButtons.remove(buttonId);

    //переопределяем номера, отправляемые при клике
    for( int i = 0; i < numberLineEdits.size(); i ++)
    {
        connect(deleteButtons[i], SIGNAL(clicked(bool)), signalMapper, SLOT(map()));
        signalMapper -> setMapping(deleteButtons[i], i); // по клику кнопки будем передавать номер этой кнопки
    }

}

