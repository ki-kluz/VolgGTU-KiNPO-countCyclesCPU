#ifndef EXPRNODETYPE_H
#define EXPRNODETYPE_H

typedef enum {
    NODE_UNKNOWN,       // (по умолчанию)
    // Базовые узлы (операнды)
    NODE_VALUE,                        // Значение (константа)
    NODE_VARIABLE,                     // Переменная

    // Арифметические операции
    NODE_PLUS,                         // Сложение (+)
    NODE_MINUS,                        // Вычитание (-)
    NODE_MULTIPLICATION,               // Умножение (*)
    NODE_DIVISION,                     // Деление (/)
    NODE_INTEGER_DIVISION,             // Целочисленное деление
    NODE_REMAINDER,                    // Остаток от деления (%)

    // Инкремент и декремент
    NODE_PREF_INC,                     // Префиксный инкремент (++x)
    NODE_PREF_DEC,                     // Префиксный декремент (--x)
    NODE_POST_INC,                     // Постфиксный инкремент (x++)
    NODE_POST_DEC,                     // Постфиксный декремент (x--)

    // Логические операции
    NODE_LOG_AND,                      // Логическое И (&&)
    NODE_LOG_OR,                       // Логическое ИЛИ (||)
    NODE_LOG_NOT,                      // Логическое НЕ (!)

    // Унарные операции
    NODE_NEGATIVE,                     // Унарный минус (-x)

    // Операции сравнения
    NODE_EQUAL,                        // Равно (==)
    NODE_NOT_EQUAL,                    // Не равно (!=)
    NODE_LESS,                         // Меньше (<)
    NODE_GREATER,                      // Больше (>)
    NODE_LESS_EQUAL,                   // Меньше или равно (<=)
    NODE_GREATER_EQUAL,                // Больше или равно (>=)

    // Побитовые операции
    NODE_BIT_AND,                      // Побитовое И (&)
    NODE_BIT_OR,                       // Побитовое ИЛИ (|)
    NODE_BIT_XOR,                      // Побитовое исключающее ИЛИ (^)
    NODE_BIT_NOT,                      // Побитовое НЕ (~)
    NODE_SHIFT_LEFT,                   // Сдвиг влево (<<)
    NODE_SHIFT_RIGHT,                  // Сдвиг вправо (>>)

    // Операции присваивания
    NODE_ASSIGNMENT,                   // Присваивание (=)
    NODE_PLUS_EQUAL,                   // Присваивание со сложением (+=)
    NODE_MINUS_EQUAL,                  // Присваивание с вычитанием (-=)
    NODE_MULTI_EQUAL,                  // Присваивание с умножением (*=)
    NODE_DIV_EQUAL,                    // Присваивание с делением (/=)
    NODE_REMAIN_EQUAL,                 // Присваивание с остатком (%=)

    // Преобразование типов
    NODE_CONVERT                       // Преобразование типа (convert)
} ExprNodeType;

#endif // EXPRNODETYPE_H
