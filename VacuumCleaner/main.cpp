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
    w.setWindowTitle("AI VAcuum Cleaner");
    w.show();
    a.exec();


}
