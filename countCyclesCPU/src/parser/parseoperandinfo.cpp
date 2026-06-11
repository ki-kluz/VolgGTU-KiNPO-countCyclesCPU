#include <QStringList>
#include <QRegularExpression>

#include "parseoperandinfo.h"
#include "../utils/typeutils.h"


namespace parse_utils
{
    OperandInfo parseOperandInfo(const QString& operandStr, QSet<Error>& errors) {
        // Разделить строку по пробелу (с удалением лишних пробелов)
        QStringList parts = operandStr.trimmed().split(QRegularExpression("\\s+"), Qt::SkipEmptyParts);

        // Если строка соответствует корректному формату (ровно 2 аргумента: имя и тип)
        if (parts.size() == 2) {
            // Выделить имя переменной (первый аргумент)
            QString name = parts[0];

            // Выделить тип переменной (второй аргумент)
            QString typeStr = parts[1];

            // Если строка информации об операнде обработана
            DataType type = type_utils::stringToDataType(typeStr);
            if (type != TYPE_UNKNOWN) {
                // Сформировать и вернуть объект OperandInfo
                return OperandInfo(name, "", type);
            } else {    // Иначе (тип не распознан)
                // Добавить соответствующую ошибку
                Error err;
                err.setType(ERR_UNSUPPORTED_TYPE);  // Указан неподдерживаемый тип данных
                err.setObjectName(typeStr);
                err.setActual(typeStr);
                errors.insert(err);

                return OperandInfo(name, "", TYPE_UNKNOWN);
            }
        }
        // Иначе (неверный формат строки)
        else {
            // Добавить соответствующую ошибку
            Error err;
            err.setType(ERR_MISSING_TYPE_DECLARATION);  // Неполное описание переменных
            err.setObjectName(operandStr);
            errors.insert(err);

            return OperandInfo();
        }
    }
}
