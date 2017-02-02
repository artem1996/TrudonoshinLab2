//
// Created by note on 02.02.17.
//

#include "equation.h"
#define DIAP 0.001


Equation::Equation(double tK2, double tK1, double tK0, double tCons)
{
    k2 = tK2;
    k1 = tK1;
    k0 = tK0;
    cons = tCons;
}

void Equation::setStep(std::vector<UnevenStep> steps) {
    for(int i = 0; i < steps.size(); i++) {
        for(int j = 0; j < steps[i].getNumSteps(); j++)
            xSteps.push_back(steps[i].getStepSize());
    }
}


void Equation::setBC(std::vector<BoundaryCondition> tBC) {
    BC = tBC;
    /*for(int i = 0; i < BC.size(); i++) {
        std::cout << BC[i];
    }*/
}

void Equation::solution() {
    matrix = new gauss((int)xSteps.size() + 1);
    matrix->reset();
    double tempPoint = BC[0].getPoint();
    int BCPoint = 0;
    int i;
    for(i = 0; i < xSteps.size(); i++) {
        xValues.push_back(tempPoint);
        double step = xSteps[i];

        int j = i + 1;

        matrix->into_matrix(i,i,k2/step) ;
        matrix->into_matrix(i,j,-k2/step) ;
        matrix->into_matrix(j,i,-k2/step) ;
        matrix->into_matrix(j,j,k2/step) ;

        matrix->into_matrix(i,i,k1/2) ;
        matrix->into_matrix(i,j,-k1/2) ;
        matrix->into_matrix(j,i,k1/2) ;
        matrix->into_matrix(j,j,-k1/2) ;

        matrix->into_matrix(i,i,-k0*step/3) ;
        matrix->into_matrix(i,j,-k0*step/6) ;
        matrix->into_matrix(j,i,-k0*step/6) ;
        matrix->into_matrix(j,j,-k0*step/3) ;

        matrix->into_constants(i, cons*step/2);
        matrix->into_constants(j, cons*step/2);

        if(BCPoint < BC.size() && tempPoint >= BC[BCPoint].getPoint() - DIAP) {
            if(BC[BCPoint].getType() == 1) {
                matrix->into_constants(i, - k2 * BC[BCPoint].getValue());
                BCPoint++;
            } else if(BC[BCPoint].getType() == 0) {
                matrix->clearStr(i);
                matrix->into_matrix(i,i,1) ;
                matrix->into_constants(i, BC[BCPoint].getValue());
                BCPoint++;
            } else {
                matrix->into_matrix(i, i, k2);
                BCPoint++;
            }
        }
        tempPoint += step;
    }
    xValues.push_back(tempPoint);
    if(BCPoint < BC.size() && tempPoint >= BC[BCPoint].getPoint() - DIAP) {
        if(BC[BCPoint].getType() == 1) {
            matrix->into_constants(i, k2 * BC[BCPoint].getValue());
        } else if(BC[BCPoint].getType() == 0) {
            matrix->clearStr(i);
            matrix->into_matrix(i,i,1) ;
            matrix->into_constants(i, BC[BCPoint].getValue());
        } else {
            matrix->into_matrix(i, i, -k2);
        }
    }
    //matrix->print_system();
    matrix->triangle();
    matrix->do_solution();
    double * sol = matrix->get_solution();
    for(i = 0; i < xValues.size(); i++) {
        yValues.push_back(sol[i]);
    }
}

void Equation::doubleSolution() {
    matrix = new gauss((int) xSteps.size() * 2 + 1);
    matrix->reset();
    double tempPoint = BC[0].getPoint();
    int BCPoint = 0;
    int i = 0;
    for(i = 0; i < xSteps.size() * 2; i += 2) {
        double step = xSteps[i / 2];

        int j = i + 1;
        int k = i + 2;

        matrix->into_matrix(i,i,-7 * k2 / (3 * step) - k1 / 2 + 2 * k0 * step / 15);
        matrix->into_matrix(i,j, 8 * k2 / (3 * step) + 2 * k1 / 3 + k0 * step / 15);
        matrix->into_matrix(i,k, -k2 / (3 * step) - k1 / 6 - k0 * step / 30);

        matrix->into_matrix(j,i, 8 * k2 / (3 * step) - 2 * k1 / 3 + k0 * step / 15);
        matrix->into_matrix(j,j, -16 * k2 / (3 * step) + 8 * k0 * step / 15);
        matrix->into_matrix(j,k, 8 * k2 / (3 * step) + 2 * k1 / 3 + k0 * step / 15);

        matrix->into_matrix(k,i, -k2 / (3 * step) + k1 / 6 - k0 * step / 30);
        matrix->into_matrix(k,j, 8 * k2 / (3 * step) - 2 * k1 / 3 + k0 * step / 15);
        matrix->into_matrix(k,k, -7 * k2 / (3 * step) + k1 / 2 + 2 * k0 * step /15);

        matrix->into_constants(i, -cons * step / 6);
        matrix->into_constants(j, -2 * cons * step / 3);
        matrix->into_constants(k, -cons * step / 6);

        if(BCPoint < BC.size() && tempPoint >= BC[BCPoint].getPoint() - DIAP) {
            if(BC[BCPoint].getType() == 1) {
                matrix->into_constants(i, k2 * BC[BCPoint].getValue());
                BCPoint++;
            } else if(BC[BCPoint].getType() == 0) {
                matrix->clearStr(i);
                matrix->into_matrix(i,i,1) ;
                matrix->into_constants(i, BC[BCPoint].getValue());
                BCPoint++;
            } else {
                matrix->into_matrix(i, i, - k2);
                BCPoint++;
            }
        }

        xValues.push_back(tempPoint);
        xValues.push_back(tempPoint + step / 2);
        tempPoint += step;
    }
    xValues.push_back(tempPoint);
    if(BCPoint < BC.size() && tempPoint >= BC[BCPoint].getPoint() - DIAP) {
        if(BC[BCPoint].getType() == 1) {
            matrix->into_constants(i, -k2*BC[BCPoint].getValue());
        } else if(BC[BCPoint].getType() == 0) {
            matrix->clearStr(i);
            matrix->into_matrix(i,i,1) ;
            matrix->into_constants(i, BC[BCPoint].getValue());
        } else {
            matrix->into_matrix(i, i, k2);
        }
    }
    //matrix->print_system();
    matrix->triangle();
    matrix->do_solution();
    double * sol = matrix->get_solution();
    for(i = 0; i < xValues.size(); i++) {
        yValues.push_back(sol[i]);
    }
}

std::vector<double> Equation::getXValues() {
    return xValues;
}

std::vector<double> Equation::getYValues() {
    return yValues;
}
