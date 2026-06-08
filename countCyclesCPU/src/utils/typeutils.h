#ifndef TYPEUTILS_H
#define TYPEUTILS_H

#include <QString>

#include "src/enums/DataType.h"
#include "src/enums/ExprNodeType.h"


namespace type_utils
{
    DataType stringToDataType(const QString& str);
    ExprNodeType stringToExprNodeType(const QString& str);

    QString dataTypeToString(DataType type);
    QString exprNodeTypeToString(ExprNodeType type);

    DataType parseConstantType(const QString& token);
}

#endif // TYPEUTILS_H
