#-------------------------------------------------
#
# Project created by QtCreator 2017-11-04T20:10:44
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Othello
TEMPLATE = app


SOURCES += main.cpp \
    juego.cpp \
    casilla.cpp \
    inteligencia.cpp \
    escena.cpp \
    vista.cpp \
    mainwindow.cpp

HEADERS  += \
    juego.h \
    casilla.h \
    inteligencia.h \
    MyLinkedList.h \
    node.h \
    escena.h \
    vista.h \
    mainwindow.h

RC_ICONS = Imagen/icon.ico
