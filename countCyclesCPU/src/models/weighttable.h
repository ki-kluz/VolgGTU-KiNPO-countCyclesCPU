#ifndef WEIGHTTABLE_H
#define WEIGHTTABLE_H

/**
 * @file weighttable.h
 * @brief Класс для управления стоимостью (весами) операций.
 */

#include <QMap>
#include "../enums/DataType.h"
#include "../enums/ExprNodeType.h"
#include "../models/weightkey.h"

/**
 * @brief Таблица весов операций процессора.
 *
 * Хранит дефолтные стоимости операций и позволяет переопределять их
 * пользовательскими значениями из файла весов.
 */
class WeightTable
{
public:
    /** @brief Конструктор. Инициализирует дефолтные веса. */
    WeightTable();

    /**
     * @brief Получает итоговую стоимость по ключу.
     * @param[in] key Ключ операции.
     * @return Стоимость в тактах.
     */
    int getCost(WeightKey key) const;

    /**
     * @brief Удобная обертка для получения стоимости базовой операции.
     * @param[in] type Тип операции.
     * @param[in] operType Тип данных операндов.
     * @return Стоимость в тактах.
     */
    int getOperationCost(ExprNodeType type, DataType operType) const;

    /**
     * @brief Получает стоимость операции приведения типов (convert).
     * @param[in] leftType Исходный тип.
     * @param[in] rightType Целевой тип.
     * @return Стоимость конвертации в тактах.
     */
    int getConvertCost(DataType leftType, DataType rightType) const;

    /**
     * @brief Добавляет или перезаписывает пользовательский вес операции.
     * @param[in] key Ключ операции.
     * @param[in] cost Новая стоимость.
     * @return true при успешном добавлении.
     */
    bool addUserWeight(WeightKey key, int cost);

    /**
     * @brief Фабричный метод, возвращающий таблицу только с дефолтными весами.
     */
    static WeightTable getDefaultWeights();

private:
    QMap<WeightKey, int> defaultWeights;    ///< Словарь дефолтных весов (по умолчанию)
    QMap<WeightKey, int> userWeights;       ///< Словарь пользовательских весов (из файла)

    /** @brief Внутренний метод для заполнения словаря defaultWeights базовыми значениями. */
    void setDefaultWeights();
};

#endif // WEIGHTTABLE_H