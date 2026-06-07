#include <QtTest>

// add necessary includes here

class ParseTreeFromStringTest : public QObject
{
    Q_OBJECT

public:
    ParseTreeFromStringTest();
    ~ParseTreeFromStringTest();

private slots:
    void test_case1();
};

ParseTreeFromStringTest::ParseTreeFromStringTest() {}

ParseTreeFromStringTest::~ParseTreeFromStringTest() {}

void ParseTreeFromStringTest::test_case1() {}

// QTEST_APPLESS_MAIN(TEST_parseTreeFromString)

#include "test_parsetreefromstring.moc"
