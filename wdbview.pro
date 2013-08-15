#-------------------------------------------------
#
# Project created by QtCreator 2013-07-18T10:27:36
#
#-------------------------------------------------

QT       += core gui sql

TARGET = wdbview
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    dataselector.cpp \
    griddatadisplay.cpp \
    databaseconnectiondialog.cpp \
    griddatadisplaywidget.cpp

HEADERS  += mainwindow.h \
    dataselector.h \
    griddatadisplay.h \
    databaseconnectiondialog.h \
    griddatadisplaywidget.h


isEmpty(PREFIX):PREFIX = /usr/local
BINDIR = $$PREFIX/bin
INSTALLS += target
target.path = $$BINDIR

OTHER_FILES += \
    README \
    COPYING

DISTFILES += $$OTHER_FILES
