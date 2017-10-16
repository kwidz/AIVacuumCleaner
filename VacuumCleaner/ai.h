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
private :
    QTimer* timer;

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
    void machineLearning();
    Box* ObserveEnvironmentWithAllMySensors();
    std::vector<Point> UpdateMyState();
    Point ChooseAnAction(std::vector<Point> v);
    Box* Sensor();
public slots:
    void timerHit2();
};



#endif // AI_H
