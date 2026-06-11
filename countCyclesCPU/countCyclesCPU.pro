QT += core
QT -= gui

CONFIG += c++17 cmdline

#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000

SOURCES += \
    main.cpp \
    src/io/generatedot.cpp \
    src/io/readinputfile.cpp \
    src/io/writeoutputfile.cpp \
    src/models/error.cpp \
    src/models/exprnode.cpp \
    src/models/operandinfo.cpp \
    src/models/weightkey.cpp \
    src/models/weighttable.cpp \
    src/parser/parseoperandinfo.cpp \
    src/parser/parsetreefromstring.cpp \
    src/parser/parseweightinfo.cpp \
    src/utils/typeutils.cpp


HEADERS += \
    config.h \
    src/enums/DataType.h \
    src/enums/ErrorType.h \
    src/enums/ExprNodeType.h \
    src/io/generatedot.h \
    src/io/readinputfile.h \
    src/io/writeoutputfile.h \
    src/models/error.h \
    src/models/exprnode.h \
    src/models/operandinfo.h \
    src/models/weightkey.h \
    src/models/weighttable.h \
    src/parser/parseoperandinfo.h \
    src/parser/parsetreefromstring.h \
    src/parser/parseweightinfo.h \
    src/utils/typeutils.h


# Default rules for deployment
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin

!isEmpty(target.path): INSTALLS += target
