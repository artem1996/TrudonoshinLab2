#ifndef EQUATION_H
#define EQUATION_H
#include <QVector>
#include <gauss.h>
#include <boundarycondition.h>
#include <unevenstep.h>

class Equation
{
    double k2, k1, k0, cons, xLeft, xRight;
    QVector<double> xSteps;
    QVector<double> xValues;
    QVector<double> yValues;
    gauss *matrix;
    QVector<BoundaryCondition> BC;
public:
    Equation(double tK2, double tK1, double tK0, double tCons, double tXLeft, double tXRight);
    void simpleStep(int steps);
    void difficultStep(QVector<UnevenStep> steps);
    void setBC(QVector<BoundaryCondition> tBC);
    void solution();
    void doubleSolution();
    QVector<double> getXValues();
    QVector<double> getYValues();

};

#endif // EQUATION_H
