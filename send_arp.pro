TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt
LIBS += -lpcap

SOURCES += \
    arpctl.cpp \
    infinfo.cpp \
    main.cpp

HEADERS += \
    arpctl.h \
    infinfo.h \
    packet.h
