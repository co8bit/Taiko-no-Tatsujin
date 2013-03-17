#-------------------------------------------------
#
# Project created by QtCreator 2013-03-17T15:28:41
#
#-------------------------------------------------

QT       += core gui\
            phonon

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Taiko-no-Tatsujin
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    midi.cpp \
    note.cpp

HEADERS  += mainwindow.h \
    midi.h \
    note.h

FORMS    += mainwindow.ui

RESOURCES += \
    resources.qrc
