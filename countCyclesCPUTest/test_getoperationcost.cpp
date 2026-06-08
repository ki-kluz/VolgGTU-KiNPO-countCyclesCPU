#include <QtTest>

#include "../countCyclesCPU/src/enums/ExprNodeType.h"
#include "../countCyclesCPU/src/enums/DataType.h"
#include "../countCyclesCPU/src/models/weighttable.h"
#include "../countCyclesCPU/src/models/weightkey.h"


class GetOperationCostTest : public QObject
{
    Q_OBJECT

public:
    GetOperationCostTest();
    ~GetOperationCostTest();

private slots:
    void test_getOperationCost_data();
    void test_getOperationCost();
};

GetOperationCostTest::GetOperationCostTest() {}
GetOperationCostTest::~GetOperationCostTest() {}

void GetOperationCostTest::test_getOperationCost_data()
{
    QTest::addColumn<ExprNodeType>("op");
    QTest::addColumn<DataType>("type");
    QTest::addColumn<bool>("useCustomWeight");
    QTest::addColumn<int>("customWeightValue");
    QTest::addColumn<int>("expectedCost");

    // Тест 1-4: Базовая арифметика
    QTest::newRow("1. Plus for int") << NODE_PLUS << TYPE_INT << false << 0 << 1;
    QTest::newRow("2. Plus for long long") << NODE_PLUS << TYPE_LLONG << false << 0 << 2;
    QTest::newRow("3. Plus for double") << NODE_PLUS << TYPE_DOUBLE << false << 0 << 3;
    QTest::newRow("4. Minus for float") << NODE_MINUS << TYPE_FLOAT << false << 0 << 3;

    // Тест 5-9: Умножение и деление
    QTest::newRow("5. Mul for short") << NODE_MULTIPLICATION << TYPE_SHORT << false << 0 << 4;
    QTest::newRow("6. Mul for long") << NODE_MULTIPLICATION << TYPE_LONG << false << 0 << 6;
    QTest::newRow("7. Div for double") << NODE_DIVISION << TYPE_DOUBLE << false << 0 << 20;
    QTest::newRow("8. IntDiv for int") << NODE_INTEGER_DIVISION << TYPE_INT << false << 0 << 40;
    QTest::newRow("9. Remainder for char") << NODE_REMAINDER << TYPE_CHAR << false << 0 << 40;

    // Тест 10-11: Инкременты
    QTest::newRow("10. PrefInc for int") << NODE_PREF_INC << TYPE_INT << false << 0 << 1;
    QTest::newRow("11. PostInc for float") << NODE_POST_INC << TYPE_FLOAT << false << 0 << 3;

    // Тест 12-14: Логические
    QTest::newRow("12. LogAnd for bool") << NODE_LOG_AND << TYPE_BOOL << false << 0 << 2;
    QTest::newRow("13. LogOr for bool") << NODE_LOG_OR << TYPE_BOOL << false << 0 << 2;
    QTest::newRow("14. LogNot for bool") << NODE_LOG_NOT << TYPE_BOOL << false << 0 << 1;

    // Тест 15-17: Сравнения
    QTest::newRow("15. Equal for char") << NODE_EQUAL << TYPE_CHAR << false << 0 << 1;
    QTest::newRow("16. Equal for long long") << NODE_EQUAL << TYPE_LLONG << false << 0 << 2;
    QTest::newRow("17. Equal for double") << NODE_EQUAL << TYPE_DOUBLE << false << 0 << 3;

    // Тест 18-19: Битовые
    QTest::newRow("18. BitAnd for int") << NODE_BIT_AND << TYPE_INT << false << 0 << 1;
    QTest::newRow("19. ShiftLeft for long") << NODE_SHIFT_LEFT << TYPE_LONG << false << 0 << 2;

    // Тест 20-22: Присваивания
    QTest::newRow("20. Assignment for int") << NODE_ASSIGNMENT << TYPE_INT << false << 0 << 1;
    QTest::newRow("21. PlusEqual for int") << NODE_PLUS_EQUAL << TYPE_INT << false << 0 << 2;
    QTest::newRow("22. MultiEqual for float") << NODE_MULTI_EQUAL << TYPE_FLOAT << false << 0 << 21;

    // Тест 23: Пользовательский вес
    QTest::newRow("23. Custom weight for Plus double") << NODE_PLUS << TYPE_DOUBLE << true << 10 << 10;

    // Тест 24: Неизвестная операция
    QTest::newRow("24. Unknown operation") << NODE_UNKNOWN << TYPE_INT << false << 0 << 0;
}

void GetOperationCostTest::test_getOperationCost()
{
    QFETCH(ExprNodeType, op);
    QFETCH(DataType, type);
    QFETCH(bool, useCustomWeight);
    QFETCH(int, customWeightValue);
    QFETCH(int, expectedCost);

    // Получаем таблицу по умолчанию
    WeightTable table = WeightTable::getDefaultWeights();

    // Если тест требует пользовательского веса, добавляем его
    if (useCustomWeight) {
        WeightKey key(op, type, TYPE_UNKNOWN);
        table.addUserWeight(key, customWeightValue);
    }

    // Проверяем стоимость
    int actualCost = table.getOperationCost(op, type);
    QCOMPARE(actualCost, expectedCost);
}

#include "test_getoperationcost.moc"
