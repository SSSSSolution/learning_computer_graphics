unix:MOC_DIR=.tmp
unix:OBJECTS_DIR=.tmp
unix:UI_DIR=.tmp

TEMPLATE = app
TARGET = test_sphere_circle
DESTDIR = ./test

DEPENDPATH += .
INCLUDEPATH += .
QT -= gui
QT += testlib

CONFIG += console
CONFIG -= app_bundle
CONFIG += testcase

# Input
HEADERS += sphere.h \
           circle.h

SOURCES += \
    test_sphere_circle.cpp
