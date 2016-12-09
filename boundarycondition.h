#ifndef BOUNDARYCONDITION_H
#define BOUNDARYCONDITION_H
#include <iostream>


class BoundaryCondition
{
    int bType;
    double point;
    double value;
public:
    BoundaryCondition(int, double, double);
    BoundaryCondition();

    void setType(int);
    void setPoint(double);
    void setValue(double);

    int getType();
    double getPoint();
    double getValue();

    friend bool operator<(const BoundaryCondition &first, const BoundaryCondition &second);
    friend std::ostream &operator<<(std::ostream &out, BoundaryCondition &BC);
};

#endif // BOUNDARYCONDITION_H
