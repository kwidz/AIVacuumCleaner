#ifndef AI_H
#define AI_H
#include <vector>
#include <QThread>
#include <QTimer>
#include "sensor.h"
#include "effector.h"

class AI : public QThread
{
public :
    Point pos_aspi;
    sensor senseur;
    effector effecteur;
    int energy=0;
    int jewelPicked=0;
    int jewelRemoved=0;
    int dustRemoved=0;
    int* overallPoints;
    int timeBetweenResearch=2;
    bool reboot = true;
private :
    QTimer* timer;
    void stats();

    Q_OBJECT
    signals:
        void refreshMap(QString test);
public:
    AI();
    void timerHit();
    void justDoIt();

    Point getPos_aspi() const;
    void setPos_aspi(const Point &value);

private:
    void run();
    void machineLearning(Point p);
    Box* ObserveEnvironmentWithAllMySensors();
    std::vector<Point> UpdateMyState();
    Point ChooseAnAction(std::vector<Point> v);
    Box* Sensor();
public slots:
    void timerHit2();
};



#endif // AI_H
