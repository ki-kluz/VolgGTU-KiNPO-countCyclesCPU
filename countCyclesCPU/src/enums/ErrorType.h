#ifndef ERRORTYPE_H
#define ERRORTYPE_H

typedef enum {
    ERR_NONE,       // (по умолчанию)

    // Ошибки входного файла
    ERR_INPUT_FILE,                       // Ошибка входного файла
    ERR_INPUT_FILE_NOT_FOUND,             // Входной файл не существует или нет доступа
    ERR_INPUT_FILE_EMPTY,                 // Входной файл пуст

    // Ошибки декларации и типов
    ERR_MISSING_TYPE_DECLARATION,         // Неполное описание переменных - для операнда не указан тип
    ERR_UNSUPPORTED_TYPE,                 // Указан неподдерживаемый тип данных
    ERR_DUPLICATE_OPERAND,                // Дублирование описания операнда

    // Ошибки выражений и ОПЗ
    ERR_INSUFFICIENT_OPERANDS,            // Дефицит операндов для выполнения операции в ОПЗ
    ERR_EXCESS_OPERANDS,                  // Избыток операндов в выражении
    ERR_INVALID_TOKEN,                    // Присутствие в выражении недопустимых символов/операций
    ERR_MAX_OPERATIONS_EXCEEDED,          // Превышено допустимое количество операций
    ERR_OPERAND_OUT_OF_RANGE,             // Операнд не принадлежит указанному диапазону

    // Ошибки файла весов
    ERR_WEIGHTS_FILE,                     // Ошибка файла весов
    ERR_WEIGHTS_FILE_NOT_FOUND,           // Файл весов не существует или нет доступа
    ERR_WEIGHTS_FILE_EMPTY,               // Файл весов пуст
    ERR_INVALID_LINE_FORMAT,              // Строка не соответствует допустимому формату в файле весов

    // Ошибки парсинга и валидации весов
    ERR_MISSING_CONVERT_KEYWORD,          // Для преобразования типов отсутствует ключевое слово convert
    ERR_UNRECOGNIZED_OBJECT,              // Указан неизвестный тип данных или оператор
    ERR_WEIGHT_NOT_POSITIVE_INTEGER,      // Вес операции не является натуральным числом
    ERR_WEIGHT_OUT_OF_RANGE,              // Вес операции не принадлежит указанному диапазону
    ERR_DUPLICATE_WEIGHT_DEFINITION,      // Дублирование описания операции
    ERR_SAME_TYPE_CONVERSION,             // Конфликт типов при преобразовании в тот же тип

    // Ошибки выходного файла
    ERR_OUTPUT_FILE,                      // Ошибка выходного файла
    ERR_OUTPUT_FILE_NOT_SPECIFIED,        // Выходной файл не указан
    ERR_OUTPUT_FILE_CANNOT_CREATE         // Невозможно создать указанный выходной файл
} ErrorType;

#endif // ERRORTYPE_H
