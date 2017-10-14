#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H
#define WIDTH 10
#define HEIGHT 10
#include <vector>
#include <QThread>
#include <QTimer>
//Environement with an array of Boxs which contains some Dust and/or Jewels
//matrix class for easy 2d arrays
template<class T, size_t rows, size_t cols>
class Matrix
{
public:
    std::array<T, rows * cols> m_Data;
    T& operator()(size_t y, size_t x)
    {
        return m_Data[y * cols + x];
    }
};


enum Obstacle {Dust, Jewel};

//the box which is containing Dust or jewel
class Box
{
public:
    Box();
    std::vector<Obstacle> getContent();
    std::string display();
private:
    std::vector<Obstacle> content;


};

class Environment : public QThread
{
    Q_OBJECT
    signals:
        void refreshMap(QString test);
public:
    Environment();
    void changeMatrix();
    Matrix<Box,WIDTH,HEIGHT> getGrid();

private:
     Matrix<Box, WIDTH, HEIGHT> grid;
private:
    void run();
    QString m_test;
private slots:
    void timerHit();
};






#endif // ENVIRONMENT_H
