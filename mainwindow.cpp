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

    //кнопка, чтобы открыть окно загрузки данных о состояниях
    connect(ui -> loadButton,
            SIGNAL(clicked(bool)),
            this,
            SLOT(loadData()));

    //кнопка, открывающая окно с заданием адреса и порта
    connect(ui -> setIPButton,
            SIGNAL(clicked(bool)),
            this,
            SLOT(setIPAddress()));

    //кнопка для очистки списка переходов
    connect(ui -> clearListButton,
            SIGNAL(clicked(bool)),
            this,
            SLOT(clearTransitionsList()));


    //передача заданного списка переходов и состояний контроллеру
    connect(setTransitions,
            SIGNAL(okaySignal(QVector<int>,QVector<QString>,QVector<QVector<int> >)),
            controller,
            SLOT(createStates(QVector<int>,QVector<QString>,QVector<QVector<int> >)));

    //передача контроллеру адреса и порта для соединения
    connect(setIP,
            SIGNAL(okaySignal(QString,int)),
            controller,
            SLOT(setNetworkSettings(QString,int)));

    //передача от контроллера картинки для отрисовки
    connect(controller,
            SIGNAL(imageReady(QImage)),
            this,
            SLOT(updateImage(QImage)));

    //передача от контроллера списка совершенных переходов
    connect(controller,
            SIGNAL(textReady(QString)),
            this,
            SLOT(updateText(QString)));

    //меню
    //открыть окно загрузки данных о состояниях
    connect(ui -> action_9,
            SIGNAL(triggered(bool)),
            this,
            SLOT(loadData()));

    //открыть окно для задания порта и адреса
    connect(ui -> action_10,
            SIGNAL(triggered(bool)),
            this,
            SLOT(setIPAddress()));

    //открытие файла
    connect(ui -> action_8,
            SIGNAL(triggered(bool)),
            this,
            SLOT(openFile()));

    //сохранение информации о состояниях в файл
    connect(ui -> action_5,
            SIGNAL(triggered(bool)),
            this,
            SLOT(saveFile()));

    //сохранить результаты теста
    connect(ui -> action_2,
            SIGNAL(triggered(bool)),
            this,
            SLOT(saveResults()));
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
    int imgWidth, imgHeight;
    sc1 -> clear();

    //если картинка шире сцены, приравниваем ее ширину к ширине сцены, чтобы не выехала за края
    if(image.width() > ui -> graphicsView -> width())
        imgWidth = ui -> graphicsView -> width();
    else
        imgWidth = image.width();

    //с высотой то же самое
    if(image.height() > ui -> graphicsView -> height())
        imgHeight = ui -> graphicsView -> height();
    else
        imgHeight = image.height();

    sc1 -> addPixmap(QPixmap::fromImage(image).scaled(imgWidth, imgHeight));
}

void MainWindow::updateText(QString text)
{
    ui -> textEdit -> append(text);
}

void MainWindow::clearTransitionsList()
{
    ui -> textEdit -> clear();
}

void MainWindow::openFile()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "",
                                                    tr("Text Files (*.txt)"));

    if (fileName != "") {
        QFile file(fileName);
        if (!file.open(QIODevice::ReadOnly)) {
            QMessageBox::critical(this, tr("Error"), tr("Could not open file"));
            return;
        }
        file.close();
        setTransitions -> openFile(fileName);
    }

}

void MainWindow::saveFile()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"), "",
                                                    tr("Text Files (*.txt)")) + ".txt";

    if (fileName != "") {
        QFile file(fileName);
        if (!file.open(QIODevice::WriteOnly)) {
            QMessageBox::critical(this, tr("Error"), tr("Could not save file"));
            return;
        }
        file.close();
        setTransitions -> saveFile(fileName);
    }
}

void MainWindow::saveResults()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"), "",
                                                    tr("Text Files (*.txt)")) + ".txt";

    if (fileName != "") {
        QFile file(fileName);
        if (!file.open(QIODevice::WriteOnly)) {
            QMessageBox::critical(this, tr("Error"), tr("Could not save file"));
            return;
        }
        QTextStream stream(&file);
        stream << ui -> textEdit -> toPlainText();
        stream.flush();
        file.close();

    }
}
