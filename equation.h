#ifndef EQUATION_H
#define EQUATION_H
#include <QVector>
#include <gauss.h>
#include <boundarycondition.h>

class Equation
{
    double k2, k1, k0, cons, xLeft, xRight;
    QVector<double> xSteps;
    QVector<double> xValues;
    QVector<double> yValues;
    gauss *matrix;
    int BCCount;
    BoundaryCondition *BC;
public:
    Equation(double tK2, double tK1, double tK0, double tCons, double tXLeft, double tXRight);
    void simpleStep(int steps);
    void difficultStep(int numSteps, double step);
    void setBCCount(int n);
    void setBC(int number, bool tType, double tPoint, double tValue);
    void prepSolution();
    void solution();
    QVector<double> getXValues();
    QVector<double> getYValues();

};

#endif // EQUATION_H
