#include <QFile>
#include <QTextStream>
#include <QSet>

#include "readfile.h"


bool readFile(const QString& filePath, QVector<QString>& fileLines, QSet<Error>& errors, FileType fileType) {
    QFile file(filePath);

    // Если удалось открыть файл для чтения и записи
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        Error err;
        // Выбираем тип ошибки в зависимости от файла
        if (fileType == FileType::Input) {
            err.setType(ERR_INPUT_FILE_NOT_FOUND);
        } else {
            err.setType(ERR_WEIGHTS_FILE_NOT_FOUND);
        }
        err.setInputFilePath(filePath);
        errors.insert(err);
        return false;
    }

    // QTextStream - поток чтения текста
    QTextStream in(&file);

    // Пока не достигнут конец файла
    while (!in.atEnd()) {
        // Считать строку до символа переноса ('\n')
        QString line = in.readLine();
        // Занести считанную строку в контейнер
        fileLines.push_back(line);
    }

    // Проверка пустого файла
    if (fileLines.isEmpty()) {
        Error err;
        if (fileType == FileType::Input) {
            err.setType(ERR_INPUT_FILE_EMPTY);
        } else {
            err.setType(ERR_WEIGHTS_FILE_EMPTY);
        }
        err.setInputFilePath(filePath);
        errors.insert(err);

        file.close();
        return false;
    }

    // Закрыть файл
    file.close();
    return true;
}
