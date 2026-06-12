#include <QtTest>
#include <QSet>
#include <QMap>
#include <QStringList>

#include "../countCyclesCPU/src/models/exprnode.h"
#include "../countCyclesCPU/src/models/weighttable.h"
#include "../countCyclesCPU/src/models/error.h"
#include "../countCyclesCPU/src/models/operandinfo.h"
#include "../countCyclesCPU/src/parser/parseoperandinfo.h"
#include "../countCyclesCPU/src/parser/parseweightinfo.h"
#include "../countCyclesCPU/src/parser/parsetreefromstring.h"


class CalculateCostTest : public QObject
{
    Q_OBJECT

public:
    CalculateCostTest();
    ~CalculateCostTest();

private slots:
    void test_calculateCost_data();
    void test_calculateCost();
};

CalculateCostTest::CalculateCostTest() {}
CalculateCostTest::~CalculateCostTest() {}

void CalculateCostTest::test_calculateCost_data()
{
    QTest::addColumn<QString>("exprStr");
    QTest::addColumn<QStringList>("varsStr");
    QTest::addColumn<QStringList>("weightsStr");
    QTest::addColumn<int>("expectedCost");
    QTest::addColumn<QSet<Error>>("expectedErrors");

    QSet<Error> expErrors;
    Error err;

    // Тест 1: Сложение двух int (базовый случай)
    expErrors.clear();
    QTest::newRow("1. int + int")
        << "a b +" << QStringList{"a int", "b int"} << QStringList{} << 1 << expErrors;

    // Тест 2: Сложение двух double
    QTest::newRow("2. double + double")
        << "x y +" << QStringList{"x double", "y double"} << QStringList{} << 3 << expErrors;

    // Тест 3: Сложение char и short (оба целые, неявное расширение до int)
    QTest::newRow("3. char + short -> int")
        << "c s +" << QStringList{"c char", "s short"} << QStringList{} << 3 << expErrors;

    // Тест 4: Сложение int и double (преобразование int -> double)
    QTest::newRow("4. int + double -> double")
        << "a b +" << QStringList{"a int", "b double"} << QStringList{} << 7 << expErrors;

    // Тест 5: Умножение long long на long long
    QTest::newRow("5. llong * llong")
        << "p q *" << QStringList{"p llong", "q llong"} << QStringList{} << 6 << expErrors;

    // Тест 6: Деление float на float
    QTest::newRow("6. float / float")
        << "x y /" << QStringList{"x float", "y float"} << QStringList{} << 20 << expErrors;

    // Тест 7: Логическое И bool и bool
    QTest::newRow("7. bool && bool")
        << "a b &&" << QStringList{"a bool", "b bool"} << QStringList{} << 2 << expErrors;

    // Тест 8: Логическое НЕ bool (унарная операция)
    QTest::newRow("8. ! bool")
        << "a !" << QStringList{"a bool"} << QStringList{} << 1 << expErrors;

    // Тест 9: Сравнение char и char
    QTest::newRow("9. char == char")
        << "a b ==" << QStringList{"a char", "b char"} << QStringList{} << 1 << expErrors;

    // Тест 10: Битовый сдвиг int
    QTest::newRow("10. int <<")
        << "a 2 <<" << QStringList{"a int"} << QStringList{} << 1 << expErrors;

    // Тест 11: Присваивание double
    QTest::newRow("11. double =")
        << "a b =" << QStringList{"a double", "b double"} << QStringList{} << 1 << expErrors;

    // Тест 12: Сложное выражение (3 операции, разные типы)
    QTest::newRow("12. Complex expression (3 ops)")
        << "a b c * +" << QStringList{"a int", "b double", "c float"} << QStringList{} << 14 << expErrors;

    // Тест 13: Выражение с 1 операцией – константа 1000000
    QTest::newRow("13. Constant 1000000")
        << "1000000" << QStringList{} << QStringList{} << 0 << expErrors;

    // Тест 14: Выражение с 1 операцией – константа вне диапазона
    expErrors.clear();
    err.setType(ERR_OPERAND_OUT_OF_RANGE);
    err.setObjectName("2000000");
    expErrors.insert(err);
    QTest::newRow("14. Constant out of range")
        << "2000000" << QStringList{} << QStringList{} << 0 << expErrors;

    // Тест 15: Вещественная константа с 20 знаками
    expErrors.clear();
    QTest::newRow("15. Float const 20 digits")
        << "0.12345678901234567890" << QStringList{} << QStringList{} << 0 << expErrors;

    // Тест 16: Вещественная константа вне диапазона
    expErrors.clear();
    err.setType(ERR_OPERAND_OUT_OF_RANGE);
    err.setObjectName("1000000.1");
    expErrors.insert(err);
    QTest::newRow("16. Float const out of range")
        << "1000000.1" << QStringList{} << QStringList{} << 0 << expErrors;

    // Тест 17: Операция ++ над bool
    expErrors.clear();
    err.setType(ERR_UNSUPPORTED_OPERATION_FOR_TYPE);
    expErrors.insert(err);
    QTest::newRow("17. ++ on bool")
        << "a ++_" << QStringList{"a bool"} << QStringList{} << 0 << expErrors;

    // Тест 18: Использование пользовательских весов
    expErrors.clear();
    QTest::newRow("18. Custom weight")
        << "a b +" << QStringList{"a int", "b int"} << QStringList{"+ int 10"} << 10 << expErrors;

    // Тест 19: Преобразование типа с пользовательским весом
    QTest::newRow("19. Custom convert weight")
        << "a b +" << QStringList{"a int", "b double"} << QStringList{"convert int double 2", "+ double 3"} << 5 << expErrors;

    // Тест 20: Суммарная стоимость больше 10000
    expErrors.clear();
    err.setType(ERR_MAX_COST_EXCEEDED);
    expErrors.insert(err);
    QTest::newRow("20. Max cost exceeded")
        << "a b +" << QStringList{"a int", "b int"} << QStringList{"+ int 10001"} << 0 << expErrors;

    // Тест 21: Логическое И int и int (недопустимо)
    expErrors.clear();
    err.setType(ERR_UNSUPPORTED_OPERATION_FOR_TYPE);
    expErrors.insert(err);
    QTest::newRow("21. && on int")
        << "a b &&" << QStringList{"a int", "b int"} << QStringList{} << 0 << expErrors;

    // Тест 22: Логическое ИЛИ float и float (недопустимо)
    expErrors.clear();
    err.setType(ERR_UNSUPPORTED_OPERATION_FOR_TYPE);
    expErrors.insert(err);
    QTest::newRow("22. || on float")
        << "a b ||" << QStringList{"a float", "b float"} << QStringList{} << 0 << expErrors;

    // Тест 23: Комплексный тест №1 (10 операций)
    expErrors.clear();
    QTest::newRow("23. Complex test 1")
        << "a -_ b c * d e / f > - g h && i j == | ||"
        << QStringList{"a int", "b int", "c short", "d int", "e double", "f double", "g bool", "h bool", "i int", "j int"}
        << QStringList{} << 58 << expErrors;

    // Тест 24: Комплексный тест №2 (15 операций)
    expErrors.clear();
    QTest::newRow("24. Complex test 2")
        << "a b + c * d e / f - g h > i j < && k l == m n & o p | q r ^ s t << u v >> w ! ="
        << QStringList{
               "a int", "b int", "c int", "d int", "e int",
               "f int", "g bool", "h bool", "i int", "j int",
               "k int", "l int", "m int", "n int", "o int",
               "p int", "q int", "r int", "s int", "t int",
               "u int", "v int", "w bool"
           }
        << QStringList{}
        << 237
        << expErrors;

    // Тест 25: Выражение с 20 операциями (максимум)
    QString expr20 = "a1 a2 +";
    QStringList vars20 = {"a1 int", "a2 int"};
    for (int i = 3; i <= 21; ++i) {
        expr20 += QString(" a%1 +").arg(i);
        vars20.append(QString("a%1 int").arg(i));
    }
    QTest::newRow("25. Expression 20 operations") << expr20 << vars20 << QStringList{} << 20 << expErrors;

    // Тест 26: Выражение с 21 операцией (превышение)
    QString expr21 = expr20 + " a22 +";
    QStringList vars21 = vars20;
    vars21.append("a22 int");
    expErrors.clear();
    err.setType(ERR_MAX_OPERATIONS_EXCEEDED);
    expErrors.insert(err);
    QTest::newRow("26. Expression 21 operations (exceeded)") << expr21 << vars21 << QStringList{} << 0 << expErrors;
}

void CalculateCostTest::test_calculateCost()
{
    QFETCH(QString, exprStr);
    QFETCH(QStringList, varsStr);
    QFETCH(QStringList, weightsStr);
    QFETCH(int, expectedCost);
    QFETCH(QSet<Error>, expectedErrors);

    QSet<Error> actualErrors;

    // Парсим переменные
    QMap<QString, DataType> operandsInfo;
    for (const QString& varStr : varsStr) {
        OperandInfo opInfo = parse_utils::parseOperandInfo(varStr, actualErrors);
        if (opInfo.type != TYPE_UNKNOWN) {
            operandsInfo.insert(opInfo.name, opInfo.type);
        }
    }

    // Парсим веса
    WeightTable weightTable = WeightTable::getDefaultWeights();
    for (const QString& wStr : weightsStr) {
        auto weightOpt = parse_utils::parseWeightInfo(wStr, actualErrors);
        if (weightOpt.has_value()) {
            weightTable.addUserWeight(weightOpt->first, weightOpt->second);
        }
    }

    // Строим дерево
    ExprNode* root = parse_utils::parseTreeFromString(exprStr, operandsInfo, actualErrors);

    // Считаем стоимость
    int actualCost = 0;
    if (root != nullptr) {
        actualCost = root->calculateCost(weightTable, actualErrors);
        delete root;
    }

    // Проверяем результаты
    QCOMPARE(actualCost, expectedCost);
    QCOMPARE(actualErrors.size(), expectedErrors.size());
}

#include "test_calculatecost.moc"
