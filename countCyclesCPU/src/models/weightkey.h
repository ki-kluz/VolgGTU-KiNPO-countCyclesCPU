#ifndef WEIGHTKEY_H
#define WEIGHTKEY_H

#include "../enums/DataType.h"
#include "../enums/ExprNodeType.h"


struct WeightKey
{
    WeightKey(ExprNodeType op, DataType left, DataType right);

    ExprNodeType op;        // Узел дерева (Plus, Minus и тд)
    DataType leftType;      // Тип данных левого операнда
    DataType rightType;     // Тип данных правого операнда

    bool operator<(const WeightKey& other) const;
};

#endif // WEIGHTKEY_H
