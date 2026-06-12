#include "operandinfo.h"


OperandInfo::OperandInfo() {
    name = "";
    value = "";
    type = TYPE_UNKNOWN;
}

OperandInfo::OperandInfo(const QString& name, const QString& value, DataType type) {
    this->name = name;
    this->value = value;
    this->type = type;
}
