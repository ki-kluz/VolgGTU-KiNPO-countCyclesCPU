#ifndef TYPEUTILS_H
#define TYPEUTILS_H

/**
 * @file typeutils.h
 * @brief Утилиты для работы с типами данных и конвертации строк.
 */

#include <QString>
#include <QSet>
#include "../enums/DataType.h"
#include "../enums/ExprNodeType.h"
#include "../models/error.h"

/**
 * @namespace type_utils
 * @brief Пространство имен со вспомогательными функциями для парсинга и форматирования типов.
 */
namespace type_utils
{
/**
 * @brief Преобразует строковое представление типа данных в элемент перечисления DataType.
 * @param[in] str Строка с названием типа.
 * @return Соответствующее значение DataType.
 */
DataType stringToDataType(const QString& str);

/**
 * @brief Преобразует строковое представление операции в элемент перечисления ExprNodeType.
 * @param[in] str Строка с оператором.
 * @return Соответствующее значение ExprNodeType.
 */
ExprNodeType stringToExprNodeType(const QString& str);

/**
 * @brief Возвращает строковое представление типа данных.
 * @param[in] type Значение из перечисления DataType.
 * @return Строка с названием типа.
 */
QString dataTypeToString(DataType type);

/**
 * @brief Возвращает строковое представление узла операции.
 * @param[in] type Значение из перечисления ExprNodeType.
 * @return Строка с символом оператора.
 */
QString exprNodeTypeToString(ExprNodeType type);

/**
 * @brief Определяет тип константы на основе её строкового представления.
 * @param[in] token Строка, содержащая константу.
 * @param[in,out] errors Множество для записи ошибки.
 * @return Определенный тип данных константы.
 */
DataType getConstType(const QString& token, QSet<Error>& errors);
}

#endif // TYPEUTILS_H