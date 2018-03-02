#-------------------------------------------------
#
# Project created by QtCreator 2014-07-01T18:25:38
#
#-------------------------------------------------

QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
TARGET = ASearchVisualizer
TEMPLATE = app
QMAKE_CXXFLAGS += -std=c++11


SOURCES += main.cpp\
        mainwindow.cpp \
    tinyxml/tinyxmlparser.cpp \
    tinyxml/tinyxmlerror.cpp \
    tinyxml/tinyxml.cpp \
    tinyxml/tinystr.cpp \
    globalstep.cpp \
    map.cpp \
    logcontainer.cpp \
    mygraphicsview.cpp \
    infowindow.cpp \
    color_window.cpp

HEADERS  += mainwindow.h \
    tinyxml/tinyxml.h \
    tinyxml/tinystr.h \
    globalstep.h \
    point.h \
    map.h \
    logcontainer.h \
    colors.h \
    mygraphicsview.h \
    infowindow.h \
    color_window.h

FORMS    += mainwindow.ui \
    infowindow.ui \
    color_window.ui
