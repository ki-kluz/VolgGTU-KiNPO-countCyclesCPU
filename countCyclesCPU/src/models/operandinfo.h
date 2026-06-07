#ifndef OPERANDINFO_H
#define OPERANDINFO_H

#include <QString>

#include "src/enums/DataType.h"


struct OperandInfo
{
    OperandInfo();
    OperandInfo(
        const QString& name,
        const QString& value,
        DataType type
        );

    QString name;       // Имя переменной (по умолчание пустое "" - const)
    QString value;      // Значение
    DataType type;      // Тип данных переменной
};

#endif // OPERANDINFO_H
