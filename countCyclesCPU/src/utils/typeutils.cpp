#include "typeutils.h"
#include <QHash>

namespace type_utils
{
    DataType stringToDataType(const QString& str) {
        static const QHash<QString, DataType> map = {
            {"bool", DataType::TYPE_BOOL},
            {"char", DataType::TYPE_CHAR},
            {"short", DataType::TYPE_SHORT},
            {"int", DataType::TYPE_INT},
            {"long", DataType::TYPE_LONG},
            {"llong", DataType::TYPE_LLONG},
            {"float", DataType::TYPE_FLOAT},
            {"double", DataType::TYPE_DOUBLE}
        };

        return map.value(str, DataType::TYPE_UNKNOWN);
    }

    ExprNodeType stringToExprNodeType(const QString& str) {
        static const QHash<QString, ExprNodeType> map = {
            {"+", ExprNodeType::NODE_PLUS},
            {"-", ExprNodeType::NODE_MINUS},
            {"*", ExprNodeType::NODE_MULTIPLICATION},
            {"/", ExprNodeType::NODE_DIVISION},
            {"//", ExprNodeType::NODE_INTEGER_DIVISION},
            {"%", ExprNodeType::NODE_REMAINDER},
            {"++_", ExprNodeType::NODE_PREF_INC},
            {"--_", ExprNodeType::NODE_PREF_DEC},
            {"_++", ExprNodeType::NODE_POST_INC},
            {"_--", ExprNodeType::NODE_POST_DEC},
            {"&&", ExprNodeType::NODE_LOG_AND},
            {"||", ExprNodeType::NODE_LOG_OR},
            {"!", ExprNodeType::NODE_LOG_NOT},
            {"-_", ExprNodeType::NODE_NEGATIVE},
            {"==", ExprNodeType::NODE_EQUAL},
            {"!=", ExprNodeType::NODE_NOT_EQUAL},
            {"<", ExprNodeType::NODE_LESS},
            {">", ExprNodeType::NODE_GREATER},
            {"<=", ExprNodeType::NODE_LESS_EQUAL},
            {">=", ExprNodeType::NODE_GREATER_EQUAL},
            {"&", ExprNodeType::NODE_BIT_AND},
            {"|", ExprNodeType::NODE_BIT_OR},
            {"^", ExprNodeType::NODE_BIT_XOR},
            {"~", ExprNodeType::NODE_BIT_NOT},
            {"<<", ExprNodeType::NODE_SHIFT_LEFT},
            {">>", ExprNodeType::NODE_SHIFT_RIGHT},
            {"=", ExprNodeType::NODE_ASSIGNMENT},
            {"+=", ExprNodeType::NODE_PLUS_EQUAL},
            {"-=", ExprNodeType::NODE_MINUS_EQUAL},
            {"*=", ExprNodeType::NODE_MULTI_EQUAL},
            {"/=", ExprNodeType::NODE_DIV_EQUAL},
            {"%=", ExprNodeType::NODE_REMAIN_EQUAL},
            {"convert", ExprNodeType::NODE_CONVERT}
        };

        return map.value(str, ExprNodeType::NODE_UNKNOWN);
    }

    QString dataTypeToString(DataType type) {
        static const QHash<DataType, QString> map = {
            {DataType::TYPE_BOOL, "bool"},
            {DataType::TYPE_CHAR, "char"},
            {DataType::TYPE_SHORT, "short"},
            {DataType::TYPE_INT, "int"},
            {DataType::TYPE_LONG, "long"},
            {DataType::TYPE_LLONG, "long long"},
            {DataType::TYPE_FLOAT, "float"},
            {DataType::TYPE_DOUBLE, "double"}
        };

        return map.value(type, "unknown");
    }

    QString exprNodeTypeToString(ExprNodeType type) {
        static const QHash<ExprNodeType, QString> map = {
            {ExprNodeType::NODE_PLUS, "+"},
            {ExprNodeType::NODE_MINUS, "-"},
            {ExprNodeType::NODE_MULTIPLICATION, "*"},
            {ExprNodeType::NODE_DIVISION, "/"},
            {ExprNodeType::NODE_INTEGER_DIVISION, "//"},
            {ExprNodeType::NODE_REMAINDER, "%"},
            {ExprNodeType::NODE_PREF_INC, "++_"},
            {ExprNodeType::NODE_PREF_DEC, "--_"},
            {ExprNodeType::NODE_POST_INC, "_++"},
            {ExprNodeType::NODE_POST_DEC, "_--"},
            {ExprNodeType::NODE_LOG_AND, "&&"},
            {ExprNodeType::NODE_LOG_OR, "||"},
            {ExprNodeType::NODE_LOG_NOT, "!"},
            {ExprNodeType::NODE_NEGATIVE, "-_"},
            {ExprNodeType::NODE_EQUAL, "=="},
            {ExprNodeType::NODE_NOT_EQUAL, "!="},
            {ExprNodeType::NODE_LESS, "<"},
            {ExprNodeType::NODE_GREATER, ">"},
            {ExprNodeType::NODE_LESS_EQUAL, "<="},
            {ExprNodeType::NODE_GREATER_EQUAL, ">="},
            {ExprNodeType::NODE_BIT_AND, "&"},
            {ExprNodeType::NODE_BIT_OR, "|"},
            {ExprNodeType::NODE_BIT_XOR, "^"},
            {ExprNodeType::NODE_BIT_NOT, "~"},
            {ExprNodeType::NODE_SHIFT_LEFT, "<<"},
            {ExprNodeType::NODE_SHIFT_RIGHT, ">>"},
            {ExprNodeType::NODE_ASSIGNMENT, "="},
            {ExprNodeType::NODE_PLUS_EQUAL, "+="},
            {ExprNodeType::NODE_MINUS_EQUAL, "-="},
            {ExprNodeType::NODE_MULTI_EQUAL, "*="},
            {ExprNodeType::NODE_DIV_EQUAL, "/="},
            {ExprNodeType::NODE_REMAIN_EQUAL, "%="},
            {ExprNodeType::NODE_CONVERT, "convert"}
        };

        return map.value(type, "unknown");
    }

    DataType getConstType(const QString& token, QSet<Error>& errors) {
        DataType type = DataType::TYPE_UNKNOWN;
        bool ok = false;
        double checkValue = 0.0;

        if (token == "true" || token == "false") {
            type = DataType::TYPE_BOOL;
        }
        else if (token.startsWith('\'') && token.endsWith('\'') && token.length() == 3) {
            type = DataType::TYPE_CHAR;
        }
        else if (token.endsWith('F', Qt::CaseInsensitive)) {
            checkValue = token.left(token.length() - 1).toDouble(&ok);
            if (ok) {
                type = DataType::TYPE_FLOAT;
            }
        }
        else if (token.endsWith("LL", Qt::CaseInsensitive)) {
            checkValue = static_cast<double>(token.left(token.length() - 2).toLongLong(&ok));
            if (ok) {
                type = DataType::TYPE_LLONG;
            }
        }
        else if (token.endsWith('L', Qt::CaseInsensitive)) {
            checkValue = static_cast<double>(token.left(token.length() - 1).toLong(&ok));
            if (ok) {
                type = DataType::TYPE_LONG;
            }
        }
        else if (token.endsWith('S', Qt::CaseInsensitive)) {
            checkValue = static_cast<double>(token.left(token.length() - 1).toShort(&ok));
            if (ok) {
                type = DataType::TYPE_SHORT;
            }
        }
        else if (token.contains('.')) {
            checkValue = token.toDouble(&ok);
            if (ok) {
                type = DataType::TYPE_DOUBLE;
            }
        }
        else {
            checkValue = static_cast<double>(token.toInt(&ok));
            if (ok) {
                type = DataType::TYPE_INT;
            }
        }

        // Если токен успешно распознан как число, проверяем его диапазон
        if (ok && type != DataType::TYPE_BOOL && type != DataType::TYPE_CHAR) {
            if (checkValue < -1000000.0 || checkValue > 1000000.0) {
                Error err;
                err.setType(ERR_OPERAND_OUT_OF_RANGE);
                err.setObjectName(token);
                errors.insert(err);

                // Сбрасываем тип
                type = DataType::TYPE_UNKNOWN;
            }
        }
        return type;
    }
}
