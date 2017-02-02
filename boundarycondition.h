//
// Created by note on 02.02.17.
//

#ifndef ARINATRUD2_BOUNDARYCONDITION_H
#define ARINATRUD2_BOUNDARYCONDITION_H

#include <iostream>


class BoundaryCondition
{
    int bType;
    double point;
    double value;
public:
    BoundaryCondition(int, double, double);
    BoundaryCondition();

    int getType();
    double getPoint();
    double getValue();

    friend bool operator<(const BoundaryCondition &first, const BoundaryCondition &second);
    friend std::ostream &operator<<(std::ostream &out, BoundaryCondition &BC);
};

#endif //ARINATRUD2_BOUNDARYCONDITION_H
