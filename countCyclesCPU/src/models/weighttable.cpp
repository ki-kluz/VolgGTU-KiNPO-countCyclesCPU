#include "weighttable.h"


WeightTable::WeightTable() {

}

int WeightTable::getCost(WeightKey key) const {
    return 0;   // Заглушка
}

int WeightTable::getOperationCost(ExprNodeType type, DataType operType) const {
    return 0;   // Заглушка
}

int WeightTable::getConvertCost(DataType leftType, DataType rightType) const {
    return 0;   // Заглушка
}

bool WeightTable::addUserWeight(WeightKey key, int cost) {
    return false;   // Заглушка
}

void WeightTable::setDefaultWeights() {
    // Заглушка
}

WeightTable WeightTable::getDefaultWeights() {
    return WeightTable();
}
