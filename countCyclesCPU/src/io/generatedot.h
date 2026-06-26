#ifndef GENERATEDOT_H
#define GENERATEDOT_H

/**
 * @file generatedot.h
 * @brief Функции для генерации визуального представления дерева выражений в формате DOT.
 */

#include <QTextStream>
#include "../models/exprnode.h"

/**
 * @brief Генерирует DOT-граф для заданного синтаксического дерева.
 * @param[in] root Указатель на корневой узел дерева выражений.
 * @param[in,out] out Поток вывода (QTextStream), куда будет записан код графа.
 */
void generateDOT(ExprNode* root, QTextStream& out);

/**
 * @brief Рекурсивно обходит дерево и генерирует узлы и связи в формате DOT.
 * @param[in] node Указатель на текущий обрабатываемый узел.
 * @param[in,out] out Поток вывода (QTextStream) для записи DOT-кода.
 * @param[in,out] nodeId Ссылка на счетчик идентификаторов узлов.
 */
void generateDOTRecursive(ExprNode* node, QTextStream& out, int& nodeId);

#endif // GENERATEDOT_H