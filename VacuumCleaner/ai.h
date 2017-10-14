#ifndef AI_H
#define AI_H
#include "environment.h"
#include <vector>
#include <QThread>
#include <QTimer>


class Point
{
    public:
        int x, y;
    public:
        Point() : x(0), y(0) {}
        Point(int x, int y) : x(x), y(y) {}
};

class AI : public QThread
{


    Q_OBJECT
    signals:
        void refreshMap(QString test);
public:
    AI();
private:
    void run();
    void machineLearning();
    Matrix<Box, WIDTH, HEIGHT>ObserveEnvironmentWithAllMySensors();
    std::vector<Point> UpdateMyState();
    Point ChooseAnAction(std::vector<Point> v);
    void justDoIt();
    Matrix<Box, WIDTH, HEIGHT> Sensor();
private slots:
    void timerHit();
    void timerHit2();
};



#endif // AI_H
