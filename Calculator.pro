
QT += gui

QT += core

QT += widgets

CONFIG += c++11 console
CONFIG -= app_bundle


DEFINES += QT_DEPRECATED_WARNINGS


SOURCES += \
        calculatorwidget.cpp \
        logicalanswer.cpp \
        main.cpp \
        mainwindow.cpp \
        parametrslist.cpp \
        reversepolishnotation.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    calculatorwidget.h \
    logicalanswer.h \
    mainwindow.h \
    parametrslist.h \
    reversepolishnotation.h

RESOURCES     = application.qrc

DISTFILES += \
    reversepolishnotation.o
