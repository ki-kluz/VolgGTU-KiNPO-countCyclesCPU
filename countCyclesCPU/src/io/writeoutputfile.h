#ifndef WRITEOUTPUTFILE_H
#define WRITEOUTPUTFILE_H

#include <QString>
#include <QSet>

#include "../models/exprnode.h"
#include "../models/error.h"


static QString generateInfix(ExprNode* node);

bool writeOutputFile(
    const QString& outputFile,
    ExprNode* root,
    int totalCost,
    QSet<Error>& errors
    );

#endif // WRITEOUTPUTFILE_H
