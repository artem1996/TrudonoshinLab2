//
// Created by note on 02.02.17.
//

#ifndef ARINATRUD2_EQUATION_H
#define ARINATRUD2_EQUATION_H


#include <vector>
#include "gauss.h"
#include "boundarycondition.h"
#include "UnEvenStep.h"

class Equation
{
    double k2, k1, k0, cons;
    std::vector<double> xSteps;
    std::vector<double> xValues;
    std::vector<double> yValues;
    gauss *matrix;
    std::vector<BoundaryCondition> BC;
public:
    Equation(double tK2, double tK1, double tK0, double tCons);
    void setStep(std::vector<UnevenStep> steps);
    void setBC(std::vector<BoundaryCondition> tBC);
    void solution();
    void doubleSolution();
    std::vector<double> getXValues();
    std::vector<double> getYValues();

};

#endif //ARINATRUD2_EQUATION_H
