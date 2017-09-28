#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H
#define WIDTH 10
#define HEIGHT 10
#include <vector>
#include <QThread>
//Environement with an array of Boxs which contains some Dust and/or Jewels
//matrix class for easy 2d arrays
template<class T, size_t rows, size_t cols>
class Matrix
{
    std::array<T, rows * cols> m_Data;
public:
    T& operator()(size_t y, size_t x)
    {
        return m_Data[y * cols + x];
    }
};


enum Obstacle { Dust, Jewel};

//the box which is containing Dust or jewel
class Box
{
public:
    Box();
    std::vector<Obstacle> getContent();
private:
    std::vector<Obstacle> content;


};

class Environment : public QThread
{
public:
    Environment();
    Matrix<Box,WIDTH,HEIGHT> getGrid();
    void run();
private:
     Matrix<Box, WIDTH, HEIGHT> grid;
};






#endif // ENVIRONMENT_H
