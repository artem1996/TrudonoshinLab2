#include "equation.h"
#include "iostream"
#define DIAP 0.001


Equation::Equation(double tK2, double tK1, double tK0, double tCons, double tXLeft, double tXRight)
{
    k2 = tK2;
    k1 = tK1;
    k0 = tK0;
    cons = tCons;
    xLeft = tXLeft;
    xRight = tXRight;
}

void Equation::simpleStep(int steps) {
    //std::cerr << xRight << ' ' << xLeft << ' ' << steps << '\n';
    double step = (xRight - xLeft) / steps;
    //std::cerr << step << '\n';
    for(int i = 0; i < steps; i++) {
        xSteps.append(step);
    }
}

void Equation::difficultStep(QVector<UnevenStep> steps) {
    for(int i = 0; i < steps.size(); i++) {
        for(int j = 0; i < steps[i].getNumSteps(); j++)
            xSteps.append(steps[i].getStepSize());
    }
}

void Equation::prepSolution() {
    matrix = new gauss(xSteps.size() + 1);
}

void Equation::setBC(QVector<BoundaryCondition> tBC) {
    BC = tBC;
    for(int i = 0; i < BC.size(); i++) {
        std::cout << BC[i];
    }
}

void Equation::solution() {
    matrix->reset();
    double tempPoint = xLeft;
    int BCPoint = 0;
    int i = 0;
    for(i = 0; i < xSteps.size(); i++) {
        xValues.push_back(tempPoint);
        //std::cerr << i << " ";
        //std::cout << BCPoint << " from " << BCCount << " next value " << BC[BCPoint].getValue() << " type " << BC[BCPoint].getType() << "\n";
        double step = xSteps[i];
        int j = i + 1;

        matrix->into_matrix(i,i,k2/step) ;
        matrix->into_matrix(i,j,-k2/step)  ;
        matrix->into_matrix(j,i,-k2/step) ;
        matrix->into_matrix(j,j,k2/step) ;

        matrix->into_matrix(i,i,-k1/2) ;
        matrix->into_matrix(i,j,-k1/2)  ;
        matrix->into_matrix(j,i,k1/2) ;
        matrix->into_matrix(j,j,k1/2) ;

        matrix->into_matrix(i,i,k0*step/3) ;
        matrix->into_matrix(i,j,k0*step/6)  ;
        matrix->into_matrix(j,i,k0*step/6) ;
        matrix->into_matrix(j,j,k0*step/3) ;

        matrix->into_constants(i, cons*step/2);
        matrix->into_constants(j, cons*step/2);

        if(BCPoint < BC.size() && tempPoint >= BC[BCPoint].getValue() - DIAP) {
            if(BC[BCPoint].getType()) {
                matrix->into_constants(i, -k2*BC[BCPoint].getValue());
                BCPoint++;
            } else {
                matrix->clearStr(i);
                matrix->into_matrix(i,i,1) ;
                //std::cout << "lol \n";
                matrix->into_constants(i, BC[BCPoint].getValue());
                BCPoint++;
            }
        }


        //std::cout << tempPoint << '\n';
        tempPoint += step;
    }
    xValues.push_back(tempPoint);
    if(BCPoint < BC.size() && tempPoint >= BC[BCPoint].getValue() - DIAP) {
        if(BC[BCPoint].getType()) {
            matrix->into_constants(i, -k2*BC[BCPoint].getValue());
            BCPoint++;
        } else {
            matrix->clearStr(i);
            matrix->into_matrix(i,i,1) ;
            //std::cout << "lol \n";
            matrix->into_constants(i, BC[BCPoint].getValue());
            BCPoint++;
        }
    }

    matrix->triangle();
    matrix->do_solution();
    double * sol = matrix->get_solution();
    for(i = 0; i < xValues.size(); i++) {
        yValues.push_back(sol[i]);
    }
    matrix->print_system();
}

QVector<double> Equation::getXValues() {
    return xValues;
}

QVector<double> Equation::getYValues() {
    return yValues;
}
