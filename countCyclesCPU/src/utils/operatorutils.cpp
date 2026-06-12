#include "operatorutils.h"


namespace operator_utils
{
    bool checkSupportedOperation(ExprNodeType op, DataType left, DataType right, QSet<Error>& errors) {
        bool isValid = true;

        // Примечание: инкремент(++_ и _++)/декремент(--_ и _--) ОШИБКА для типа BOOL
        if (op == NODE_PREF_INC || op == NODE_PREF_DEC || op == NODE_POST_INC || op == NODE_POST_DEC) {
            if (left == TYPE_BOOL) {
                Error err;
                err.setType(ERR_UNSUPPORTED_OPERATION_FOR_TYPE);
                errors.insert(err);
                isValid = false;
            }
        }
        // Примечание: битовые операции и остаток от деления ТОЛЬКО для целых чисел
        else if (op == NODE_REMAINDER || op == NODE_REMAIN_EQUAL || op == NODE_BIT_AND ||
                 op == NODE_BIT_OR || op == NODE_BIT_XOR || op == NODE_BIT_NOT ||
                 op == NODE_SHIFT_LEFT || op == NODE_SHIFT_RIGHT) {

            static const QSet<DataType> integralTypes{
                TYPE_CHAR, TYPE_SHORT, TYPE_INT, TYPE_LONG, TYPE_LLONG
            };
            bool isLeftIntegral  = integralTypes.contains(left);
            bool isRightIntegral = integralTypes.contains(right);

            if (!isLeftIntegral || (right != TYPE_UNKNOWN && !isRightIntegral)) {
                Error err;
                err.setType(ERR_UNSUPPORTED_OPERATION_FOR_TYPE);
                errors.insert(err);
                isValid = false;
            }
        }
        return isValid;
    }

    bool checkNarrowingConversion(ExprNodeType op, DataType left, DataType right, QSet<Error>& errors) {
        // Примечание: сужающее преобразование, если правый тип обладает большей размерностью, чем левый
        if (op == NODE_ASSIGNMENT || op == NODE_PLUS_EQUAL || op == NODE_MINUS_EQUAL ||
            op == NODE_MULTI_EQUAL || op == NODE_DIV_EQUAL || op == NODE_REMAIN_EQUAL) {

            if (right > left) { // Опираемся на порядок в enum DataType
                Error err;
                err.setType(ERR_NARROWING_CONVERSION);
                errors.insert(err);
                return false;
            }
        }
        return true;
    }

    bool checkMaxCostLimit(int totalCost, QSet<Error>& errors) {
        if (totalCost > 10000) {
            Error err;
            err.setType(ERR_MAX_COST_EXCEEDED);
            errors.insert(err);
            return false;
        }
        return true;
    }
}
