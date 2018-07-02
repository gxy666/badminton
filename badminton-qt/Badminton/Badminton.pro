#-------------------------------------------------
#
# Project created by QtCreator 2018-05-26T11:37:43
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Badminton
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
        oneplayerwindow.cpp \
        player.cpp \
        referee.cpp \
    musicthread.cpp \
    doubleplayerwindow.cpp \
    logdialog.cpp

HEADERS += \
        mainwindow.h \
        oneplayerwindow.h \
        player.h \
        referee.h \
    musicthread.h \
    doubleplayerwindow.h \
    logdialog.h

FORMS += \
        mainwindow.ui \
        oneplayerwindow.ui \
    doubleplayerwindow.ui \
    logdialog.ui

RESOURCES += \
    resource.qrc
CONFIG += \
        resources_big
QT  += \
        network \
        widgets \
        multimedia

DISTFILES +=
