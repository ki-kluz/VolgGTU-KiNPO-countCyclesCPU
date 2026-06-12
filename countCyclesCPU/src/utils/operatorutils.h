#ifndef OPERATORUTILS_H
#define OPERATORUTILS_H

#include <QSet>

#include "../enums/ExprNodeType.h"
#include "../enums/DataType.h"
#include "../models/error.h"


namespace operator_utils
{
    // Проверка на недопустимые операции (ERR_UNSUPPORTED_OPERATION_FOR_TYPE)
    bool checkSupportedOperation(ExprNodeType op, DataType left, DataType right, QSet<Error>& errors);

    // Проверка на сужающее преобразование (ERR_NARROWING_CONVERSION)
    bool checkNarrowingConversion(ExprNodeType op, DataType left, DataType right, QSet<Error>& errors);

    // Проверка на превышение лимита стоимости (ERR_MAX_COST_EXCEEDED)
    bool checkMaxCostLimit(int totalCost, QSet<Error>& errors);
}

#endif // OPERATORUTILS_H
