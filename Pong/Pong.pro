TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

LIBS += -L/usr/local/lib -lSDL2 -lSDL2_image -ldl -lpthread
INCLUDES += /usr/local/include

SOURCES += main.cpp \
    pong.cpp \
    paddle.cpp \
    ball.cpp \
    pausemenu.cpp

HEADERS += \
    pong.h \
    paddle.h \
    ball.h \
    gamestate.h \
    pausemenu.h

