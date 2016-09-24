TEMPLATE = app
TARGET = bigint
CONFIG -= qt
CONFIG += console

SOURCES += main.cpp \
    bigint.cpp \
    pairing.cpp

HEADERS += \
    bigint.h \
    intheap.h \
    pairing.h
