#ifndef AI_H
#define AI_H
#include <vector>
#include <QThread>
#include <QTimer>
class AI : public QThread
{
    Q_OBJECT
    signals:
        void refreshMap(QString test);
public:
    AI();
private:
    void run();
private slots:
    void timerHit();
    void timerHit2();
};


#endif // AI_H
