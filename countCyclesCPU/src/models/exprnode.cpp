#include "exprnode.h"


ExprNode::ExprNode() {

}

ExprNode::ExprNode(
    ExprNodeType type,
    const QString& val,
    DataType dataType
) {

}

ExprNode::ExprNode(
    ExprNodeType type,
    DataType dataType,
    ExprNode* left,
    ExprNode* right
) {

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
    return false;   // Заглушка
}

bool ExprNode::isBinaryOperator(ExprNodeType type) {
    return false;   // Заглушка
}

DataType ExprNode::getGeneralType(DataType left, DataType right) {
    return TYPE_UNKNOWN;    // Заглушка
}

DataType ExprNode::getResultType(ExprNodeType op, DataType left, DataType right) {
    return TYPE_UNKNOWN;    // Заглушка
}

bool ExprNode::isConversionNecessary(DataType left, DataType right) {
    return false;   // Заглушка
}
