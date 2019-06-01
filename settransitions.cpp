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
    connect(ui->deleteButton,
            SIGNAL(clicked(bool)),
            this,
            SLOT(deleteSlot()));

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
    }
    numberLineEdits.clear();
    nameLineEdits.clear();
    toStatesLineEdits.clear();

    //открытие файла
    QFile file(fileName);
    QString strNumb, strName, strToStates;

    QTextStream in(&file);
    file.open(QIODevice::ReadOnly);


    while (!(in.atEnd())) {

        in >> strNumb;
        in >> strName;
        in >> strToStates;

        addLineEdit();

        numberLineEdits[numberLineEdits.size() - 1] -> setText(strNumb);
        nameLineEdits[nameLineEdits.size() - 1] -> setText(strName);
        toStatesLineEdits[toStatesLineEdits.size() - 1] -> setText(strToStates);

    }
    file.close();
    deleteSlot();
    okaySlot();
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
}

void SetTransitions::okaySlot()
{
    QVector <int> numbers;
    QVector <QString> names;
    QVector <QVector <int>> transitions;
    for (int i = 0; i < numberLineEdits.size(); i ++)
    {
        numbers.push_back(numberLineEdits[i] -> text().toInt());
        names.push_back(nameLineEdits[i] -> text());
        QStringList tempList = toStatesLineEdits[i] -> text().split(',');
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

}

