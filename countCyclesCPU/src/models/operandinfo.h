#ifndef OPERANDINFO_H
#define OPERANDINFO_H

/**
 * @file operandinfo.h
 * @brief Структура для хранения информации об операндах (переменных и константах).
 */

#include <QString>
#include "../enums/DataType.h"

/**
 * @brief Структура, описывающая операнд выражения.
 */
struct OperandInfo
{
    /** @brief Конструктор по умолчанию. */
    OperandInfo();

    /**
     * @brief Конструктор с инициализацией.
     * @param[in] name Имя переменной.
     * @param[in] value Значение (для констант).
     * @param[in] type Тип данных.
     */
    OperandInfo(const QString& name, const QString& value, DataType type);

    QString name;       ///< Имя переменной (по умолчанию пустое "" для констант)
    QString value;      ///< Значение константы
    DataType type;      ///< Тип данных переменной или константы
};

#endif // OPERANDINFO_H