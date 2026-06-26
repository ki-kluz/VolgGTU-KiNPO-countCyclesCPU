#ifndef WRITEOUTPUTFILE_H
#define WRITEOUTPUTFILE_H

/**
 * @file writeoutputfile.h
 * @brief Функции для записи результатов работы программы в выходной файл.
 */

#include <QString>
#include <QSet>
#include "../models/exprnode.h"
#include "../models/error.h"

/**
 * @brief Генерирует инфиксную запись выражения на основе синтаксического дерева.
 * @param[in] node Указатель на корневой узел дерева (или поддерева).
 * @return Строка, содержащая инфиксную запись выражения.
 */
static QString generateInfix(ExprNode* node);

/**
 * @brief Записывает итоговые результаты в выходной файл.
 * @param[in] outputFile Путь к выходному файлу.
 * @param[in] root Указатель на корневой узел дерева выражений.
 * @param[in] totalCost Суммарная стоимость вычисления выражения в тактах.
 * @param[in,out] errors Множество для записи ошибок.
 * @return true Если данные успешно записаны в файл.
 * @return false Если выходной файл не указан или его невозможно создать.
 */
bool writeOutputFile(const QString& outputFile, ExprNode* root, int totalCost, QSet<Error>& errors);

#endif // WRITEOUTPUTFILE_H