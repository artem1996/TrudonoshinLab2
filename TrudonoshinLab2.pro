#-------------------------------------------------
#
# Project created by QtCreator 2016-11-25T10:36:13
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = TrudonoshinLab2
TEMPLATE = app


SOURCES += main.cpp\
        mkewindow.cpp \
    gauss.cpp \
    qcustomplot.cpp \
    equation.cpp \
    boundarycondition.cpp

HEADERS  += mkewindow.h \
    gauss.h \
    qcustomplot.h \
    equation.h \
    boundarycondition.h

FORMS    += mkewindow.ui
