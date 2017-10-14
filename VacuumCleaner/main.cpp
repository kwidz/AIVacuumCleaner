#include "mainwindow.h"
#include <QApplication>
#include <QLabel>
#include "environment.h"
#include <iostream>
#include <QHBoxLayout>
#include <QGraphicsScene>
using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    Environment e;
    QLabel *label = new QLabel;
    w.setWindowTitle("AI VAcuum Cleaner");
    QObject::connect(&e, SIGNAL(refreshMap(QString)), label, SLOT(setText(QString)), Qt::QueuedConnection);
    e.start();
    w.show();
    a.exec();
    e.quit();
    e.wait();

}
