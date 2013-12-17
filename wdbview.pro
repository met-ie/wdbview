#-------------------------------------------------
#
# Project created by QtCreator 2013-07-18T10:27:36
#
#-------------------------------------------------

QT       += core gui sql

TARGET = wdbview
TEMPLATE = app
VERSION = 1.1.1


SOURCES += main.cpp\
        mainwindow.cpp \
    dataselector.cpp \
    griddatadisplay.cpp \
    databaseconnectiondialog.cpp \
    griddatadisplaywidget.cpp \
    griddata.cpp \
    gridmetadatadisplay.cpp

HEADERS  += mainwindow.h \
    dataselector.h \
    griddatadisplay.h \
    databaseconnectiondialog.h \
    griddatadisplaywidget.h \
    griddata.h \
    logging.h \
    gridmetadatadisplay.h


isEmpty(PREFIX):PREFIX = /usr/local

BINDIR = $$PREFIX/bin
INSTALLS += target
target.path = $$BINDIR

icon.files = share/no.met.wdb.wdbview.desktop
icon.path = $$PREFIX/share/applications

INSTALLS += icon

OTHER_FILES += \
    README \
    COPYING \
    share/no.met.wdb.wdbview.desktop

DISTFILES += $$OTHER_FILES
