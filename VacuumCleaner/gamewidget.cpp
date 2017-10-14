#include <QMessageBox>
#include <QTimer>
#include <QMouseEvent>
#include <QDebug>
#include <QRectF>
#include "ai.h"
#include <QPainter>
#include <qmath.h>
#include "gamewidget.h"
#include <iostream>

GameWidget::GameWidget(QWidget *parent) :
    QWidget(parent),
    timer(new QTimer(this)),
    generations(-1),
    universeSize(50)
{
    timer->setInterval(3000);
    m_masterColor = "#000";
    universe = new Box[(universeSize + 2) * (universeSize + 2)];
    connect(timer, SIGNAL(timeout()), this, SLOT(newTurn()));
    memset(universe, false, sizeof(Box)*(universeSize + 2) * (universeSize + 2));
}

GameWidget::~GameWidget()
{
    delete [] universe;
}

void GameWidget::startGame(const int &number)
{
    generations = 1;
    ai.universe = universe;
    ai.universeSize = &universeSize;
    ai.start();
    ai.quit();
    ai.wait();
    timer->start();
}

void GameWidget::stopGame()
{
    timer->stop();
}

void GameWidget::clear()
{
    for(int k = 1; k <= universeSize; k++) {
        for(int j = 1; j <= universeSize; j++) {
            universe[k*universeSize + j].deleteDust();
            universe[k*universeSize + j].deleteJewel();
        }
    }
    gameEnds(true);
    update();
}

int GameWidget::cellNumber()
{
    return universeSize;
}

void GameWidget::setCellNumber(const int &s)
{
    universeSize = s;
    resetUniverse();
    update();
}

void GameWidget::resetUniverse()
{
    delete [] universe;
    universe = new Box[(universeSize + 2) * (universeSize + 2)];
    memset(universe, false, sizeof(Box)*(universeSize + 2) * (universeSize + 2));
}

QString GameWidget::dump()
{
    char temp;
    QString master = "";
    for(int k = 1; k <= universeSize; k++) {
        for(int j = 1; j <= universeSize; j++) {
            if(universe[k*universeSize + j].getDust() == Dust) {
                temp = '*';
            } else {
                temp = 'o';
            }
            master.append(temp);
        }
        master.append("\n");
    }
    return master;
}

void GameWidget::setDump(const QString &data)
{
    int current = 0;
    for(int k = 1; k <= universeSize; k++) {
        for(int j = 1; j <= universeSize; j++) {
            if(data[current] == '*')
                universe[k*universeSize + j].addDust();
            current++;
        }
        current++;
    }
    update();
}

int GameWidget::interval()
{
    return timer->interval();
}

void GameWidget::setInterval(int msec)
{
    timer->setInterval(msec);
}

void GameWidget::newTurn()
{
    ai.timerHit();
    if(generations>0){
    srand (time(NULL));
    int randomX = rand()% universeSize+1;
    int randomY = rand()% universeSize+1;
    while(!(universe[randomY*universeSize +randomX ].addDust())){
        randomY = rand()% universeSize+1;
        randomX = rand()% universeSize+1;
    }
    update();
}

}

void GameWidget::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    paintGrid(p);
    paintUniverse(p);
}

void GameWidget::mousePressEvent(QMouseEvent *e)
{
    emit environmentChanged(true);
    double cellWidth = (double)width()/universeSize;
    double cellHeight = (double)height()/universeSize;
    int k = floor(e->y()/cellHeight)+1;
    int j = floor(e->x()/cellWidth)+1;
    if(!(universe[k*universeSize + j].getDust()))
        universe[k*universeSize + j].addDust();
    else
        universe[k*universeSize + j].deleteDust();
    update();
}

void GameWidget::mouseMoveEvent(QMouseEvent *e)
{
    double cellWidth = (double)width()/universeSize;
    double cellHeight = (double)height()/universeSize;
    int k = floor(e->y()/cellHeight)+1;
    int j = floor(e->x()/cellWidth)+1;
    int currentLocation = k*universeSize + j;
    if(!(universe[k*universeSize + j].getDust())){
        universe[k*universeSize + j].addDust();
        update();
     }
    else{
        universe[k*universeSize + j].deleteDust();
        update();
    }
}

void GameWidget::paintGrid(QPainter &p)
{
    QRect borders(0, 0, width()-1, height()-1);
    QColor gridColor = m_masterColor;
    gridColor.setAlpha(10);
    p.setPen(gridColor);
    double cellWidth = (double)width()/universeSize;
    for(double k = cellWidth; k <= width(); k += cellWidth)
        p.drawLine(k, 0, k, height());
    double cellHeight = (double)height()/universeSize;
    for(double k = cellHeight; k <= height(); k += cellHeight)
        p.drawLine(0, k, width(), k);
    p.drawRect(borders);
}

void GameWidget::paintUniverse(QPainter &p)
{
    double cellWidth = (double)width()/universeSize;
    double cellHeight = (double)height()/universeSize;
    for(int k=0; k <= universeSize; k++) {
        for(int j=0; j <= universeSize; j++) {
            if(universe[k*universeSize + j].getDust()) {
                qreal left = (qreal)(cellWidth*j-cellWidth);
                qreal top  = (qreal)(cellHeight*k-cellHeight);
                QRectF r(left, top, (qreal)cellWidth, (qreal)cellHeight);
                p.fillRect(r, QBrush(m_masterColor));
            }
        }
    }
    //painting vacuum position
    qreal left = (qreal)(cellWidth*ai.pos_aspi.x-cellWidth);
    qreal top  = (qreal)(cellHeight*ai.pos_aspi.y-cellHeight);
    QRectF r(left, top, (qreal)cellWidth, (qreal)cellHeight);
    QColor vacuumColor="#F00";
    p.fillRect(r, QBrush(vacuumColor));
}

QColor GameWidget::masterColor()
{
    return m_masterColor;
}

void GameWidget::setMasterColor(const QColor &color)
{
    m_masterColor = color;
    update();
}
