#include "exprnode.h"
#include <QSet>


ExprNode::ExprNode() {
    type = NODE_UNKNOWN;
    val = "";
    dataType = TYPE_UNKNOWN;
    left = nullptr;
    right = nullptr;
}

ExprNode::ExprNode(
    ExprNodeType type,
    const QString& val,
    DataType dataType
) {
    this->type = type;
    this->val = val;
    this->dataType = dataType;
    left = nullptr;
    right = nullptr;
}

ExprNode::ExprNode(
    ExprNodeType type,
    DataType dataType,
    ExprNode* left,
    ExprNode* right
) {
    this->type = type;
    this->val = "";
    this->dataType = dataType;
    this->left = left;

    if (isUnaryOperator(type)) {
        this->right = nullptr;
    } else {
        this->right = right;
    }
}

ExprNode::~ExprNode() {
    delete left;
    delete right;
}

ExprNodeType ExprNode::getType() const { return type; }

QString ExprNode::getVal() const { return val; }

DataType ExprNode::getDataType() const { return dataType; }

ExprNode* ExprNode::getLeft() const { return left; }

ExprNode* ExprNode::getRight() const { return right; }


int ExprNode::calculateCost(const WeightTable& weights) {
    return 0;   // Заглушка
}

bool ExprNode::isUnaryOperator(ExprNodeType type) {
    static const QSet<ExprNodeType> unaryOps = {
        NODE_PREF_INC, NODE_PREF_DEC, NODE_POST_INC, NODE_POST_DEC,
        NODE_LOG_NOT, NODE_NEGATIVE, NODE_BIT_NOT, NODE_CONVERT
    };
    return unaryOps.contains(type);
}

bool ExprNode::isBinaryOperator(ExprNodeType type) {
    static const QSet<ExprNodeType> binaryOps = {
        NODE_PLUS, NODE_MINUS, NODE_MULTIPLICATION, NODE_DIVISION,
        NODE_INTEGER_DIVISION, NODE_REMAINDER, NODE_LOG_AND, NODE_LOG_OR,
        NODE_EQUAL, NODE_NOT_EQUAL, NODE_LESS, NODE_GREATER,
        NODE_LESS_EQUAL, NODE_GREATER_EQUAL, NODE_BIT_AND, NODE_BIT_OR,
        NODE_BIT_XOR, NODE_SHIFT_LEFT, NODE_SHIFT_RIGHT, NODE_ASSIGNMENT,
        NODE_PLUS_EQUAL, NODE_MINUS_EQUAL, NODE_MULTI_EQUAL,
        NODE_DIV_EQUAL, NODE_REMAIN_EQUAL
    };
    return binaryOps.contains(type);
}

DataType ExprNode::getGeneralType(DataType left, DataType right) {
    // Порядок типов (в DataType) соответствует приоритету неявного преобразования
    return (left > right) ? left : right;
}

DataType ExprNode::getResultType(ExprNodeType op, DataType left, DataType right) {
    DataType result = TYPE_UNKNOWN;

    // Группируем операции по логике возвращаемого типа
    static const QSet<ExprNodeType> generalTypeOps = {
        NODE_PLUS, NODE_MINUS, NODE_MULTIPLICATION, NODE_DIVISION,
        NODE_INTEGER_DIVISION, NODE_REMAINDER, NODE_BIT_AND, NODE_BIT_OR,
        NODE_BIT_XOR, NODE_SHIFT_LEFT, NODE_SHIFT_RIGHT, NODE_BIT_NOT
    };

    static const QSet<ExprNodeType> boolTypeOps = {
        NODE_EQUAL, NODE_NOT_EQUAL, NODE_LESS, NODE_GREATER,
        NODE_LESS_EQUAL, NODE_GREATER_EQUAL, NODE_LOG_AND, NODE_LOG_OR, NODE_LOG_NOT
    };

    static const QSet<ExprNodeType> leftTypeOps = {
        NODE_PREF_INC, NODE_PREF_DEC, NODE_POST_INC, NODE_POST_DEC,
        NODE_ASSIGNMENT, NODE_PLUS_EQUAL, NODE_MINUS_EQUAL, NODE_MULTI_EQUAL,
        NODE_DIV_EQUAL, NODE_REMAIN_EQUAL, NODE_NEGATIVE, NODE_VALUE, NODE_VARIABLE
    };

    if (generalTypeOps.contains(op)) {
        result = getGeneralType(left, right);
    }
    else if (boolTypeOps.contains(op)) {
        result = TYPE_BOOL;
    }
    else if (leftTypeOps.contains(op)) {
        result = left;
    }
    else if (op == NODE_CONVERT) {
        result = right;
    }
    return result;
}

bool ExprNode::isConversionNecessary(DataType left, DataType right) {
    return left != right;
}
