#include <QtTest>

// add necessary includes here

class GetOperationCostTest : public QObject
{
    Q_OBJECT

public:
    GetOperationCostTest();
    ~GetOperationCostTest();

private slots:
    void test_case1();
};

GetOperationCostTest::GetOperationCostTest() {}

GetOperationCostTest::~GetOperationCostTest() {}

void GetOperationCostTest::test_case1() {}

// QTEST_APPLESS_MAIN(TEST_getOperationCost)

#include "test_getoperationcost.moc"
