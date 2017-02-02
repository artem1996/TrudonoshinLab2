//
// Created by note on 02.02.17.
//

#ifndef ARINATRUD2_UNEVENSTEP_H
#define ARINATRUD2_UNEVENSTEP_H

#include <iostream>


class UnevenStep
{
    int numSteps;
    double stepSize;
public:
    UnevenStep();
    UnevenStep(int tNumSteps, double tStepSize);
    int getNumSteps();
    double getStepSize();
};


#endif //ARINATRUD2_UNEVENSTEP_H
