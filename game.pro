TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
LIBS += -lsfml-audio -lsfml-graphics -lsfml-network -lsfml-window -lsfml-system

QMAKE_CXXFLAGS += -std=c++11

SOURCES += main.cpp \
        utils.cpp \
        Resources.cpp \
        Game.cpp \
        Scene.cpp \
        SceneChanger.cpp \
        Collisionable.cpp \
    	Effect.cpp \
    GUI/Button.cpp \
    GUI/Container.cpp \
    GUI/Frame.cpp \
    GUI/ImgButton.cpp \
    GUI/ImgTextButton.cpp \
    GUI/Label.cpp \
    GUI/Layout.cpp \
    GUI/TextButton.cpp \
    GUI/VLayout.cpp \
    GUI/HLayout.cpp \
    GUI/Widget.cpp \
    TextBox.cpp \
    SoundManager.cpp \
    DataManager.cpp \
    StatsBar.cpp \
    TextBoxManager.cpp \
    InputManager.cpp \
    SceneTest.cpp

HEADERS += utils.hpp \
        Resources.cpp \
        Game.cpp \
        Scene.hpp \
        SceneChanger.hpp \
        Collisionable.hpp \
    	Effect.hpp \
    GUI/Button.hpp \
    GUI/Container.hpp \
    GUI/ImgButton.hpp \
    GUI/ImgTextButton.hpp \
    GUI/Label.hpp \
    GUI/Layout.hpp \
    GUI/TextButton.hpp \
    GUI/VLayout.hpp \
    GUI/HLayout.hpp \
    GUI/Widget.hpp \
    GUI/Frame.hpp \
    TextBox.hpp \
    SoundManager.hpp \
    DataManager.hpp \
    StatsBar.hpp \
    TextBoxManager.hpp \
    InputManager.hpp \
    SceneTest.hpp
