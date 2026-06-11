#ifndef TYPEUTILS_H
#define TYPEUTILS_H

#include <QString>
#include <QSet>

#include "../enums/DataType.h"
#include "../enums/ExprNodeType.h"
#include "../models/error.h"


namespace type_utils
{
    DataType stringToDataType(const QString& str);
    ExprNodeType stringToExprNodeType(const QString& str);

    QString dataTypeToString(DataType type);
    QString exprNodeTypeToString(ExprNodeType type);

    DataType getConstType(const QString& token, QSet<Error>& errors);
}

#endif // TYPEUTILS_H
