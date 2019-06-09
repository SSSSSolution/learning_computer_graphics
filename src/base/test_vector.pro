unix:MOC_DIR=.tmp
unix:OBJECTS_DIR=.tmp
unix:UI_DIR=.tmp

TEMPLATE = app
TARGET = test_vector
DESTDIR = ./test

DEPENDPATH += .
INCLUDEPATH += .
QT -= gui
QT += testlib

CONFIG += console
CONFIG -= app_bundle
CONFIG += testcase

# Input
HEADERS += vector2.h \
    vector3.h \
    vector4.h \
    vectorn.h \
    matrix.h \
    point3.h

SOURCES += \
    test_vector.cpp
