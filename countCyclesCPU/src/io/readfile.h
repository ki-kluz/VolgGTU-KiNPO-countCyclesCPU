#ifndef READFILE_H
#define READFILE_H

#include <QVector>
#include <QString>

#include "../models/error.h"


enum class FileType {
    Input,
    Weight
};

bool readFile(
    const QString& filePath,
    QVector<QString>& fileContent,
    QSet<Error>& errors,
    FileType fileType
);

#endif // READFILE_H
