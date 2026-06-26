#ifndef WEIGHTKEY_H
#define WEIGHTKEY_H

/**
 * @file weightkey.h
 * @brief Структура ключа для таблицы весов операций.
 */

#include "../enums/DataType.h"
#include "../enums/ExprNodeType.h"

/**
 * @brief Составной ключ для поиска стоимости операции в QMap.
 *
 * Уникально идентифицирует операцию на основе её типа и типов операндов.
 */
struct WeightKey
{
    /**
     * @brief Конструктор ключа.
     * @param[in] op Тип операции.
     * @param[in] left Тип левого операнда.
     * @param[in] right Тип правого операнда.
     */
    WeightKey(ExprNodeType op, DataType left, DataType right);

    ExprNodeType op;        ///< Узел дерева (Plus, Minus и т.д.)
    DataType leftType;      ///< Тип данных левого операнда
    DataType rightType;     ///< Тип данных правого операнда

    /**
     * @brief Оператор "меньше".
     * @param[in] other Другой ключ для сравнения
     */
    bool operator<(const WeightKey& other) const;
};

#endif // WEIGHTKEY_H