#include "generatedot.h"

#include "../utils/typeutils.h"


void generateDOT(ExprNode* root, QTextStream& out) {
    // Если корень дерева равен nullptr
    if (root == nullptr) {
        // Завершить выполнение функции
        return;
    }
    // Записать заголовок DOT-структуры
    out << "digraph G {\n";

    // Создать счётчик идентификаторов уникальных узлов
    int nodeId = 0;

    // Вызвать рекурсивную функцию генерации
    generateDOTRecursive(root, out, nodeId);

    // Записать конец DOT-структуры
    out << "}\n";
}

void generateDOTRecursive(ExprNode* node, QTextStream& out, int& nodeId) {
    // Если текущий узел равен nullptr
    if (node == nullptr) {
        // Завершить выполнение функции
        return;
    }
    // Сохранить идентификатор текущего узла
    int currentId = nodeId;

    // Увеличить счётчик идентификаторов
    nodeId++;

    // Сформировать строку текущего узла
    QString label;
    if (node->getType() == NODE_VALUE || node->getType() == NODE_VARIABLE) {
        label = node->getVal();
    } else {
        label = type_utils::exprNodeTypeToString(node->getType());
    }
    label.replace("\"", "\\\"");

    out << "    node" << currentId << " [label=\"" << label << "\"];\n";

    // Если существует левый потомок
    if (node->getLeft() != nullptr) {
        // Сгенерировать связь между ними
        out << "    node" << currentId << " -> node" << nodeId << ";\n";

        // Рекурсивно обработать левый узел
        generateDOTRecursive(node->getLeft(), out, nodeId);
    }
    // Если существует правый потомок
    if (node->getRight() != nullptr) {
        // Сгенерировать связь между ними
        // ВАЖНО: nodeId здесь уже изменён после обхода левого поддерева, что гарантирует уникальность!
        out << "    node" << currentId << " -> node" << nodeId << ";\n";

        // Рекурсивно обработать правый узел
        generateDOTRecursive(node->getRight(), out, nodeId);
    }
}
