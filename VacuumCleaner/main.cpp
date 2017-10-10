#include "mainwindow.h"
#include <QApplication>
#include "environment.h"
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    //w.show();
    Environment e;
    cout << "running e";
    e.run();

    return a.exec();
}
