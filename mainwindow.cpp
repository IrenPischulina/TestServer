#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui -> setupUi(this);

    setTransitions = new SetTransitions();
    controller = new Controller();
    setIP = new SetIP();


    //создание и отрисовка сцены
    sc1 = new QGraphicsScene();
    ui -> graphicsView -> setScene(sc1);

    //отключение скроллбаров на сцене
    ui -> graphicsView -> setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui -> graphicsView -> setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    //растягивание сцены по graphicsView
    sc1 -> setSceneRect(0, 0, ui -> graphicsView -> width(), ui -> graphicsView -> height());

    connect(ui -> loadButton,
            SIGNAL(clicked(bool)),
            this,
            SLOT(loadData()));

    connect(setTransitions,
            SIGNAL(okaySignal(QVector<int>,QVector<QString>,QVector<QVector<int> >)),
            controller,
            SLOT(createStates(QVector<int>,QVector<QString>,QVector<QVector<int> >)));

    connect(ui -> setIPButton,
            SIGNAL(clicked(bool)),
            this,
            SLOT(setIPAddress()));

    connect(setIP,
            SIGNAL(okaySignal(QString,int)),
            controller,
            SLOT(setNetworkSettings(QString,int)));

    connect(controller,
            SIGNAL(imageReady(QImage)),
            this,
            SLOT(updateImage(QImage)));

    connect(controller,
            SIGNAL(textReady(QString)),
            this,
            SLOT(updateText(QString)));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::loadData()
{
    setTransitions -> show();
}

void MainWindow::setIPAddress()
{
    setIP -> show();
}

void MainWindow::updateImage(QImage image)
{
    sc1 -> clear();
    sc1 -> addPixmap(QPixmap::fromImage(image).scaled(ui -> graphicsView -> width(), image.height()));
}

void MainWindow::updateText(QString text)
{
    ui -> textEdit -> append(text);
}
