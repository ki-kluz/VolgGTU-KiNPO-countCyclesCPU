#ifndef ERROR_H
#define ERROR_H

/**
 * @file error.h
 * @brief Содержит класс Error для представления и обработки ошибок.
 */

#include <QString>
#include <QHash>
#include "../enums/ErrorType.h"

/**
 * @brief Класс для инкапсуляции данных об ошибке.
 *
 * Хранит тип ошибки, позицию, имена переменных и ожидаемые/фактические значения.
 * Отвечает за генерацию подробного человекочитаемого сообщения.
 */
class Error
{
public:
    /**
     * @brief Конструктор по умолчанию.
     * Инициализирует ошибку типом ERR_NONE и позицией -1.
     */
    Error();

    /**
     * @brief Генерирует форматированное текстовое сообщение об ошибке.
     * @return Строка с подробным описанием ошибки на основе её типа и параметров.
     */
    QString generateErrorMessage() const;

    /** @brief Устанавливает тип ошибки. */
    void setType(ErrorType type);
    /** @brief Устанавливает путь к входному файлу (для файловых ошибок). */
    void setInputFilePath(const QString& path);
    /** @brief Устанавливает путь к выходному файлу (для файловых ошибок). */
    void setOutputFilePath(const QString& path);
    /** @brief Устанавливает имя проблемного объекта (переменной, оператора). */
    void setObjectName(const QString& name);
    /** @brief Устанавливает ожидаемое значение или диапазон. */
    void setExpected(const QString& expected);
    /** @brief Устанавливает фактическое значение или тип. */
    void setActual(const QString& actual);
    /** @brief Устанавливает позицию ошибки в выражении. */
    void setPos(int pos);

    /**
     * @brief Оператор сравнения на равенство.
     * @param[in] other Другой объект Error для сравнения.
     * @return true Если типы и параметры ошибок совпадают.
     */
    bool operator==(const Error& other) const;

    /**
     * @brief Дружественная функция для вычисления хэша (нужна для работы QSet).
     * @param[in] err Объект ошибки.
     * @param[in] seed Базовое значение для хэширования.
     * @return Вычисленный хэш.
     */
    friend uint qHash(const Error& err, uint seed);

private:
    ErrorType type;             ///< Тип ошибки
    QString inputFilePath;      ///< Путь, откуда не удалось прочитать файл
    QString outputFilePath;     ///< Путь, куда не удалось записать файл
    QString objectName;         ///< Имя переменной / оператора / типа
    QString expected;           ///< Ожидаемое значение или диапазон
    QString actual;             ///< Фактическое значение
    int pos;                    ///< Позиция ошибочного символа (начиная с 1)
};

/**
 * @brief Глобальная функция вычисления хэша для QSet<Error>.
 */
uint qHash(const Error& err, uint seed = 0);

#endif // ERROR_H