#ifndef POINT_H
#define POINT_H
#include "curve.h"
#include <boost/multiprecision/cpp_int.hpp>

using namespace boost::multiprecision;

class Point : public Curve
{
private:
    int512_t x = 0;
    int512_t y = 0;
    Point G;
    void doublePoint();
    void addPoint(Point Q);

public:
    Point(int512_t x, int512_t y);
    Point calculateComposition();
    void printPoint();

};

#endif // POINT_H
