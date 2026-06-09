#include <QtTest>

#include "test_calculatecost.cpp"
#include "test_parsetreefromstring.cpp"
#include "test_getoperationcost.cpp"


int main(int argc, char *argv[])
{
    int status = 0;
    status |= QTest::qExec(new GetOperationCostTest, argc, argv);
    status |= QTest::qExec(new ParseTreeFromStringTest, argc, argv);
    status |= QTest::qExec(new CalculateCostTest, argc, argv);
    return status;
}
