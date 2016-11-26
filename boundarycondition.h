#ifndef BOUNDARYCONDITION_H
#define BOUNDARYCONDITION_H
#include <iostream>


class BoundaryCondition
{
    bool bType;
    double point;
    double value;
public:
    BoundaryCondition(bool, double, double);
    BoundaryCondition();

    void setType(bool);
    void setPoint(double);
    void setValue(double);

    bool getType();
    double getPoint();
    double getValue();

    friend bool operator<(const BoundaryCondition &first, const BoundaryCondition &second);
    friend std::ostream &operator<<(std::ostream &out, BoundaryCondition &BC);
};

#endif // BOUNDARYCONDITION_H
