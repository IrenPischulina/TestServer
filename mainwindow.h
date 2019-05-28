#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QImage>
#include <QGraphicsScene>

#include "settransitions.h"
#include "controller.h"
#include "setip.h"

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

private:
    Ui::MainWindow *ui;
    SetTransitions * setTransitions;
    Controller * controller;
    SetIP * setIP;
    QGraphicsScene * sc1;
};

#endif // MAINWINDOW_H
