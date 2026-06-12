#include <QStringList>
#include <QRegularExpression>

#include "parseweightinfo.h"
#include "../utils/typeutils.h"


namespace parse_utils
{
    std::optional<QPair<WeightKey, int>> parseWeightInfo(const QString& weightStr, QSet<Error>& errors) {
        // Разбить входную строку на список подстрок по разделителю пробел
        QStringList parts = weightStr.trimmed().split(QRegularExpression("\\s+"), Qt::SkipEmptyParts);

        if (parts.isEmpty()) {
            return std::nullopt;
        }

        // Если первый элемент равен «convert» и количество параметров соответствует формату (ключевое слово «convert», исходный тип, результирующий тип, вес)
        if (parts[0] == "convert" && parts.size() == 4) {
            DataType srcType = type_utils::stringToDataType(parts[1]);
            DataType dstType = type_utils::stringToDataType(parts[2]);

            bool okSrc = (srcType != TYPE_UNKNOWN);
            bool okDst = (dstType != TYPE_UNKNOWN);

            bool okWeight;
            int weight = parts[3].toInt(&okWeight);

            // Если исходный и результирующий типы корректны, а вес является допустимым числом
            if (okSrc && okDst && okWeight && weight > 0) {
                // Проверка на конфликт типов при преобразовании в тот же тип
                if (srcType == dstType) {
                    // Добавить соответствующую ошибку и вернуть std::nullopt
                    Error err;
                    err.setType(ERR_SAME_TYPE_CONVERSION);  // Конфликт типов при преобразовании
                    err.setObjectName(parts[1] + " -> " + parts[2]);
                    errors.insert(err);
                    return std::nullopt;
                }

                // Сформировать ключ преобразования WeightKey
                WeightKey key(NODE_CONVERT, srcType, dstType);

                // Вернуть объект std::optional, содержащий пару (ключ, вес)
                return qMakePair(key, weight);
            }
            // Иначе
            else {
                // Добавить соответствующую ошибку и вернуть std::nullopt
                Error err;
                if (!okSrc || !okDst) {
                    err.setType(ERR_UNRECOGNIZED_OBJECT);   // Указан неизвестный тип данных
                    err.setObjectName(!okSrc ? parts[1] : parts[2]);
                } else if (!okWeight) {
                    err.setType(ERR_INVALID_WEIGHT_FORMAT); // Вес операции не является натуральным числом
                    err.setObjectName(parts[3]);
                } else {
                    err.setType(ERR_WEIGHT_OUT_OF_RANGE);   // Вес операции не принадлежит диапазону
                    err.setObjectName(parts[3]);
                }
                errors.insert(err);
                return std::nullopt;
            }
        }
        // Иначе, если строка соответствует формату операции (операция, тип, вес)
        else if (parts.size() == 3) {
            ExprNodeType op = type_utils::stringToExprNodeType(parts[0]);
            DataType type = type_utils::stringToDataType(parts[1]);

            bool okOp = (op != NODE_UNKNOWN);
            bool okType = (type != TYPE_UNKNOWN);

            bool okWeight;
            int weight = parts[2].toInt(&okWeight);

            // Если операция и тип корректны, а вес является допустимым числом
            if (okOp && okType && okWeight && weight > 0) {
                // Сформировать ключ операции WeightKey
                WeightKey key(op, type, type);

                // Вернуть объект std::optional, содержащий пару (ключ, вес)
                return qMakePair(key, weight);
            }
            // Иначе
            else {
                // Добавить соответствующую ошибку и вернуть std::nullopt
                Error err;
                if (!okOp || !okType) {
                    err.setType(ERR_UNRECOGNIZED_OBJECT);   // Указан неизвестный тип данных
                    err.setObjectName(!okOp ? parts[0] : parts[1]);
                } else if (!okWeight) {
                    err.setType(ERR_INVALID_WEIGHT_FORMAT); // Вес операции не является натуральным числом
                    err.setObjectName(parts[2]);
                } else {
                    err.setType(ERR_WEIGHT_OUT_OF_RANGE);   // Вес операции не принадлежит диапазону
                    err.setObjectName(parts[2]);
                }
                errors.insert(err);
                return std::nullopt;
            }
        }
        // Иначе (неверный формат строки)
        else {
            // Добавить соответствующую ошибку и вернуть std::nullopt
            Error err;
            if (parts.size() == 4 && parts[0] != "convert") {
                err.setType(ERR_MISSING_CONVERT_KEYWORD);   // Для преобразования типов отсутствует ключевое слово convert
            } else {
                err.setType(ERR_INVALID_LINE_FORMAT);       // Строка не соответствует допустимому формату
            }
            err.setObjectName(weightStr);
            errors.insert(err);

            return std::nullopt;
        }
    }
}
