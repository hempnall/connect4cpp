TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    board.cpp \
    game.cpp \
    player.cpp \
    manualplayer.cpp \
    autoplayer.cpp \
    testplayer.cpp

HEADERS += \
    board.h \
    game.h \
    player.h \
    manualplayer.h \
    autoplayer.h \
    testplayer.h

LIBS += -lstdc++ /usr/local/Cellar/boost/1.56.0/lib/libboost_system.a /usr/local/Cellar/boost/1.56.0/lib/libboost_chrono.a
# -L/usr/local/Cellar/boost/1.56.0/lib/
# /lib/gcrt0.o
INCLUDEPATH += /usr/local/Cellar/boost/1.56.0/include
QMAKE_CXXFLAGS += -std=c++11


