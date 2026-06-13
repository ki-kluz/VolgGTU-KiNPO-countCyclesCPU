#include "error.h"


Error::Error() {
    type = ERR_NONE;
    pos = -1;
}

void Error::setType(ErrorType type) { this->type = type; }

void Error::setInputFilePath(const QString& path) { this->inputFilePath = path; }

void Error::setOutputFilePath(const QString& path) { this->outputFilePath = path; }

void Error::setObjectName(const QString& name) { this->objectName = name; }

void Error::setExpected(const QString& expected) { this->expected = expected; }

void Error::setActual(const QString& actual) { this->actual = actual; }

void Error::setPos(int pos) { this->pos = pos; }

bool Error::operator==(const Error& other) const {
    return type == other.type &&
           pos == other.pos &&
           objectName == other.objectName &&
           expected == other.expected &&
           actual == other.actual &&
           inputFilePath == other.inputFilePath &&
           outputFilePath == other.outputFilePath;
}

// Функция хеширования (обязательна для QSet)
uint qHash(const Error& err, uint seed) {
    return qHash(static_cast<int>(err.type), seed) ^
           qHash(err.objectName, seed) ^
           qHash(err.pos, seed);
}


QString Error::generateErrorMessage() const {
    QString messageTemplate;
    QString positionInfo = (pos >= 0) ? QString(" [Position: %1]").arg(pos) : "";

    switch (type) {
    // === ОШИБКИ ФАЙЛОВ (ВВОД/ВЫВОД/ВЕСА) ===
    case ERR_INPUT_FILE_NOT_FOUND:
        return "Error: input file not found or inaccessible.";

    case ERR_INPUT_FILE_EMPTY:
        return "Error: input file is empty.";

    case ERR_WEIGHTS_FILE_NOT_FOUND:
        return "Error: weights file not found or inaccessible.";

    case ERR_WEIGHTS_FILE_EMPTY:
        return "Error: weights file is empty.";

    case ERR_OUTPUT_FILE_NOT_SPECIFIED:
        return "Error: output file is not specified.";

    case ERR_OUTPUT_FILE_CANNOT_CREATE:
        return "Error: unable to write output data (invalid path or insufficient permissions).";


    // === ОШИБКИ ДЕКЛАРАЦИИ И ТИПОВ ===
    case ERR_MISSING_TYPE_DECLARATION:
        messageTemplate = "Error: missing type declaration for variable '%1'.";
        return messageTemplate.arg(objectName) + positionInfo;

    case ERR_UNSUPPORTED_TYPE:
        messageTemplate = "Error: unsupported data type '%1'.";
        return messageTemplate.arg(actual) + positionInfo;

    case ERR_DUPLICATE_OPERAND:
        messageTemplate = "Error: duplicate declaration of operand '%1'.";
        return messageTemplate.arg(objectName) + positionInfo;


    // === ОШИБКИ CONST ===
    case ERR_OPERAND_OUT_OF_RANGE:
        // expected хранит строку с диапазоном, например "[-1000000.0 ... 1000000.0]"
        messageTemplate = "Error: operand '%1' is out of the allowed range %2.";
        return messageTemplate.arg(objectName, expected) + positionInfo;


    // === ОШИБКИ ВЫРАЖЕНИЙ И ОПЗ ===
    case ERR_INSUFFICIENT_OPERANDS:
        messageTemplate = "Error: insufficient operands for operator '%1'.";
        return messageTemplate.arg(objectName) + positionInfo;

    case ERR_EXCESS_OPERANDS:
        return "Error: invalid expression structure (excess operands detected)." + positionInfo;

    case ERR_INVALID_TOKEN:
        return "Error: invalid or unsupported token detected in expression." + positionInfo;

    case ERR_MAX_OPERATIONS_EXCEEDED:
        return "Error: maximum number of operations exceeded (20)." + positionInfo;


    // === ОШИБКИ ПАРСИНГА ФАЙЛА ВЕСОВ ===
    case ERR_INVALID_LINE_FORMAT:
        return "Error: invalid line format in weights file." + positionInfo;

    case ERR_MISSING_CONVERT_KEYWORD:
        return "Error: invalid type conversion rule (missing keyword convert)." + positionInfo;

    case ERR_UNRECOGNIZED_OBJECT:
        messageTemplate = "Error: unrecognized object '%1'.";
        return messageTemplate.arg(objectName) + positionInfo;

    case ERR_INVALID_WEIGHT_FORMAT:
        return "Error: operation weight must be a positive integer." + positionInfo;

    case ERR_WEIGHT_OUT_OF_RANGE:
        messageTemplate = "Error: operation weight is outside the allowed range %1.";
        return messageTemplate.arg(expected) + positionInfo;

    case ERR_SAME_TYPE_CONVERSION:
        return "Error: type conversion to the same type is not allowed." + positionInfo;

    case ERR_DUPLICATE_WEIGHT_DEFINITION:
        messageTemplate = "Error: duplicate weight definition for '%1'.";
        return messageTemplate.arg(objectName) + positionInfo;


    // === ОШИБКИ ВЫЧИСЛЕНИЙ (NEW) ===
    case ERR_UNSUPPORTED_OPERATION_FOR_TYPE:
        // objectName = операция (например, "++"), actual = тип (например, "bool")
        messageTemplate = "Error: operation '%1' is not supported for type '%2'.";
        return messageTemplate.arg(objectName, actual) + positionInfo;

    case ERR_NARROWING_CONVERSION:
        // actual = исходный тип (например, "double"), expected = целевой тип (например, "int")
        messageTemplate = "Error: unsupported narrowing conversion from '%1' to '%2'.";
        return messageTemplate.arg(actual, expected) + positionInfo;

    case ERR_MAX_COST_EXCEEDED:
        return "Error: maximum calculation cost exceeded (limit: 10000)." + positionInfo;


    // === БАЗОВЫЕ СЛУЧАИ ===
    case ERR_NONE:
        return "No error.";

    default:
        return QString("Error: unknown error code %1.").arg(static_cast<int>(type));
    }
}
