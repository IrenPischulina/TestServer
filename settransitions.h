#ifndef SETTRANSITIONS_H
#define SETTRANSITIONS_H

#include <QWidget>
#include <QVector>
#include <QLineEdit>
#include <QFile>
#include <QTextStream>
#include <QPushButton>
#include <QSignalMapper>


namespace Ui {
class SetTransitions;
}

class SetTransitions : public QWidget
{
    Q_OBJECT

public:
    explicit SetTransitions(QWidget *parent = 0);
    ~SetTransitions();
    void openFile(QString fileName);
    void saveFile(QString fileName);

public slots:
    void addLineEdit();
    void okaySlot();
    void deleteSlot();
    void deleteAllSlot();
    void deleteStateSlot(int buttonId);

signals:
    void okaySignal(QVector <int> numbers, QVector <QString> names, QVector <QVector <int>> transitions);

private:
    Ui::SetTransitions *ui;
    QVector <QLineEdit*> nameLineEdits;
    QVector <QLineEdit*> numberLineEdits;
    QVector <QLineEdit*> toStatesLineEdits;
    QVector <QPushButton*> deleteButtons;

    QSignalMapper * signalMapper;//для коннекта слотов к массиву кнопок удаления
};

#endif // SETTRANSITIONS_H
