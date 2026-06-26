#ifndef EXPRNODE_H
#define EXPRNODE_H

/**
 * @file exprnode.h
 * @brief Содержит класс ExprNode для представления узлов синтаксического дерева.
 */

#include <QString>
#include <QSet>
#include "../enums/DataType.h"
#include "../enums/ExprNodeType.h"
#include "../models/weighttable.h"
#include "../models/error.h"

/**
 * @brief Класс узла абстрактного синтаксического дерева (AST).
 *
 * Может представлять как операнд (лист дерева), так и операцию (внутренний узел).
 * Содержит логику рекурсивного вычисления стоимости выражения.
 */
class ExprNode
{
public:
    /** @brief Конструктор по умолчанию. */
    ExprNode();

    /**
     * @brief Конструктор для создания узла-операнда (листа).
     * @param[in] type Тип узла (NODE_VALUE или NODE_VARIABLE).
     * @param[in] val Строковое значение (имя переменной или константа).
     * @param[in] dataType Тип данных операнда.
     */
    ExprNode(ExprNodeType type, const QString& val, DataType dataType);

    /**
     * @brief Конструктор для создания узла-операции.
     * @param[in] type Тип операции (например, NODE_PLUS).
     * @param[in] dataType Тип данных результата операции.
     * @param[in] left Указатель на левое поддерево.
     * @param[in] right Указатель на правое поддерево (может быть nullptr для унарных операций).
     */
    ExprNode(ExprNodeType type, DataType dataType, ExprNode* left, ExprNode* right);

    /** @brief Деструктор. Рекурсивно удаляет дочерние узлы. */
    ~ExprNode();

    ExprNodeType getType() const;       ///< Возвращает тип узла
    QString getVal() const;             ///< Возвращает строковое значение
    DataType getDataType() const;       ///< Возвращает тип данных
    ExprNode* getLeft() const;          ///< Возвращает указатель на левого потомка
    ExprNode* getRight() const;         ///< Возвращает указатель на правого потомка

    /**
     * @brief Рекурсивно вычисляет суммарную стоимость поддерева в тактах.
     * @param[in] weights Таблица весов операций.
     * @param[in,out] errors Множество для записи семантических ошибок.
     * @return Суммарная стоимость в тактах (или -1 при ошибке).
     */
    int calculateCost(const WeightTable& weights, QSet<Error>& errors);

    /** @param[in] type Тип узла. */
    static bool isUnaryOperator(ExprNodeType type);

    /** @param[in] type Тип узла. */
    static bool isBinaryOperator(ExprNodeType type);

    /**
     * @param[in] left Тип левого операнда.
     * @param[in] right Тип правого операнда.
     */
    static DataType getGeneralType(DataType left, DataType right);

    /**
     * @param[in] op Тип операции.
     * @param[in] left Тип левого операнда.
     * @param[in] right Тип правого операнда.
     */
    static DataType getResultType(ExprNodeType op, DataType left, DataType right);

    /**
     * @param[in] left Тип левого операнда.
     * @param[in] right Тип правого операнда.
     */
    static bool isConversionNecessary(DataType left, DataType right);

private:
    ExprNodeType type;       ///< Тип узла выражения (оператор или операнд)
    QString val;             ///< Значение узла (для листьев)
    DataType dataType;       ///< Тип данных узла
    ExprNode* left;          ///< Левый операнд (потомок)
    ExprNode* right;         ///< Правый операнд (потомок)
};

#endif // EXPRNODE_H