QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
include(./QsLog/QsLog.pri)
include(./libmodbus/libmodbus.pri)
include(./communication/communication.pri)
LIBS += -Ldll -lws2_32

SOURCES += \
    common.cpp \
    main.cpp \
    mainwindow.cpp \
    sys_mg/cm_mg.cpp \
    sys_mg/data_mg.cpp
HEADERS += \
    common.h \
    mainwindow.h \
    sys_mg/cm_mg.h \
    sys_mg/data_mg.h

FORMS += \
    mainwindow.ui \


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target



#RESOURCES += \
#    resources/res.qrc
RC_ICONS = temp.ico

#程序版本
VERSION = 0.2.2.1

#程序名称
QMAKE_TARGET_PRODUCT = "monitor_temp"


