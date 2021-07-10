#include "mainwindow.h"
#include "field.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qRegisterMetaType<Field>("Field");
    MainWindow w;
    w.show();
    return a.exec();
}
