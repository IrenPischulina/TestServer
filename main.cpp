#include "mainwindow.h"
#include <QApplication>
#include <QTranslator>
#include <QLibraryInfo>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTranslator qTranslator;
    qTranslator.load("qt_ru", QLibraryInfo::location(QLibraryInfo::TranslationsPath));
    a.installTranslator(&qTranslator);

    MainWindow w;
    w.show();

    return a.exec();
}
