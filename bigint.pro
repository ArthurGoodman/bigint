TEMPLATE = app
TARGET = bigint
CONFIG -= qt
CONFIG += console

SOURCES += main.cpp \
    bigint.cpp \
    pairing.cpp \
    intmap.cpp

HEADERS += \
    bigint.h \
    pairing.h \
    intset.h \
    intmap.h
