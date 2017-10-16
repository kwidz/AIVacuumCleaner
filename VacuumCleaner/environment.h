#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H
#define PERCENTAGE_JEWELS 15 
#define PERCENTAGE_DUST 30
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
    bool getDust();
    bool getJewel();
    bool addDust();
    bool addJewel();
    void deleteDust();
    void deleteJewel();
private:
    bool dust=false;
    bool jewel=false;

};
#endif // ENVIRONMENT_H
