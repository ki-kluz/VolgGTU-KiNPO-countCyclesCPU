#include <QtTest>
#include <QMap>
#include <QSet>
#include <QString>

#include "../countCyclesCPU/src/parser/parsetreefromstring.h"
#include "../countCyclesCPU/src/models/exprnode.h"
#include "../countCyclesCPU/src/models/error.h"


class ParseTreeFromStringTest : public QObject
{
    Q_OBJECT

public:
    ParseTreeFromStringTest();
    ~ParseTreeFromStringTest();

private slots:
    void test_parseTreeFromString_data();
    void test_parseTreeFromString();
};

ParseTreeFromStringTest::ParseTreeFromStringTest() {}
ParseTreeFromStringTest::~ParseTreeFromStringTest() {}

void ParseTreeFromStringTest::test_parseTreeFromString_data()
{
    QTest::addColumn<QString>("exprStr");
    QTest::addColumn<QMap<QString, DataType>>("operandsInfo");
    QTest::addColumn<bool>("expectedSuccess");
    QTest::addColumn<QSet<Error>>("expectedErrors");

    QMap<QString, DataType> vars;
    QSet<Error> expErrors;
    Error err;

    // Тест 1: Одна переменная
    vars = {{"a", TYPE_INT}};
    expErrors.clear();
    QTest::newRow("1. Single variable") << "a" << vars << true << expErrors;

    // Тест 2: Одна константа
    vars.clear();
    expErrors.clear();
    QTest::newRow("2. Single constant") << "3" << vars << true << expErrors;

    // Тест 3: Бинарная операция
    vars = {{"a", TYPE_INT}, {"b", TYPE_INT}};
    expErrors.clear();
    QTest::newRow("3. Binary operation") << "a b +" << vars << true << expErrors;

    // Тест 4: Унарная операция
    vars = {{"a", TYPE_BOOL}};
    expErrors.clear();
    QTest::newRow("4. Unary operation") << "a !" << vars << true << expErrors;

    // Тест 5: Унарный минус
    vars = {{"a", TYPE_INT}};
    expErrors.clear();
    QTest::newRow("5. Unary minus") << "a -_" << vars << true << expErrors;

    // Тест 6: Смесь бинарных и унарных операций
    vars = {{"a", TYPE_BOOL}, {"b", TYPE_BOOL}};
    expErrors.clear();
    QTest::newRow("6. Mix of binary and unary") << "a b ! &&" << vars << true << expErrors;

    // Тест 7: Неподдерживаемая операция (тернарный оператор)
    vars = {{"a", TYPE_INT}, {"b", TYPE_INT}, {"c", TYPE_INT}};
    expErrors.clear();
    err = Error();
    err.setType(ERR_INVALID_TOKEN); err.setObjectName("?"); expErrors.insert(err);
    err.setType(ERR_INVALID_TOKEN); err.setObjectName(":"); expErrors.insert(err);
    err.setType(ERR_EXCESS_OPERANDS); err.setObjectName("a b c ? :"); expErrors.insert(err);
    QTest::newRow("7. Unsupported operation (ternary)") << "a b c ? :" << vars << false << expErrors;

    // Тест 8: Недостаток операндов для бинарной операции
    vars = {{"a", TYPE_INT}};
    expErrors.clear();
    err = Error();
    err.setType(ERR_INSUFFICIENT_OPERANDS);
    err.setObjectName("+");
    expErrors.insert(err);
    QTest::newRow("8. Insufficient operands (binary)") << "a +" << vars << false << expErrors;

    // Тест 9: Недостаток операндов для унарной операции
    vars.clear();
    expErrors.clear();
    err = Error();
    err.setType(ERR_INSUFFICIENT_OPERANDS);
    err.setObjectName("!");
    expErrors.insert(err);
    QTest::newRow("9. Insufficient operands (unary)") << "!" << vars << false << expErrors;

    // Тест 10: Избыток операндов (в стеке остаётся >1 узла)
    vars = {{"a", TYPE_INT}, {"b", TYPE_INT}, {"c", TYPE_INT}};
    expErrors.clear();
    err = Error();
    err.setType(ERR_EXCESS_OPERANDS);
    err.setObjectName("a b c +");
    expErrors.insert(err);
    QTest::newRow("10. Excess operands") << "a b c +" << vars << false << expErrors;

    // Тест 11: Пустое выражение
    vars.clear();
    expErrors.clear();
    err = Error();
    err.setType(ERR_INVALID_TOKEN);
    err.setObjectName("");
    expErrors.insert(err);
    QTest::newRow("11. Empty expression") << "" << vars << false << expErrors;

    // Тест 12: Неизвестная переменная
    vars = {{"a", TYPE_INT}};
    expErrors.clear();
    err = Error();
    err.setType(ERR_MISSING_TYPE_DECLARATION); err.setObjectName("b"); expErrors.insert(err);
    err.setType(ERR_INSUFFICIENT_OPERANDS); err.setObjectName("+"); expErrors.insert(err);
    QTest::newRow("12. Unknown variable") << "a b +" << vars << false << expErrors;

    // Тест 13: Целая const вне допустимого диапазона
    vars.clear();
    expErrors.clear();
    err = Error();
    err.setType(ERR_OPERAND_OUT_OF_RANGE); err.setObjectName("2000000"); expErrors.insert(err);
    err.setType(ERR_INVALID_TOKEN); err.setObjectName("2000000"); expErrors.insert(err);
    err.setType(ERR_EXCESS_OPERANDS); err.setObjectName("2000000"); expErrors.insert(err);
    QTest::newRow("13. Int const out of range") << "2000000" << vars << false << expErrors;

    // Тест 14: Вещественная const вне допустимого диапазона
    vars.clear();
    expErrors.clear();
    err = Error();
    err.setType(ERR_OPERAND_OUT_OF_RANGE); err.setObjectName("1000000.1"); expErrors.insert(err);
    err.setType(ERR_INVALID_TOKEN); err.setObjectName("1000000.1"); expErrors.insert(err);
    err.setType(ERR_EXCESS_OPERANDS); err.setObjectName("1000000.1"); expErrors.insert(err);
    QTest::newRow("14. Float const out of range") << "1000000.1" << vars << false << expErrors;

    // Тест 15: Недопустимый символ/оператор
    vars = {{"a", TYPE_INT}, {"b", TYPE_INT}};
    expErrors.clear();
    err = Error();
    err.setType(ERR_INVALID_TOKEN); err.setObjectName("@"); expErrors.insert(err);
    QTest::newRow("15. Invalid character") << "a @ b +" << vars << true << expErrors;

    // Тест 16: Операция ++ над bool (запрещённая комбинация) - проверяется в calculateCost, парсер должен отработать успешно
    vars = {{"a", TYPE_BOOL}};
    expErrors.clear();
    QTest::newRow("16. ++ on bool") << "a ++_" << vars << true << expErrors;

    // Тест 17: Очистка стека после ошибки
    vars.clear();
    expErrors.clear();
    err = Error();
    err.setType(ERR_INSUFFICIENT_OPERANDS);
    err.setObjectName("+");
    expErrors.insert(err);
    QTest::newRow("17. Stack cleanup on error") << "5 6 + 7 * +" << vars << false << expErrors;

    // Тест 18: Выражение из одних const
    vars.clear();
    expErrors.clear();
    QTest::newRow("18. Only constants") << "6 7 +" << vars << true << expErrors;

    // Тест 19: Вложенные унарные операции
    vars = {{"a", TYPE_BOOL}};
    expErrors.clear();
    QTest::newRow("19. Nested unary operations") << "a ! !" << vars << true << expErrors;

    // Тест 20: Бинарная операция с правой ассоциативностью
    vars = {{"a", TYPE_INT}, {"b", TYPE_INT}};
    expErrors.clear();
    QTest::newRow("20. Right-associative binary op") << "a b 5 = =" << vars << true << expErrors;

    // Тест 21: Выражение содержит ровно 20 операций (проверка границы)
    vars.clear();
    QString expr20 = "a1 a2 +";
    vars.insert("a1", TYPE_INT);
    vars.insert("a2", TYPE_INT);
    for (int i = 3; i <= 21; ++i) {
        QString varName = QString("a%1").arg(i);
        vars.insert(varName, TYPE_INT);
        expr20 += " " + varName + " +";
    }
    expErrors.clear();
    QTest::newRow("21. Exactly 20 operations") << expr20 << vars << true << expErrors;

    // Тест 22: Превышение максимального количества операций (21 операция)
    vars.clear();
    QString expr21 = "a1 a2 +";
    vars.insert("a1", TYPE_INT);
    vars.insert("a2", TYPE_INT);
    for (int i = 3; i <= 22; ++i) {
        QString varName = QString("a%1").arg(i);
        vars.insert(varName, TYPE_INT);
        expr21 += " " + varName + " +";
    }
    expErrors.clear();
    err = Error();
    err.setType(ERR_MAX_OPERATIONS_EXCEEDED);
    expErrors.insert(err);
    QTest::newRow("22. Max operations exceeded") << expr21 << vars << false << expErrors;

    // Тест 23: Комплексный тест (10 операций, отличный от «+»)
    vars = {
        {"a", TYPE_INT}, {"b", TYPE_INT}, {"c", TYPE_INT},
        {"d", TYPE_INT}, {"e", TYPE_INT}, {"f", TYPE_BOOL},
        {"g", TYPE_BOOL}, {"h", TYPE_INT}, {"i", TYPE_INT}
    };
    expErrors.clear();
    QTest::newRow("23. Complex test (10 ops)")
        << "a -_ b c * d / e > f g && h i & 1 << = || +"
        << vars << true << expErrors;
}

using OperandsMap = QMap<QString, DataType>;

void ParseTreeFromStringTest::test_parseTreeFromString()
{
    QFETCH(QString, exprStr);
    QFETCH(OperandsMap, operandsInfo);
    QFETCH(bool, expectedSuccess);
    QFETCH(QSet<Error>, expectedErrors);

    QSet<Error> actualErrors;

    // Вызываем тестируемую функцию из пространства имен parser
    ExprNode* root = parse_utils::parseTreeFromString(exprStr, operandsInfo, actualErrors);

    // Проверяем, создалось ли дерево
    bool actualSuccess = (root != nullptr);
    QCOMPARE(actualSuccess, expectedSuccess);

    // Проверяем совпадение количества ошибок
    QCOMPARE(actualErrors.size(), expectedErrors.size());

    // Очищаем память, если дерево было построено
    if (root) {
        delete root;
    }
}

#include "test_parsetreefromstring.moc"
