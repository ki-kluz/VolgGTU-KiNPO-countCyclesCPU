#ifndef PARSETREEFROMSTRING_H
#define PARSETREEFROMSTRING_H

/**
 * @file parsetreefromstring.h
 * @brief Функция построения абстрактного синтаксического дерева (AST) из строки ОПЗ.
 */

#include <QString>
#include <QMap>
#include <QSet>
#include "../models/error.h"
#include "../models/exprnode.h"

namespace parse_utils
{
/**
 * @brief Строит синтаксическое дерево на основе выражения в обратной польской записи (ОПЗ).
 * @param[in] exprStr Строка с выражением в формате ОПЗ.
 * @param[in] operandsInfo Словарь объявленных переменных.
 * @param[in,out] errors Множество для записи ошибок.
 * @return Указатель на корневой узел дерева (ExprNode*) или nullptr в случае ошибки.
 */
ExprNode* parseTreeFromString(
    const QString& exprStr,
    const QMap<QString, DataType>& operandsInfo,
    QSet<Error>& errors
    );
}

#endif // PARSETREEFROMSTRING_H