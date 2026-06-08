#ifndef WEIGHTTABLE_H
#define WEIGHTTABLE_H

#include <QMap>

#include "../enums/DataType.h"
#include "../enums/ExprNodeType.h"
#include "../models/weightkey.h"


class WeightTable
{
public:
    WeightTable();

    int getCost(WeightKey key) const;
    int getOperationCost(ExprNodeType type, DataType operType) const;
    int getConvertCost(DataType leftType, DataType rightType) const;

    bool addUserWeight(WeightKey key, int cost);

    static WeightTable getDefaultWeights();

private:
    QMap<WeightKey, int> defaultWeights;    // (по умолчанию)
    QMap<WeightKey, int> userWeights;       // (пользовательская)

    void setDefaultWeights();
};

#endif // WEIGHTTABLE_H
