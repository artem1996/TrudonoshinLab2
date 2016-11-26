#include "unevenstep.h"

UnevenStep::UnevenStep()
{

}

UnevenStep::UnevenStep(int tNumSteps, double tStepSize, int tDiapNumber) {
    numSteps = tNumSteps;
    stepSize = tStepSize;
    diapNumber = tDiapNumber;
}

int UnevenStep::getNumSteps() {
    return numSteps;
}

double UnevenStep::getStepSize() {
    return stepSize;
}

int UnevenStep::getDiapNumber() {
    return diapNumber;
}

void UnevenStep::setNumSteps(int tNumSteps) {
    numSteps = tNumSteps;
}

void UnevenStep::setStepSize(double tStepSize) {
    stepSize = tStepSize;
}

void UnevenStep::setDiapNumber(int tDiapNumber) {
    diapNumber = tDiapNumber;
}

bool operator<(const UnevenStep &first, const UnevenStep &second) {
    return (first.diapNumber < second.diapNumber);
}

std::ostream &operator<<(std::ostream &out, UnevenStep &US) {
    out << US.numSteps << '\t' << US.stepSize << '\t' << US.diapNumber << '\n';
    return out;
}
