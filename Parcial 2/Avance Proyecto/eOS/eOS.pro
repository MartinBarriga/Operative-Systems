#-------------------------------------------------
#
# Project created by QtCreator 2018-03-20T11:49:19
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = eOS
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    navegador.cpp \
    shell.cpp \
    monitor.cpp \
    monitoreo.cpp

HEADERS  += mainwindow.h \
    navegador.h \
    shell.h \
    monitor.h \
    monitoreo.h

FORMS    += mainwindow.ui \
    navegador.ui \
    shell.ui \
    monitor.ui \
    monitoreo.ui

RESOURCES += \
    rscimg.qrc
