#ifndef CONFIG_H
#define CONFIG_H

namespace config
{
    // === Ограничения постоянных (const) ===
    constexpr double MIN_OPERAND_VALUE = -1000000.0;
    constexpr double MAX_OPERAND_VALUE =  1000000.0;

    // === Ограничения выражений ===
    constexpr int MAX_OPERATIONS = 20;      // Максимальное количество операций в выражении
    constexpr int MAX_COST = 10000;         // Максимальная суммарная стоимость (в тактах)
}

#endif // CONFIG_H
