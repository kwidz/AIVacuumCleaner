#include "mainwindow.h"
#include <QApplication>
#include <QLabel>
#include "environment.h"
#include "ai.h"
#include <iostream>
#include <QHBoxLayout>
#include <QGraphicsScene>
using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    //AI i;
    w.setWindowTitle("AI VAcuum Cleaner");
   // i.start();
    w.show();
    a.exec();
    //i.quit();
    //i.wait();

}
