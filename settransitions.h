#ifndef SETTRANSITIONS_H
#define SETTRANSITIONS_H

#include <QWidget>
#include <QVector>
#include <QLineEdit>
#include <QFile>
#include <QTextStream>


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

public slots:
    void addLineEdit();
    void okaySlot();
    void deleteSlot();

signals:
    void okaySignal(QVector <int> numbers, QVector <QString> names, QVector <QVector <int>> transitions);

private:
    Ui::SetTransitions *ui;
    QVector <QLineEdit*> nameLineEdits;
    QVector <QLineEdit*> numberLineEdits;
    QVector <QLineEdit*> toStatesLineEdits;
};

#endif // SETTRANSITIONS_H
