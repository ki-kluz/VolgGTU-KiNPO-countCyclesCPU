#include <QTextStream>
#include <QVector>
#include <QMap>
#include <QSet>

#include "src/io/readfile.h"
#include "src/io/writeoutputfile.h"

#include "src/parser/parseoperandinfo.h"
#include "src/parser/parseweightinfo.h"
#include "src/parser/parsetreefromstring.h"

#include "src/models/exprnode.h"
#include "src/models/operandinfo.h"
#include "src/models/error.h"


int main(int argc, char *argv[])
{
    QTextStream errStream(stderr);

    // Проверить корректность аргументов командной строки
    if (argc < 3 || argc > 4) {
        errStream << "Usage: countCyclesCPU <inputFile> [weightFile] <outputFile>\n";
        return 1;
    }

    // Разбираем входные параметры
    QString inputFile = argv[1];
    QString weightFile = (argc == 4) ? argv[2] : "";
    QString outputFile = (argc == 4) ? argv[3] : argv[2];

    // Контейнеры программы
    QVector<QString> inputLines;
    QVector<QString> weightLines;
    QMap<QString, DataType> varsInfo;   // Словарь для парсера дерева
    QSet<Error> errors;                 // Набор для сбора ошибок
    ExprNode* root = nullptr;

    // Считать данные из первого входного файла
    readFile(inputFile, inputLines, errors, FileType::Input);

    QString expression = "";
    if (!inputLines.isEmpty()) {
        expression = inputLines[0];
    }

    // Для каждой строки входного файла (начиная со второй)
    for (int i = 1; i < inputLines.size(); i++) {
        // Разобрать информацию переменной
        OperandInfo opInfo = parse_utils::parseOperandInfo(inputLines[i], errors);

        // Сохраняем в словарь (имя -> тип) для парсера дерева
        if (opInfo.type != TYPE_UNKNOWN) {
            // Проверка на дублирование операнда (согласно ErrorType)
            if (varsInfo.contains(opInfo.name)) {
                Error err;
                err.setType(ERR_DUPLICATE_OPERAND);
                err.setObjectName(opInfo.name);
                errors.insert(err);
            } else {
                varsInfo.insert(opInfo.name, opInfo.type);
            }
        }
    }

    // Получаем таблицу по умолчанию
    WeightTable weightTable = WeightTable::getDefaultWeights();

    // При наличии файла весов
    if (!weightFile.isEmpty()) {
        // Считать данные из второго входного файла
        readFile(weightFile, weightLines, errors, FileType::Weight);

        // Для каждой строки из файла весов
        for (const QString& line : weightLines) {
            // Разобрать веса
            auto weightOpt = parse_utils::parseWeightInfo(line, errors);

            // Добавить веса в пользовательскую таблицу
            if (weightOpt.has_value()) {
                // Пытаемся добавить вес в таблицу (если false -> ошибка дубликата)
                if (!weightTable.addUserWeight(weightOpt->first, weightOpt->second)) {
                    Error err;
                    err.setType(ERR_DUPLICATE_WEIGHT_DEFINITION);
                    err.setObjectName(line);
                    errors.insert(err);
                }
            }
        }
    }

    // Разобрать дерево из ОПЗ выражения
    if (errors.isEmpty() && !expression.isEmpty()) {
        root = parse_utils::parseTreeFromString(expression, varsInfo, errors);
    }

    // Если удалось считать данные без ошибок
    if (errors.isEmpty() && root != nullptr) {
        // Считать суммарное количество тактов процессора
        int totalCost = root->calculateCost(weightTable, errors);

        // Формируем выходной файл из узлов выражения ТОЛЬКО если расчет прошел успешно
        // (например, не было ERR_MAX_COST_EXCEEDED или ERR_UNSUPPORTED_OPERATION_FOR_TYPE)
        if (errors.isEmpty()) {
            writeOutputFile(outputFile, root, totalCost, errors);
        }
    }

    // Иначе (если были накоплены ошибки на любом из этапов)
    if (!errors.isEmpty()) {
        // Выводим все ошибки в консоль
        for (const Error& err : errors) {
            errStream << err.generateErrorMessage() << "\n";
        }
        if (root) { delete root; }
        return 1;
    }

    if (root) { delete root; }
    return 0;
}
