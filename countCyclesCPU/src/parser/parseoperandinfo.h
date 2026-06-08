#ifndef PARSEOPERANDINFO_H
#define PARSEOPERANDINFO_H

#include <QString>
#include <QSet>

#include "../models/error.h"
#include "../models/operandinfo.h"


namespace parse_utils
{
    OperandInfo parseOperandInfo(
        const QString& operandStr,
        QSet<Error>& errors
    );
}

#endif
