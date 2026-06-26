#ifndef CONFIG_H
#define CONFIG_H

/**
 * @file config.h
 * @brief Глобальные константы и ограничения программы.
 */

/**
 * @namespace config
 * @brief Пространство имен, содержащее глобальные настройки и лимиты.
 */
namespace config
{
// === Ограничения постоянных (const) ===
constexpr double MIN_OPERAND_VALUE = -1000000.0; ///< Минимально допустимое значение константы
constexpr double MAX_OPERAND_VALUE =  1000000.0; ///< Максимально допустимое значение константы

// === Ограничения выражений ===
constexpr int MAX_OPERATIONS = 20;      ///< Максимальное количество операций в выражении
constexpr int MAX_COST = 10000;         ///< Максимальная суммарная стоимость вычисления (в тактах)
}

#endif // CONFIG_H