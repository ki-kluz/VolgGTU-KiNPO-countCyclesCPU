#ifndef PARSEOPERANDINFO_H
#define PARSEOPERANDINFO_H

/**
 * @file parseoperandinfo.h
 * @brief Функция для разбора информации об операндах (переменных).
 */

#include <QString>
#include <QSet>
#include "../models/error.h"
#include "../models/operandinfo.h"

/**
 * @namespace parse_utils
 * @brief Пространство имен, содержащее функции лексического и синтаксического анализа.
 */
namespace parse_utils
{
/**
 * @brief Разбирает строку с описанием переменной из входного файла.
 * @param[in] operandStr Строка, содержащая описание операнда.
 * @param[in,out] errors Множество для записи лексических и синтаксических ошибок.
 * @return Объект OperandInfo с извлеченным именем и типом.
 */
OperandInfo parseOperandInfo(const QString& operandStr, QSet<Error>& errors);
}

#endif // PARSEOPERANDINFO_H