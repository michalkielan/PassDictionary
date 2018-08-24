#-------------------------------------------------
#
# Project created by QtCreator 2018-04-21T19:17:58
#
#-------------------------------------------------

QT += core gui
QT += printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PassDictionaryQt
TEMPLATE = app

QMAKE_CXXFLAGS += -Wall -Wextra -Wshadow -pedantic

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH+=$$PWD/inc/

SOURCES += \
    src/main.cpp \
    src/mainwindow.cpp \
    src/fileloader.cpp \
    src/clipboard.cpp \
    src/passdata.cpp \
    src/currentpassword.cpp \
    src/aboutwindow.cpp \
    src/printer.cpp

HEADERS += \
    inc/mainwindow.h \
    inc/fileloader.h \
    inc/clipboard.h \
    inc/passphrase.h \
    inc/passdata.h \
    inc/currentpassword.h \
    inc/aboutwindow.h \
    inc/printer.h

FORMS += \
    forms/mainwindow.ui \
    forms/aboutwindow.ui
