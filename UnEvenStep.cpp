//
// Created by note on 02.02.17.
//

#include "UnEvenStep.h"

UnevenStep::UnevenStep()
{

}

UnevenStep::UnevenStep(int tNumSteps, double tStepSize) {
    numSteps = tNumSteps;
    stepSize = tStepSize;
}

int UnevenStep::getNumSteps() {
    return numSteps;
}

double UnevenStep::getStepSize() {
    return stepSize;
}

