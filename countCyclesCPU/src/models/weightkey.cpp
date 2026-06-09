#include "weightkey.h"


WeightKey::WeightKey(ExprNodeType op, DataType left, DataType right) {
    this->op = op;
    leftType = left;
    rightType = right;
}

bool WeightKey::operator<(const WeightKey& other) const {
    if (op != other.op) {
        return op < other.op;
    }
    if (leftType != other.leftType) {
        return leftType < other.leftType;
    }
    return rightType < other.rightType;
}
