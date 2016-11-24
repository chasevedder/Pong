TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

LIBS += -L/usr/local/lib -lSDL2 -lSDL2_image -lSDL2_ttf -ldl -lpthread
INCLUDES += /usr/local/include

SOURCES += main.cpp \
    pong.cpp \
    paddle.cpp \
    ball.cpp \
    pausemenu.cpp \
    game.cpp

HEADERS += \
    pong.h \
    paddle.h \
    ball.h \
    gamestate.h \
    pausemenu.h \
    gamestatemanager.h \
    game.h

