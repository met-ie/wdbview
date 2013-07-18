#include <QtGui/QApplication>
#include <QDebug>
#include <QFile>
#include "mainwindow.h"
#include <fstream>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow window;

    window.show();
    
    return a.exec();
}
