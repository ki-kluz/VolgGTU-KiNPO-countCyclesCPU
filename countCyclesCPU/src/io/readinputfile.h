#ifndef READINPUTFILE_H
#define READINPUTFILE_H

#include <QVector>
#include <QString>

#include "../models/error.h"


bool readInputFile(
    const QString& filePath,
    QVector<QString>& fileContent,
    QSet<Error>& errors
    );

#endif // READINPUTFILE_H
