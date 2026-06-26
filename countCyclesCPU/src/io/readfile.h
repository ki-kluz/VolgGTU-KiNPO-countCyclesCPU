#ifndef READFILE_H
#define READFILE_H

/**
 * @file readfile.h
 * @brief Универсальные функции для чтения входных данных и файла весов.
 */

#include <QVector>
#include <QString>
#include "../models/error.h"

/**
 * @brief Перечисление типов читаемых файлов.
 *
 * Используется для определения контекста чтения и генерации
 * соответствующих типов ошибок (например, ERR_INPUT_FILE_NOT_FOUND
 * или ERR_WEIGHTS_FILE_NOT_FOUND).
 */
enum class FileType {
    Input,  ///< Входной файл с выражением и типами переменных
    Weight  ///< Файл с пользовательскими весами операций
};

/**
 * @brief Универсальная функция чтения данных из текстового файла.
 *
 * @param[in] filePath Путь к читаемому файлу.
 * @param[out] fileContent Контейнер (вектор), куда будут записаны прочитанные строки.
 * @param[in,out] errors Множество для записи возникающих ошибок.
 * @param[in] fileType Тип файла (Input или Weight), определяющий код ошибки.
 *
 * @return true Если файл успешно открыт и прочитан (не пустой).
 * @return false Если произошла ошибка доступа или файл оказался пустым.
 */
bool readFile(
    const QString& filePath,
    QVector<QString>& fileContent,
    QSet<Error>& errors,
    FileType fileType
    );

#endif // READFILE_H