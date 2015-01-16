TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    board.cpp \
    game.cpp \
    player.cpp \
    manualplayer.cpp \
    autoplayer.cpp

HEADERS += \
    board.h \
    game.h \
    player.h \
    manualplayer.h \
    autoplayer.h

LIBS += -lstdc++

QMAKE_CXXFLAGS += -std=c++0x
