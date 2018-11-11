TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    journalrecord.cpp \
    journalcontainer.cpp \
    main.cpp \
    dutyrecord.cpp \
    baserecord.cpp

HEADERS += \
    journalrecord.h \
    journalcontainer.h \
    dutyrecord.h \
    baserecord.h

FORMS +=
