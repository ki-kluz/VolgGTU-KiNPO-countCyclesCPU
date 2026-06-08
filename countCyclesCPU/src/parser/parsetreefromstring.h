#ifndef PARSETREEFROMSTRING_H
#define PARSETREEFROMSTRING_H

#include <QString>
#include <QMap>
#include <QSet>

#include "../models/error.h"
#include "../models/exprnode.h"


namespace parse_utils
{
    ExprNode* parseTreeFromString(
        const QString& exprStr,
        const QMap<QString, DataType>& operandsInfo,
        QSet<Error>& errors
    );
}

#endif
