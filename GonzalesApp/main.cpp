#include "ui/mainwindow.h"
#include <QApplication>

///@todo: move factories there from mainwindow
///@todo add algorithm to Node for iterating!
///@todo remove unnecessary files from repository


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
