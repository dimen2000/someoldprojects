#-------------------------------------------------
#
# Project created by QtCreator 2018-06-01T21:51:42
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Nothing_interesting
TEMPLATE = app
QMAKE_LFLAGS += -static -static-libgcc
win32 {
        RC_FILE += icon.rc
        OTHER_FILES += icon.rc
}


SOURCES += main.cpp\
        mainwindow.cpp \
    cells.cpp

HEADERS  += mainwindow.h \
    cells.h

FORMS    += mainwindow.ui

DISTFILES +=

RESOURCES += \
    ni_pics.qrc
