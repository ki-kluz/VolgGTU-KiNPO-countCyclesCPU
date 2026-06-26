#ifndef PARSEWEIGHTINFO_H
#define PARSEWEIGHTINFO_H

/**
 * @file parseweightinfo.h
 * @brief Функция для разбора пользовательских весов операций.
 */

#include <QString>
#include <QSet>
#include <QPair>
#include <optional>
#include "../models/error.h"
#include "../models/weightkey.h"

namespace parse_utils
{
/**
 * @brief Разбирает строку из файла весов и формирует правило стоимости.
 * @param[in] weightStr Строка с правилом переопределения веса.
 * @param[in,out] errors Множество для записи ошибок парсинга.
 * @return std::optional, содержащий пару из ключа операции и её стоимости.
 */
std::optional<QPair<WeightKey, int>> parseWeightInfo(const QString& weightStr, QSet<Error>& errors);
}

#endif // PARSEWEIGHTINFO_H