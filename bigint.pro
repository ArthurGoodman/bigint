TEMPLATE = app
TARGET = bigint
CONFIG -= qt
CONFIG += console

LIBS += -L../gmp/lib -lgmp
INCLUDEPATH += ../gmp/include

SOURCES += main.cpp \
    bigint.cpp \
    pairing.cpp \
    intmap.cpp \
    gmpintmap.cpp \
    gmppairing.cpp

HEADERS += \
    bigint.h \
    pairing.h \
    intset.h \
    intmap.h \
    gmpintmap.h \
    gmpintset.h \
    gmppairing.h
