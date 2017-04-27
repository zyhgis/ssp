#-------------------------------------------------
#
# Project created by QtCreator 2017-03-21T17:11:40
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = TSP
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        tsp.cpp \
    qcustomplot.cpp \
    dialog1.cpp \
    modelbuilder.cpp \
    pieceslist.cpp \
    puzzlewidget.cpp \
    mainwindow.cpp \
    observer.cpp \
    observerinput.cpp

HEADERS  += tsp.h \
    qcustomplot.h \
    dialog1.h \
    modelbuilder.h \
    pieceslist.h \
    puzzlewidget.h \
    mainwindow.h \
    observer.h \
    observerinput.h

FORMS    += tsp.ui \
    dialog1.ui \
    modelbuilder.ui \
    observer.ui \
    observerinput.ui

RESOURCES += \
    puzzle.qrc

DISTFILES += \
    puzzle.pro.user \
    example.jpg
