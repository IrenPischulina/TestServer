#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QImage>
#include <QGraphicsScene>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>

#include "settransitions.h"
#include "controller.h"
#include "setip.h"
#include "reference.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void loadData();
    void setIPAddress();
    void updateImage(QImage image);
    void updateText(QString text);
    void clearTransitionsList();
    void openFile();
    void saveFile();
    void saveResults();
    void reference1();


private:
    Ui::MainWindow *ui;
    SetTransitions * setTransitions;
    Controller * controller;
    SetIP * setIP;
    QGraphicsScene * sc1;
    Reference * reference;
};

#endif // MAINWINDOW_H
