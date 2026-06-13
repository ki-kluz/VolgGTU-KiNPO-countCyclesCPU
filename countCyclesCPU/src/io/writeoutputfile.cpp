#include <QFile>
#include <QTextStream>

#include "writeoutputfile.h"
#include "../io/generatedot.h"
#include "../utils/typeutils.h"


// Вспомогательная функция для генерации инфиксной записи из дерева
static QString generateInfix(ExprNode* node) {
    if (node == nullptr) {
        return "";
    }
    // Если это лист (значение или переменная), просто возвращаем его
    if (node->getType() == NODE_VALUE || node->getType() == NODE_VARIABLE) {
        return node->getVal();
    }
    // Если это унарная операция
    if (ExprNode::isUnaryOperator(node->getType())) {
        QString op = type_utils::exprNodeTypeToString(node->getType());
        QString child = generateInfix(node->getLeft());

        // Красивое форматирование специфичных унарных операторов
        if (op == "++_") return "++" + child;
        if (op == "--_") return "--" + child;
        if (op == "_++") return child + "++";
        if (op == "_--") return child + "--";
        if (op == "-_") return "-" + child;
        if (op == "convert") return "(" + type_utils::dataTypeToString(node->getDataType()) + ")" + child;

        return op + child;
    }
    // Если это бинарная операция
    QString leftStr = generateInfix(node->getLeft());
    QString rightStr = generateInfix(node->getRight());
    QString op = type_utils::exprNodeTypeToString(node->getType());

    // Оборачиваем в скобки для сохранения приоритета операций
    return "(" + leftStr + " " + op + " " + rightStr + ")";
}

bool writeOutputFile(
    const QString& outputFile,
    ExprNode* root,
    int totalCost,
    QSet<Error>& errors
    ) {
    // Проверка на то, что выходной файл указан
    if (outputFile.isEmpty()) {
        Error err;
        err.setType(ERR_OUTPUT_FILE_NOT_SPECIFIED);
        errors.insert(err);
        return false;
    }

    QFile file(outputFile);

    // Попытка открыть файл для записи
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        Error err;
        err.setType(ERR_OUTPUT_FILE_CANNOT_CREATE);
        err.setOutputFilePath(outputFile);
        errors.insert(err);
        return false;
    }

    QTextStream out(&file);

    // Первая строка – представление выражения в стандартном виде (инфиксная запись)
    out << "// Expression: " << generateInfix(root) << "\n";

    generateDOT(root, out);

    // Последняя строка – конечный ответ (суммарное количество тактов процессора)
    out << "// Total CPU cycles: " << totalCost << "\n";

    file.close();
    return true;
}
