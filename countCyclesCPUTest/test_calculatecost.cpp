#include <QtTest>

// add necessary includes here

class CalculateCostTest : public QObject
{
    Q_OBJECT

public:
    CalculateCostTest();
    ~CalculateCostTest();

private slots:
    void test_case1();
};

CalculateCostTest::CalculateCostTest() {}

CalculateCostTest::~CalculateCostTest() {}

void CalculateCostTest::test_case1() {}

// QTEST_APPLESS_MAIN(TEST_calculateCost)

#include "test_calculatecost.moc"
