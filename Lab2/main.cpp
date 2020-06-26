#include "mainwindow.h"
#include <QApplication>
#include <math.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setFixedSize(700, 700);
    w.show();

    return a.exec();
}
