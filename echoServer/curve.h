#ifndef CURVE_H
#define CURVE_H
#pragma once

#include <QString>
#include <string>
#include <QDebug>
#include <QList>
#include <QObject>
#include <iostream>
#include <boost/multiprecision/cpp_int.hpp>

using namespace boost::multiprecision;

struct Point{
    uint256_t x;
    uint256_t y;
};

class Curve;

class CurveDestroyer
{
    private:
        Curve* pInstance;
    public:
        ~CurveDestroyer();
        void initialize(Curve* p);
};

class Curve : public QObject
{
    Q_OBJECT
    private:
        static Curve* pInstance;
        static CurveDestroyer destroyer;
        static int a;
        static int b;
        static uint256_t p;
        //Base Point
        static Point G;
        static Point O;
        uint256_t getInverseElement(uint256_t& x);
        const uint256_t N {"115792089237316195423570985008687907852837564279074904382605163141518161494337"};
        bool isInfinityPoint(Point P);
        QString numIntoBinStr(uint1024_t &num);

    protected:
         Curve(QObject *parent = nullptr);
        ~Curve();

        Curve(const Curve& );
        Curve& operator = (Curve &);
        friend class CurveDestroyer;

    public:
        QString getN();
        Point addPoint(Point P, Point Q = G);
        Point doublePoint(Point P = G);
        static Curve* getInstance();
        QString getModule();
        bool isPointValid(Point P);
        Point countComposition(uint1024_t k, Point P = G);
};

#endif // CURVE_H
