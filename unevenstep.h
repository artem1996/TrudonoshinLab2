#ifndef UNEVENSTEP_H
#define UNEVENSTEP_H
#include <iostream>


class UnevenStep
{
    int numSteps;
    double stepSize;
    int diapNumber;
public:
    UnevenStep();
    UnevenStep(int tNumSteps, double tStepSize, int tDiapNumber);
    int getNumSteps();
    double getStepSize();
    int getDiapNumber();
    void setNumSteps(int tNumSteps);
    void setStepSize(double tStepSize);
    void setDiapNumber(int tDiapNumber);

    friend bool operator<(const UnevenStep &first, const UnevenStep &second);
    friend std::ostream &operator<<(std::ostream &out, UnevenStep &US);
};

#endif // UNEVENSTEP_H
