#include <QFile>
#include <QTextStream>

#include "readinputfile.h"


bool readInputFile(const QString& inputFile, QVector<QString>& inputLines, QSet<Error>& errors) {
    QFile file(inputFile);

    // Проверка существования файла
    if (!file.exists()) {
        // error.setType(ERR_INPUT_FILE_NOT_FOUND);
        // error.setInputFilePath(inputFile);
        return false;
    }

    /*Варианты открытия файла:
     - QIODevice::ReadOnly   - только чтение файла
     - QIODevice::Text       - обработка '\n', кодировок и переносов
     - QIODevice::WriteOnly  - только запись в файл
     - QIODevice::ReadWrite  - чтение и запись*/

    // Открыть входной файл только для чтения
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        // error.setType(ERR_INPUT_FILE);
        // error.setInputFilePath(inputFile);
        return false;
    }

    // QTextStream - поток чтения текста
    QTextStream in(&file);
    // Пока не достигнут конец файла
    while (!in.atEnd()) {
        // Считать строку до символа переноса ('\n')
        QString line = in.readLine();
        // Занести считанную строку в контейнер
        inputLines.push_back(line);
    }

    // Проверка пустого файла
    if (inputLines.isEmpty()) {
        // error.setType(ERR_INPUT_FILE_EMPTY);
        // error.setInputFilePath(inputFile);
        return false;
    }

    // Закрыть входной файл
    file.close();
    return true;
}
