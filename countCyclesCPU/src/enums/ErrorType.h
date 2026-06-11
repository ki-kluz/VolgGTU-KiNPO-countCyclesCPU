#ifndef ERRORTYPE_H
#define ERRORTYPE_H

enum ErrorType {
    ERR_NONE,                               // (по умолчанию)

    // Ошибки файлов (ввод/вывод/веса) -> readInputFile/writeOutputFile
    ERR_INPUT_FILE_NOT_FOUND,               // Входной файл не существует или нет доступа
    ERR_INPUT_FILE_EMPTY,                   // Входной файл пуст
    ERR_WEIGHTS_FILE_NOT_FOUND,             // Файл весов не существует или нет доступа
    ERR_WEIGHTS_FILE_EMPTY,                 // Файл весов пуст
    ERR_OUTPUT_FILE_NOT_SPECIFIED,          // Выходной файл не указан
    ERR_OUTPUT_FILE_CANNOT_CREATE,          // Невозможно создать указанный выходной файл

    // Ошибки декларации и типов -> parseOperandInfo
    ERR_MISSING_TYPE_DECLARATION,           // Неполное описание переменных - для операнда не указан тип
    ERR_UNSUPPORTED_TYPE,                   // Указан неподдерживаемый тип данных
    ERR_DUPLICATE_OPERAND,                  // Дублирование описания операнда (в main)

    // Ошибки const -> getConstType
    ERR_OPERAND_OUT_OF_RANGE,               // Операнд не принадлежит указанному диапазону

    // Ошибки выражений и ОПЗ -> parseTreeFromString
    ERR_INSUFFICIENT_OPERANDS,              // Дефицит операндов для выполнения операции в ОПЗ
    ERR_EXCESS_OPERANDS,                    // Избыток операндов в выражении
    ERR_INVALID_TOKEN,                      // Присутствие в выражении недопустимых символов/операций
    ERR_MAX_OPERATIONS_EXCEEDED,            // Превышено допустимое количество операций

    // Ошибки парсинга файла весов -> parseWeightInfo
    ERR_INVALID_LINE_FORMAT,                // Строка не соответствует допустимому формату в файле весов
    ERR_MISSING_CONVERT_KEYWORD,            // Для преобразования типов отсутствует ключевое слово convert
    ERR_UNRECOGNIZED_OBJECT,                // Указан неизвестный тип данных (из DataType) или оператор
    ERR_INVALID_WEIGHT_FORMAT,              // Вес операции не является натуральным числом
    ERR_WEIGHT_OUT_OF_RANGE,                // Вес операции не принадлежит указанному диапазону
    ERR_SAME_TYPE_CONVERSION,               // Конфликт типов при преобразовании в тот же тип
    ERR_DUPLICATE_WEIGHT_DEFINITION,        // Дублирование описания операции (в main)

    // Ошибки вычислений -> ExprNode::calculateCost
    ERR_UNSUPPORTED_OPERATION_FOR_TYPE,     // Применение недопустимых операций к типу
    ERR_NARROWING_CONVERSION,               // Сужающее преобразование (от большей размерности к меньшей)
    ERR_MAX_COST_EXCEEDED                   // Превышение лимита стоимости в 10000 тактов
};

#endif // ERRORTYPE_H
