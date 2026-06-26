#ifndef OPERATORUTILS_H
#define OPERATORUTILS_H

/**
 * @file operatorutils.h
 * @brief Утилиты для семантической валидации операций в дереве выражений.
 */

#include <QSet>
#include "../enums/ExprNodeType.h"
#include "../enums/DataType.h"
#include "../models/error.h"

/**
 * @namespace operator_utils
 * @brief Пространство имен, содержащее функции для проверки корректности операций.
 */
namespace operator_utils
{
/**
 * @brief Проверяет, допустима ли операция для заданных типов операндов.
 * @param[in] op Тип проверяемой операции.
 * @param[in] left Тип левого операнда.
 * @param[in] right Тип правого операнда.
 * @param[in,out] errors Множество для записи ошибки.
 * @return true Если операция допустима.
 */
bool checkSupportedOperation(ExprNodeType op, DataType left, DataType right, QSet<Error>& errors);

/**
 * @brief Проверяет наличие недопустимого сужающего преобразования.
 * @param[in] op Тип операции.
 * @param[in] left Целевой тип.
 * @param[in] right Исходный тип.
 * @param[in,out] errors Множество для записи ошибки.
 * @return true Если сужающего преобразования нет или оно допустимо.
 */
bool checkNarrowingConversion(ExprNodeType op, DataType left, DataType right, QSet<Error>& errors);

/**
 * @brief Проверяет, не превышен ли глобальный лимит стоимости вычислений.
 * @param[in] totalCost Текущая суммарная стоимость выражения в тактах.
 * @param[in,out] errors Множество для записи ошибки.
 * @return true Если лимит не превышен.
 */
bool checkMaxCostLimit(int totalCost, QSet<Error>& errors);
}

#endif // OPERATORUTILS_H