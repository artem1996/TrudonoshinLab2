#include "boundarycondition.h"

BoundaryCondition::BoundaryCondition()
{

}

BoundaryCondition::BoundaryCondition(bool tType, double tPoint, double tValue)
{
    bType = tType;
    point = tPoint;
    value = tValue;
}

void BoundaryCondition::setType(bool tType) {
    bType = tType;
}

void BoundaryCondition::setPoint(double tPoint) {
    point = tPoint;
}

void BoundaryCondition::setValue(double tValue) {
    value = tValue;
}

bool BoundaryCondition::getType() {
    return bType;
}

double BoundaryCondition::getPoint() {
    return point;
}

double BoundaryCondition::getValue() {
    return value;
}

bool operator<(const BoundaryCondition &first, const BoundaryCondition &second) {
    return (first.point < second.point);
}

std::ostream &operator<<(std::ostream &out, BoundaryCondition &BC) {
    out << BC.bType << '\t' << BC.point << '\t' << BC.value << '\n';
    return out;
}
