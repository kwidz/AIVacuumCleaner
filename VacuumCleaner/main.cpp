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
    Environment e;
    AI i;
    QLabel *label = new QLabel;
    w.layout()->addWidget(label);
    w.setWindowTitle("AI VAcuum Cleaner");
    QObject::connect(&e, SIGNAL(refreshMap(QString)), label, SLOT(setText(QString)), Qt::QueuedConnection);
    e.start();
    i.start();
    w.show();
    a.exec();
    e.quit();
    i.quit();
    i.wait();
    e.wait();

}
