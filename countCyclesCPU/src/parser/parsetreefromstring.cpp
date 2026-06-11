#include <QStringList>
#include <QRegularExpression>
#include <QStack>

#include "parsetreefromstring.h"
#include "../utils/typeutils.h"


namespace parse_utils
{
    ExprNode* parseTreeFromString(
        const QString& exprStr,
        const QMap<QString, DataType>& operandsInfo,
        QSet<Error>& errors
    ) {
        // Разбить строку ОПЗ выражения на список подстрок (частей) по разделителю пробел
        QStringList parts = exprStr.trimmed().split(QRegularExpression("\\s+"), Qt::SkipEmptyParts);

        // Создать пустой стек
        QStack<ExprNode*> stack;

        // Счетчик операций для проверки лимита
        int operationCount = 0;

        // Для каждого элемента полученного списка
        for (const QString& token : parts) {
            DataType constType = type_utils::getConstType(token, errors);
            ExprNodeType opType = type_utils::stringToExprNodeType(token);

            // Если элемент – значение (const)
            if (constType != TYPE_UNKNOWN) {
                stack.push(new ExprNode(NODE_VALUE, token, constType));
            }
            // Иначе, если элемент – имя переменной (содержится в operandsInfo)
            else if (operandsInfo.contains(token)) {
                stack.push(new ExprNode(NODE_VARIABLE, token, operandsInfo.value(token)));
            }
            // Проверяем, является ли токен известным оператором
            else if (opType != NODE_UNKNOWN) {
                // Увеличиваем счетчик операций и проверяем лимит (20 операций)
                operationCount++;
                if (operationCount > 20) {
                    while (!stack.isEmpty()) {
                        delete stack.pop();
                    }
                    Error err;
                    err.setType(ERR_MAX_OPERATIONS_EXCEEDED);
                    err.setObjectName(token);
                    errors.insert(err);
                    return nullptr;
                }
                // Иначе, если элемент – бинарная операция
                if (ExprNode::isBinaryOperator(opType)) {
                    if (stack.size() >= 2) {
                        ExprNode* right = stack.pop();
                        ExprNode* left = stack.pop();

                        ExprNode* node = new ExprNode(opType, TYPE_UNKNOWN, left, right);
                        stack.push(node);
                    } else {
                        while (!stack.isEmpty()) {
                            delete stack.pop();
                        }
                        Error err;
                        err.setType(ERR_INSUFFICIENT_OPERANDS);
                        err.setObjectName(token);
                        errors.insert(err);
                        return nullptr;
                    }
                }
                // Иначе, если элемент – унарная операция
                else if (ExprNode::isUnaryOperator(opType)) {
                    if (stack.size() >= 1) {
                        ExprNode* operand = stack.pop();

                        ExprNode* node = new ExprNode(opType, TYPE_UNKNOWN, operand, nullptr);
                        stack.push(node);
                    } else {
                        while (!stack.isEmpty()) {
                            delete stack.pop();
                        }
                        Error err;
                        err.setType(ERR_INSUFFICIENT_OPERANDS);
                        err.setObjectName(token);
                        errors.insert(err);
                        return nullptr;
                    }
                }
            }
            // Иначе (неизвестный символ)
            else {
                Error err;
                err.setType(ERR_INVALID_TOKEN);
                err.setObjectName(token);
                errors.insert(err);
            }
        }
        // Если после обработки всех элементов в стеке остался ровно один узел
        if (stack.size() == 1) {
            return stack.pop();
        }
        // Иначе (стек пуст или больше 1-го узла)
        else {
            while (!stack.isEmpty()) {
                delete stack.pop();
            }

            Error err;
            err.setType(ERR_EXCESS_OPERANDS);
            err.setObjectName(exprStr);
            errors.insert(err);

            return nullptr;
        }
    }
}
