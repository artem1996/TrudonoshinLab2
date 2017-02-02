#include <iostream>
#include <fstream>
#include <vector>
#include "boundarycondition.h"
#include "equation.h"

int main() {

    ofstream myFile("myPlot.txt");
    ofstream plotInstruction("gnuPlot.gnuplot");

    double k2 = 5;
    double k1 = -6;
    double k0 = 0;
    double cons = 7;
    double xLeft = 0, xRight = 9;
    double yLeft = 10, yRight = 15;

    std::vector<BoundaryCondition> BC;
    BC.push_back(BoundaryCondition(0, xLeft, yLeft));
    BC.push_back(BoundaryCondition(0, xRight, yRight));

    Equation eq(k2, k1, k0, cons);

    eq.setBC(BC);
    vector<UnevenStep> unevenStep;
    unevenStep.push_back(UnevenStep(20, 0.45));
    //unevenStep.push_back(UnevenStep(1, 6.0));
    //unevenStep.push_back(UnevenStep(30, 0.1));
    eq.setStep(unevenStep);
    eq.solution();
    //eq.doubleSolution();

    std::vector<double> xVal = eq.getXValues();
    std::vector<double> yVal = eq.getYValues();

    for(int i = 0; i < xVal.size(); i++) {
        double znam = 6.0*(exp(54.0/5.0)-1);
        double chisl = (-7*xVal[i] - 33*exp(6*xVal[i]/5)+exp(54.0/5)*(7*xVal[i]+60)-27);
        double temp = chisl/znam;
        myFile << xVal[i] << '\t' << yVal[i] << '\t' << temp << '\t' << fabs(yVal[i] - temp) << '\n';
    }

    myFile.close();

    plotInstruction << "plot \"./myPlot.txt\" using 1:2 with lines, \"./myPlot.txt\" using 1:3 with lines;\n";
    plotInstruction.close();

    system("gnuplot -p gnuPlot.gnuplot;");

    return 0;
}