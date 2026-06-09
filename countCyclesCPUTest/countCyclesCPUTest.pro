QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += \
            main.cpp \
            test_calculatecost.cpp \
            test_getoperationcost.cpp \
            test_parsetreefromstring.cpp \
            ../countCyclesCPU/src/models/error.cpp \
            ../countCyclesCPU/src/models/exprnode.cpp \
            ../countCyclesCPU/src/models/operandinfo.cpp \
            ../countCyclesCPU/src/models/weightkey.cpp \
            ../countCyclesCPU/src/models/weighttable.cpp \
            ../countCyclesCPU/src/parser/parseoperandinfo.cpp \
            ../countCyclesCPU/src/parser/parsetreefromstring.cpp \
            ../countCyclesCPU/src/parser/parseweightinfo.cpp
