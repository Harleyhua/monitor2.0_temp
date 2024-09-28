CONFIG += c++11

DEFINES += QS_LOG_LINE_NUMBERS    # automatically writes the file and line for each log message
#DEFINES += QS_LOG_DISABLE         # logging code is replaced with a no-op

HEADERS += \
    $$PWD/include/QsLog.h \
    $$PWD/include/QsLogDest.h \
    $$PWD/include/QsLogDisableForThisFile.h \
    $$PWD/include/QsLogLevel.h

LIBS += -L$$PWD/bin -lQsLog2

