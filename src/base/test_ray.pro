unix:MOC_DIR=.tmp
unix:OBJECTS_DIR=.tmp
unix:UI_DIR=.tmp

TEMPLATE = app
TARGET = test_ray
DESTDIR = ./test

DEPENDPATH += .
INCLUDEPATH += .
QT -= gui
QT += testlib

CONFIG += console
CONFIG -= app_bundle
CONFIG += testcase

# Input
HEADERS += ray3.h

SOURCES += \
    test_ray.cpp
