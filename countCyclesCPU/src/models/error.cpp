#include "error.h"


Error::Error() {

}

void Error::setType(ErrorType type) { this->type = type; }

void Error::setInputFilePath(const QString& path) { this->inputFilePath = path; }

void Error::setOutputFilePath(const QString& path) { this->outputFilePath = path; }

void Error::setObjectName(const QString& name) { this->objectName = name; }

void Error::setExpected(const QString& expected) { this->expected = expected; }

void Error::setActual(const QString& actual) { this->actual = actual; }

void Error::setPos(int pos) { this->pos = pos; }

QString Error::generateErrorMessage() const {
    return QString();   // Заглушка
}

bool Error::operator==(const Error& other) const {
    return false;   // Заглушка
}

// Функция хеширования (обязательна для QSet)
uint qHash(const Error& err, uint seed) {
    return qHash(static_cast<int>(err.type), seed) ^
           qHash(err.objectName, seed) ^
           qHash(err.pos, seed);
}
