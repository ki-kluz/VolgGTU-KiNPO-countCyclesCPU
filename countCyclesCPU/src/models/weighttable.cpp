#include "weighttable.h"


WeightTable::WeightTable() {
    // Инициализируем таблицу весов по умолчанию
    setDefaultWeights();
}

int WeightTable::getCost(WeightKey key) const {
    if (userWeights.contains(key))
        return userWeights.value(key);

    if (defaultWeights.contains(key))
        return defaultWeights.value(key);

    return 0;
}

int WeightTable::getOperationCost(ExprNodeType type, DataType operType) const {
    WeightKey key(type, operType, operType);
    return getCost(key);
}

int WeightTable::getConvertCost(DataType leftType, DataType rightType) const {
    WeightKey key(NODE_CONVERT, leftType, rightType);
    return getCost(key);
}

bool WeightTable::addUserWeight(WeightKey key, int cost) {
    if (userWeights.contains(key)) {
        return false;
    }
    userWeights.insert(key, cost);
    return true;
}

WeightTable WeightTable::getDefaultWeights() {
    return WeightTable();
}

void WeightTable::setDefaultWeights() {

    // ===== Веса операций =====

    // +
    defaultWeights[WeightKey(NODE_PLUS, TYPE_CHAR, TYPE_CHAR)] = 1;
    defaultWeights[WeightKey(NODE_PLUS, TYPE_SHORT, TYPE_SHORT)] = 1;
    defaultWeights[WeightKey(NODE_PLUS, TYPE_INT, TYPE_INT)] = 1;
    defaultWeights[WeightKey(NODE_PLUS, TYPE_LONG, TYPE_LONG)] = 2;
    defaultWeights[WeightKey(NODE_PLUS, TYPE_LLONG, TYPE_LLONG)] = 2;
    defaultWeights[WeightKey(NODE_PLUS, TYPE_FLOAT, TYPE_FLOAT)] = 3;
    defaultWeights[WeightKey(NODE_PLUS, TYPE_DOUBLE, TYPE_DOUBLE)] = 3;

    // -
    defaultWeights[WeightKey(NODE_MINUS, TYPE_CHAR, TYPE_CHAR)] = 1;
    defaultWeights[WeightKey(NODE_MINUS, TYPE_SHORT, TYPE_SHORT)] = 1;
    defaultWeights[WeightKey(NODE_MINUS, TYPE_INT, TYPE_INT)] = 1;
    defaultWeights[WeightKey(NODE_MINUS, TYPE_LONG, TYPE_LONG)] = 2;
    defaultWeights[WeightKey(NODE_MINUS, TYPE_LLONG, TYPE_LLONG)] = 2;
    defaultWeights[WeightKey(NODE_MINUS, TYPE_FLOAT, TYPE_FLOAT)] = 3;
    defaultWeights[WeightKey(NODE_MINUS, TYPE_DOUBLE, TYPE_DOUBLE)] = 3;

    // *
    defaultWeights[WeightKey(NODE_MULTIPLICATION, TYPE_CHAR, TYPE_CHAR)] = 4;
    defaultWeights[WeightKey(NODE_MULTIPLICATION, TYPE_SHORT, TYPE_SHORT)] = 4;
    defaultWeights[WeightKey(NODE_MULTIPLICATION, TYPE_INT, TYPE_INT)] = 4;
    defaultWeights[WeightKey(NODE_MULTIPLICATION, TYPE_LONG, TYPE_LONG)] = 6;
    defaultWeights[WeightKey(NODE_MULTIPLICATION, TYPE_LLONG, TYPE_LLONG)] = 6;
    defaultWeights[WeightKey(NODE_MULTIPLICATION, TYPE_FLOAT, TYPE_FLOAT)] = 5;
    defaultWeights[WeightKey(NODE_MULTIPLICATION, TYPE_DOUBLE, TYPE_DOUBLE)] = 5;

    // /
    defaultWeights[WeightKey(NODE_DIVISION, TYPE_CHAR, TYPE_CHAR)] = 40;
    defaultWeights[WeightKey(NODE_DIVISION, TYPE_SHORT, TYPE_SHORT)] = 40;
    defaultWeights[WeightKey(NODE_DIVISION, TYPE_INT, TYPE_INT)] = 40;
    defaultWeights[WeightKey(NODE_DIVISION, TYPE_LONG, TYPE_LONG)] = 60;
    defaultWeights[WeightKey(NODE_DIVISION, TYPE_LLONG, TYPE_LLONG)] = 60;
    defaultWeights[WeightKey(NODE_DIVISION, TYPE_FLOAT, TYPE_FLOAT)] = 20;
    defaultWeights[WeightKey(NODE_DIVISION, TYPE_DOUBLE, TYPE_DOUBLE)] = 20;

    // //
    defaultWeights[WeightKey(NODE_INTEGER_DIVISION, TYPE_CHAR, TYPE_CHAR)] = 40;
    defaultWeights[WeightKey(NODE_INTEGER_DIVISION, TYPE_SHORT, TYPE_SHORT)] = 40;
    defaultWeights[WeightKey(NODE_INTEGER_DIVISION, TYPE_INT, TYPE_INT)] = 40;
    defaultWeights[WeightKey(NODE_INTEGER_DIVISION, TYPE_LONG, TYPE_LONG)] = 60;
    defaultWeights[WeightKey(NODE_INTEGER_DIVISION, TYPE_LLONG, TYPE_LLONG)] = 60;

    // %
    defaultWeights[WeightKey(NODE_REMAINDER, TYPE_CHAR, TYPE_CHAR)] = 40;
    defaultWeights[WeightKey(NODE_REMAINDER, TYPE_SHORT, TYPE_SHORT)] = 40;
    defaultWeights[WeightKey(NODE_REMAINDER, TYPE_INT, TYPE_INT)] = 40;
    defaultWeights[WeightKey(NODE_REMAINDER, TYPE_LONG, TYPE_LONG)] = 60;
    defaultWeights[WeightKey(NODE_REMAINDER, TYPE_LLONG, TYPE_LLONG)] = 60;

    // ++
    defaultWeights[WeightKey(NODE_PREF_INC, TYPE_CHAR, TYPE_CHAR)] = 1;
    defaultWeights[WeightKey(NODE_PREF_INC, TYPE_SHORT, TYPE_SHORT)] = 1;
    defaultWeights[WeightKey(NODE_PREF_INC, TYPE_INT, TYPE_INT)] = 1;
    defaultWeights[WeightKey(NODE_PREF_INC, TYPE_LONG, TYPE_LONG)] = 1;
    defaultWeights[WeightKey(NODE_PREF_INC, TYPE_LLONG, TYPE_LLONG)] = 1;
    defaultWeights[WeightKey(NODE_PREF_INC, TYPE_FLOAT, TYPE_FLOAT)] = 3;
    defaultWeights[WeightKey(NODE_PREF_INC, TYPE_DOUBLE, TYPE_DOUBLE)] = 3;

    defaultWeights[WeightKey(NODE_POST_INC, TYPE_CHAR, TYPE_CHAR)] = 1;
    defaultWeights[WeightKey(NODE_POST_INC, TYPE_SHORT, TYPE_SHORT)] = 1;
    defaultWeights[WeightKey(NODE_POST_INC, TYPE_INT, TYPE_INT)] = 1;
    defaultWeights[WeightKey(NODE_POST_INC, TYPE_LONG, TYPE_LONG)] = 1;
    defaultWeights[WeightKey(NODE_POST_INC, TYPE_LLONG, TYPE_LLONG)] = 1;
    defaultWeights[WeightKey(NODE_POST_INC, TYPE_FLOAT, TYPE_FLOAT)] = 3;
    defaultWeights[WeightKey(NODE_POST_INC, TYPE_DOUBLE, TYPE_DOUBLE)] = 3;

    // --
    defaultWeights[WeightKey(NODE_PREF_DEC, TYPE_CHAR, TYPE_CHAR)] = 1;
    defaultWeights[WeightKey(NODE_PREF_DEC, TYPE_SHORT, TYPE_SHORT)] = 1;
    defaultWeights[WeightKey(NODE_PREF_DEC, TYPE_INT, TYPE_INT)] = 1;
    defaultWeights[WeightKey(NODE_PREF_DEC, TYPE_LONG, TYPE_LONG)] = 1;
    defaultWeights[WeightKey(NODE_PREF_DEC, TYPE_LLONG, TYPE_LLONG)] = 1;
    defaultWeights[WeightKey(NODE_PREF_DEC, TYPE_FLOAT, TYPE_FLOAT)] = 3;
    defaultWeights[WeightKey(NODE_PREF_DEC, TYPE_DOUBLE, TYPE_DOUBLE)] = 3;

    defaultWeights[WeightKey(NODE_POST_DEC, TYPE_CHAR, TYPE_CHAR)] = 1;
    defaultWeights[WeightKey(NODE_POST_DEC, TYPE_SHORT, TYPE_SHORT)] = 1;
    defaultWeights[WeightKey(NODE_POST_DEC, TYPE_INT, TYPE_INT)] = 1;
    defaultWeights[WeightKey(NODE_POST_DEC, TYPE_LONG, TYPE_LONG)] = 1;
    defaultWeights[WeightKey(NODE_POST_DEC, TYPE_LLONG, TYPE_LLONG)] = 1;
    defaultWeights[WeightKey(NODE_POST_DEC, TYPE_FLOAT, TYPE_FLOAT)] = 3;
    defaultWeights[WeightKey(NODE_POST_DEC, TYPE_DOUBLE, TYPE_DOUBLE)] = 3;

    // &&
    defaultWeights[WeightKey(NODE_LOG_AND, TYPE_BOOL, TYPE_BOOL)] = 2;

    // ||
    defaultWeights[WeightKey(NODE_LOG_OR, TYPE_BOOL, TYPE_BOOL)] = 2;

    // !
    defaultWeights[WeightKey(NODE_LOG_NOT, TYPE_BOOL, TYPE_BOOL)] = 1;

    // Унарный минус (-x)
    defaultWeights[WeightKey(NODE_NEGATIVE, TYPE_CHAR, TYPE_CHAR)] = 1;
    defaultWeights[WeightKey(NODE_NEGATIVE, TYPE_SHORT, TYPE_SHORT)] = 1;
    defaultWeights[WeightKey(NODE_NEGATIVE, TYPE_INT, TYPE_INT)] = 1;
    defaultWeights[WeightKey(NODE_NEGATIVE, TYPE_LONG, TYPE_LONG)] = 2;
    defaultWeights[WeightKey(NODE_NEGATIVE, TYPE_LLONG, TYPE_LLONG)] = 2;
    defaultWeights[WeightKey(NODE_NEGATIVE, TYPE_FLOAT, TYPE_FLOAT)] = 3;
    defaultWeights[WeightKey(NODE_NEGATIVE, TYPE_DOUBLE, TYPE_DOUBLE)] = 3;

    // ==
    defaultWeights[WeightKey(NODE_EQUAL, TYPE_BOOL, TYPE_BOOL)] = 1;
    defaultWeights[WeightKey(NODE_EQUAL, TYPE_CHAR, TYPE_CHAR)] = 1;
    defaultWeights[WeightKey(NODE_EQUAL, TYPE_SHORT, TYPE_SHORT)] = 1;
    defaultWeights[WeightKey(NODE_EQUAL, TYPE_INT, TYPE_INT)] = 1;
    defaultWeights[WeightKey(NODE_EQUAL, TYPE_LONG, TYPE_LONG)] = 2;
    defaultWeights[WeightKey(NODE_EQUAL, TYPE_LLONG, TYPE_LLONG)] = 2;
    defaultWeights[WeightKey(NODE_EQUAL, TYPE_FLOAT, TYPE_FLOAT)] = 3;
    defaultWeights[WeightKey(NODE_EQUAL, TYPE_DOUBLE, TYPE_DOUBLE)] = 3;

    // !=
    defaultWeights[WeightKey(NODE_NOT_EQUAL, TYPE_BOOL, TYPE_BOOL)] = 1;
    defaultWeights[WeightKey(NODE_NOT_EQUAL, TYPE_CHAR, TYPE_CHAR)] = 1;
    defaultWeights[WeightKey(NODE_NOT_EQUAL, TYPE_SHORT, TYPE_SHORT)] = 1;
    defaultWeights[WeightKey(NODE_NOT_EQUAL, TYPE_INT, TYPE_INT)] = 1;
    defaultWeights[WeightKey(NODE_NOT_EQUAL, TYPE_LONG, TYPE_LONG)] = 2;
    defaultWeights[WeightKey(NODE_NOT_EQUAL, TYPE_LLONG, TYPE_LLONG)] = 2;
    defaultWeights[WeightKey(NODE_NOT_EQUAL, TYPE_FLOAT, TYPE_FLOAT)] = 3;
    defaultWeights[WeightKey(NODE_NOT_EQUAL, TYPE_DOUBLE, TYPE_DOUBLE)] = 3;

    // <
    defaultWeights[WeightKey(NODE_LESS, TYPE_BOOL, TYPE_BOOL)] = 1;
    defaultWeights[WeightKey(NODE_LESS, TYPE_CHAR, TYPE_CHAR)] = 1;
    defaultWeights[WeightKey(NODE_LESS, TYPE_SHORT, TYPE_SHORT)] = 1;
    defaultWeights[WeightKey(NODE_LESS, TYPE_INT, TYPE_INT)] = 1;
    defaultWeights[WeightKey(NODE_LESS, TYPE_LONG, TYPE_LONG)] = 2;
    defaultWeights[WeightKey(NODE_LESS, TYPE_LLONG, TYPE_LLONG)] = 2;
    defaultWeights[WeightKey(NODE_LESS, TYPE_FLOAT, TYPE_FLOAT)] = 3;
    defaultWeights[WeightKey(NODE_LESS, TYPE_DOUBLE, TYPE_DOUBLE)] = 3;

    // >
    defaultWeights[WeightKey(NODE_GREATER, TYPE_BOOL, TYPE_BOOL)] = 1;
    defaultWeights[WeightKey(NODE_GREATER, TYPE_CHAR, TYPE_CHAR)] = 1;
    defaultWeights[WeightKey(NODE_GREATER, TYPE_SHORT, TYPE_SHORT)] = 1;
    defaultWeights[WeightKey(NODE_GREATER, TYPE_INT, TYPE_INT)] = 1;
    defaultWeights[WeightKey(NODE_GREATER, TYPE_LONG, TYPE_LONG)] = 2;
    defaultWeights[WeightKey(NODE_GREATER, TYPE_LLONG, TYPE_LLONG)] = 2;
    defaultWeights[WeightKey(NODE_GREATER, TYPE_FLOAT, TYPE_FLOAT)] = 3;
    defaultWeights[WeightKey(NODE_GREATER, TYPE_DOUBLE, TYPE_DOUBLE)] = 3;

    // <=
    defaultWeights[WeightKey(NODE_LESS_EQUAL, TYPE_BOOL, TYPE_BOOL)] = 1;
    defaultWeights[WeightKey(NODE_LESS_EQUAL, TYPE_CHAR, TYPE_CHAR)] = 1;
    defaultWeights[WeightKey(NODE_LESS_EQUAL, TYPE_SHORT, TYPE_SHORT)] = 1;
    defaultWeights[WeightKey(NODE_LESS_EQUAL, TYPE_INT, TYPE_INT)] = 1;
    defaultWeights[WeightKey(NODE_LESS_EQUAL, TYPE_LONG, TYPE_LONG)] = 2;
    defaultWeights[WeightKey(NODE_LESS_EQUAL, TYPE_LLONG, TYPE_LLONG)] = 2;
    defaultWeights[WeightKey(NODE_LESS_EQUAL, TYPE_FLOAT, TYPE_FLOAT)] = 3;
    defaultWeights[WeightKey(NODE_LESS_EQUAL, TYPE_DOUBLE, TYPE_DOUBLE)] = 3;

    // >=
    defaultWeights[WeightKey(NODE_GREATER_EQUAL, TYPE_BOOL, TYPE_BOOL)] = 1;
    defaultWeights[WeightKey(NODE_GREATER_EQUAL, TYPE_CHAR, TYPE_CHAR)] = 1;
    defaultWeights[WeightKey(NODE_GREATER_EQUAL, TYPE_SHORT, TYPE_SHORT)] = 1;
    defaultWeights[WeightKey(NODE_GREATER_EQUAL, TYPE_INT, TYPE_INT)] = 1;
    defaultWeights[WeightKey(NODE_GREATER_EQUAL, TYPE_LONG, TYPE_LONG)] = 2;
    defaultWeights[WeightKey(NODE_GREATER_EQUAL, TYPE_LLONG, TYPE_LLONG)] = 2;
    defaultWeights[WeightKey(NODE_GREATER_EQUAL, TYPE_FLOAT, TYPE_FLOAT)] = 3;
    defaultWeights[WeightKey(NODE_GREATER_EQUAL, TYPE_DOUBLE, TYPE_DOUBLE)] = 3;

    // &
    defaultWeights[WeightKey(NODE_BIT_AND, TYPE_CHAR, TYPE_CHAR)] = 1;
    defaultWeights[WeightKey(NODE_BIT_AND, TYPE_SHORT, TYPE_SHORT)] = 1;
    defaultWeights[WeightKey(NODE_BIT_AND, TYPE_INT, TYPE_INT)] = 1;
    defaultWeights[WeightKey(NODE_BIT_AND, TYPE_LONG, TYPE_LONG)] = 2;
    defaultWeights[WeightKey(NODE_BIT_AND, TYPE_LLONG, TYPE_LLONG)] = 2;

    // |
    defaultWeights[WeightKey(NODE_BIT_OR, TYPE_CHAR, TYPE_CHAR)] = 1;
    defaultWeights[WeightKey(NODE_BIT_OR, TYPE_SHORT, TYPE_SHORT)] = 1;
    defaultWeights[WeightKey(NODE_BIT_OR, TYPE_INT, TYPE_INT)] = 1;
    defaultWeights[WeightKey(NODE_BIT_OR, TYPE_LONG, TYPE_LONG)] = 2;
    defaultWeights[WeightKey(NODE_BIT_OR, TYPE_LLONG, TYPE_LLONG)] = 2;

    // ^
    defaultWeights[WeightKey(NODE_BIT_XOR, TYPE_CHAR, TYPE_CHAR)] = 1;
    defaultWeights[WeightKey(NODE_BIT_XOR, TYPE_SHORT, TYPE_SHORT)] = 1;
    defaultWeights[WeightKey(NODE_BIT_XOR, TYPE_INT, TYPE_INT)] = 1;
    defaultWeights[WeightKey(NODE_BIT_XOR, TYPE_LONG, TYPE_LONG)] = 2;
    defaultWeights[WeightKey(NODE_BIT_XOR, TYPE_LLONG, TYPE_LLONG)] = 2;

    // ~
    defaultWeights[WeightKey(NODE_BIT_NOT, TYPE_CHAR, TYPE_CHAR)] = 1;
    defaultWeights[WeightKey(NODE_BIT_NOT, TYPE_SHORT, TYPE_SHORT)] = 1;
    defaultWeights[WeightKey(NODE_BIT_NOT, TYPE_INT, TYPE_INT)] = 1;
    defaultWeights[WeightKey(NODE_BIT_NOT, TYPE_LONG, TYPE_LONG)] = 2;
    defaultWeights[WeightKey(NODE_BIT_NOT, TYPE_LLONG, TYPE_LLONG)] = 2;

    // <<
    defaultWeights[WeightKey(NODE_SHIFT_LEFT, TYPE_CHAR, TYPE_CHAR)] = 1;
    defaultWeights[WeightKey(NODE_SHIFT_LEFT, TYPE_SHORT, TYPE_SHORT)] = 1;
    defaultWeights[WeightKey(NODE_SHIFT_LEFT, TYPE_INT, TYPE_INT)] = 1;
    defaultWeights[WeightKey(NODE_SHIFT_LEFT, TYPE_LONG, TYPE_LONG)] = 2;
    defaultWeights[WeightKey(NODE_SHIFT_LEFT, TYPE_LLONG, TYPE_LLONG)] = 2;

    // >>
    defaultWeights[WeightKey(NODE_SHIFT_RIGHT, TYPE_CHAR, TYPE_CHAR)] = 1;
    defaultWeights[WeightKey(NODE_SHIFT_RIGHT, TYPE_SHORT, TYPE_SHORT)] = 1;
    defaultWeights[WeightKey(NODE_SHIFT_RIGHT, TYPE_INT, TYPE_INT)] = 1;
    defaultWeights[WeightKey(NODE_SHIFT_RIGHT, TYPE_LONG, TYPE_LONG)] = 2;
    defaultWeights[WeightKey(NODE_SHIFT_RIGHT, TYPE_LLONG, TYPE_LLONG)] = 2;

    // =
    defaultWeights[WeightKey(NODE_ASSIGNMENT, TYPE_BOOL, TYPE_BOOL)] = 1;
    defaultWeights[WeightKey(NODE_ASSIGNMENT, TYPE_CHAR, TYPE_CHAR)] = 1;
    defaultWeights[WeightKey(NODE_ASSIGNMENT, TYPE_SHORT, TYPE_SHORT)] = 1;
    defaultWeights[WeightKey(NODE_ASSIGNMENT, TYPE_INT, TYPE_INT)] = 1;
    defaultWeights[WeightKey(NODE_ASSIGNMENT, TYPE_LONG, TYPE_LONG)] = 1;
    defaultWeights[WeightKey(NODE_ASSIGNMENT, TYPE_LLONG, TYPE_LLONG)] = 1;
    defaultWeights[WeightKey(NODE_ASSIGNMENT, TYPE_FLOAT, TYPE_FLOAT)] = 1;
    defaultWeights[WeightKey(NODE_ASSIGNMENT, TYPE_DOUBLE, TYPE_DOUBLE)] = 1;

    // +=
    defaultWeights[WeightKey(NODE_PLUS_EQUAL, TYPE_CHAR, TYPE_CHAR)] = 2;
    defaultWeights[WeightKey(NODE_PLUS_EQUAL, TYPE_SHORT, TYPE_SHORT)] = 2;
    defaultWeights[WeightKey(NODE_PLUS_EQUAL, TYPE_INT, TYPE_INT)] = 2;
    defaultWeights[WeightKey(NODE_PLUS_EQUAL, TYPE_LONG, TYPE_LONG)] = 3;
    defaultWeights[WeightKey(NODE_PLUS_EQUAL, TYPE_LLONG, TYPE_LLONG)] = 3;
    defaultWeights[WeightKey(NODE_PLUS_EQUAL, TYPE_FLOAT, TYPE_FLOAT)] = 4;
    defaultWeights[WeightKey(NODE_PLUS_EQUAL, TYPE_DOUBLE, TYPE_DOUBLE)] = 4;

    // -=
    defaultWeights[WeightKey(NODE_MINUS_EQUAL, TYPE_CHAR, TYPE_CHAR)] = 2;
    defaultWeights[WeightKey(NODE_MINUS_EQUAL, TYPE_SHORT, TYPE_SHORT)] = 2;
    defaultWeights[WeightKey(NODE_MINUS_EQUAL, TYPE_INT, TYPE_INT)] = 2;
    defaultWeights[WeightKey(NODE_MINUS_EQUAL, TYPE_LONG, TYPE_LONG)] = 3;
    defaultWeights[WeightKey(NODE_MINUS_EQUAL, TYPE_LLONG, TYPE_LLONG)] = 3;
    defaultWeights[WeightKey(NODE_MINUS_EQUAL, TYPE_FLOAT, TYPE_FLOAT)] = 4;
    defaultWeights[WeightKey(NODE_MINUS_EQUAL, TYPE_DOUBLE, TYPE_DOUBLE)] = 4;

    // *=
    defaultWeights[WeightKey(NODE_MULTI_EQUAL, TYPE_CHAR, TYPE_CHAR)] = 41;
    defaultWeights[WeightKey(NODE_MULTI_EQUAL, TYPE_SHORT, TYPE_SHORT)] = 41;
    defaultWeights[WeightKey(NODE_MULTI_EQUAL, TYPE_INT, TYPE_INT)] = 41;
    defaultWeights[WeightKey(NODE_MULTI_EQUAL, TYPE_LONG, TYPE_LONG)] = 61;
    defaultWeights[WeightKey(NODE_MULTI_EQUAL, TYPE_LLONG, TYPE_LLONG)] = 61;
    defaultWeights[WeightKey(NODE_MULTI_EQUAL, TYPE_FLOAT, TYPE_FLOAT)] = 21;
    defaultWeights[WeightKey(NODE_MULTI_EQUAL, TYPE_DOUBLE, TYPE_DOUBLE)] = 21;

    // /=
    defaultWeights[WeightKey(NODE_DIV_EQUAL, TYPE_CHAR, TYPE_CHAR)] = 41;
    defaultWeights[WeightKey(NODE_DIV_EQUAL, TYPE_SHORT, TYPE_SHORT)] = 41;
    defaultWeights[WeightKey(NODE_DIV_EQUAL, TYPE_INT, TYPE_INT)] = 41;
    defaultWeights[WeightKey(NODE_DIV_EQUAL, TYPE_LONG, TYPE_LONG)] = 61;
    defaultWeights[WeightKey(NODE_DIV_EQUAL, TYPE_LLONG, TYPE_LLONG)] = 61;
    defaultWeights[WeightKey(NODE_DIV_EQUAL, TYPE_FLOAT, TYPE_FLOAT)] = 21;
    defaultWeights[WeightKey(NODE_DIV_EQUAL, TYPE_DOUBLE, TYPE_DOUBLE)] = 21;

    // %=
    defaultWeights[WeightKey(NODE_REMAIN_EQUAL, TYPE_CHAR, TYPE_CHAR)] = 41;
    defaultWeights[WeightKey(NODE_REMAIN_EQUAL, TYPE_SHORT, TYPE_SHORT)] = 41;
    defaultWeights[WeightKey(NODE_REMAIN_EQUAL, TYPE_INT, TYPE_INT)] = 41;
    defaultWeights[WeightKey(NODE_REMAIN_EQUAL, TYPE_LONG, TYPE_LONG)] = 61;
    defaultWeights[WeightKey(NODE_REMAIN_EQUAL, TYPE_LLONG, TYPE_LLONG)] = 61;

    // ===== Веса преобразования типов =====

    // short, int, long, long long -> float
    defaultWeights[WeightKey(NODE_CONVERT, TYPE_SHORT, TYPE_FLOAT)] = 4;
    defaultWeights[WeightKey(NODE_CONVERT, TYPE_INT, TYPE_FLOAT)] = 4;
    defaultWeights[WeightKey(NODE_CONVERT, TYPE_LONG, TYPE_FLOAT)] = 4;
    defaultWeights[WeightKey(NODE_CONVERT, TYPE_LLONG, TYPE_FLOAT)] = 4;

    // short, int, long, long long -> double
    defaultWeights[WeightKey(NODE_CONVERT, TYPE_SHORT, TYPE_DOUBLE)] = 4;
    defaultWeights[WeightKey(NODE_CONVERT, TYPE_INT, TYPE_DOUBLE)] = 4;
    defaultWeights[WeightKey(NODE_CONVERT, TYPE_LONG, TYPE_DOUBLE)] = 4;
    defaultWeights[WeightKey(NODE_CONVERT, TYPE_LLONG, TYPE_DOUBLE)] = 4;

    // char -> short, int, long, long long, bool
    defaultWeights[WeightKey(NODE_CONVERT, TYPE_CHAR, TYPE_SHORT)] = 1;
    defaultWeights[WeightKey(NODE_CONVERT, TYPE_CHAR, TYPE_INT)] = 1;
    defaultWeights[WeightKey(NODE_CONVERT, TYPE_CHAR, TYPE_LONG)] = 1;
    defaultWeights[WeightKey(NODE_CONVERT, TYPE_CHAR, TYPE_LLONG)] = 1;
    defaultWeights[WeightKey(NODE_CONVERT, TYPE_CHAR, TYPE_BOOL)] = 1;

    // char -> float, double
    defaultWeights[WeightKey(NODE_CONVERT, TYPE_CHAR, TYPE_FLOAT)] = 4;
    defaultWeights[WeightKey(NODE_CONVERT, TYPE_CHAR, TYPE_DOUBLE)] = 4;

    // bool -> short, int, long, long long
    defaultWeights[WeightKey(NODE_CONVERT, TYPE_BOOL, TYPE_SHORT)] = 1;
    defaultWeights[WeightKey(NODE_CONVERT, TYPE_BOOL, TYPE_INT)] = 1;
    defaultWeights[WeightKey(NODE_CONVERT, TYPE_BOOL, TYPE_LONG)] = 1;
    defaultWeights[WeightKey(NODE_CONVERT, TYPE_BOOL, TYPE_LLONG)] = 1;

    // bool -> float, double
    defaultWeights[WeightKey(NODE_CONVERT, TYPE_BOOL, TYPE_FLOAT)] = 4;
    defaultWeights[WeightKey(NODE_CONVERT, TYPE_BOOL, TYPE_DOUBLE)] = 4;

    // short -> int, long, long long
    defaultWeights[WeightKey(NODE_CONVERT, TYPE_SHORT, TYPE_INT)] = 1;
    defaultWeights[WeightKey(NODE_CONVERT, TYPE_SHORT, TYPE_LONG)] = 1;
    defaultWeights[WeightKey(NODE_CONVERT, TYPE_SHORT, TYPE_LLONG)] = 1;

    // int -> long, long long
    defaultWeights[WeightKey(NODE_CONVERT, TYPE_INT, TYPE_LONG)] = 1;
    defaultWeights[WeightKey(NODE_CONVERT, TYPE_INT, TYPE_LLONG)] = 1;

    // long -> long long
    defaultWeights[WeightKey(NODE_CONVERT, TYPE_LONG, TYPE_LLONG)] = 1;

    // float -> double
    defaultWeights[WeightKey(NODE_CONVERT, TYPE_FLOAT, TYPE_DOUBLE)] = 2;
}
