#-------------------------------------------------
#
# Project created by QtCreator 2018-09-17T22:07:16
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets


TARGET = Sapper
TEMPLATE = app
QMAKE_LFLAGS_RELEASE += -static -static-libgcc

win32: RC_ICONS = $$PWD/bomb.ico

#QT += multimedia

SOURCES += main.cpp\
        mainwindow.cpp \
    saperfield.cpp

HEADERS  += mainwindow.h \
    saperfield.h

FORMS    += mainwindow.ui

RESOURCES += \
    sapper_pics.qrc
