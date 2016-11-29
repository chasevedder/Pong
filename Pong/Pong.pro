TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

LIBS += -L/usr/local/lib -lenet -lprotobuf -lSDL2 -lSDL2_image -lSDL2_ttf -ldl -lpthread
INCLUDES += /usr/local/include

QMAKE_CXXFLAGS += -std=c++11

SOURCES += main.cpp \
    paddle.cpp \
    ball.cpp \
    pausemenu.cpp \
    game.cpp \
    mainstate.cpp \
    mainmenu.cpp \
    multiplayerstate.cpp \
    sdltext.cpp \
    test.pb.cc
HEADERS += \
    paddle.h \
    ball.h \
    gamestate.h \
    pausemenu.h \
    gamestatemanager.h \
    game.h \
    mainstate.h \
    mainmenu.h \
    multiplayerstate.h \
    sdltext.h \
    test.pb.h

