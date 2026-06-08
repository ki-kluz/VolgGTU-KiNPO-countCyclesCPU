#ifndef PARSEWEIGHTINFO_H
#define PARSEWEIGHTINFO_H

#include <QString>
#include <QSet>
#include <QPair>
#include <optional>

#include "src/models/error.h"
#include "src/models/weightkey.h"


namespace parse_utils
{
    std::optional<QPair<WeightKey, int>> parseWeightInfo(
        const QString& weightStr,
        QSet<Error>& errors
    );
}

#endif
