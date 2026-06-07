#ifndef EXPRNODE_H
#define EXPRNODE_H

#include <QString>

#include "src/enums/DataType.h"
#include "src/enums/ExprNodeType.h"
#include "src/models/weighttable.h"
#include "src/models/error.h"


class ExprNode
{
public:
    ExprNode();
    ExprNode(   // для operand
        ExprNodeType type,
        const QString& val,
        DataType dataType
        );
    ExprNode(   // для operators
        ExprNodeType type,
        DataType dataType,
        ExprNode* left,
        ExprNode* right
        );

    ~ExprNode();

    ExprNodeType getType() const;
    QString getVal() const;
    DataType getDataType() const;
    ExprNode* getLeft() const;
    ExprNode* getRight() const;

    int calculateCost(const WeightTable& weights);

    static bool isUnaryOperator(ExprNodeType type);
    static bool isBinaryOperator(ExprNodeType type);
    static DataType getGeneralType(DataType left, DataType right);
    static DataType getResultType(ExprNodeType op, DataType left, DataType right);
    static bool isConversionNecessary(DataType left, DataType right);

private:
    ExprNodeType type;       // Тип узла выражения (оператор или операнд)
    QString val;             // Значение узла
    DataType dataType;       // Тип данных узла
    ExprNode* left;          // Левый операнд
    ExprNode* right;         // Правый операнд
};

#endif // EXPRNODE_H
