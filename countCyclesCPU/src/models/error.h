#ifndef ERROR_H
#define ERROR_H

#include <QString>
#include <QHash>

#include "../enums/ErrorType.h"


class Error
{
public:
    Error();

    QString generateErrorMessage() const;

    void setType(ErrorType type);
    void setInputFilePath(const QString& path);
    void setOutputFilePath(const QString& path);
    void setObjectName(const QString& name);
    void setExpected(const QString& expected);
    void setActual(const QString& actual);
    void setPos(int pos);

    bool operator==(const Error& other) const;
    friend uint qHash(const Error& err, uint seed);

private:
    ErrorType type;             // Тип ошибки
    QString inputFilePath;      // Пути, откуда не удалось прочитать файл
    QString outputFilePath;     // Пути, куда не удалось записать файл
    QString objectName;         // Имени переменной / оператора / типа
    QString expected;           // Ожидаемого значения
    QString actual;             // Фактического значения
    int pos;                    // Позиции ошибочного символа (начиная с 1)
};

uint qHash(const Error& err, uint seed = 0);

#endif // ERROR_H
