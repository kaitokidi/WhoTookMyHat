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
        Collisionable.cpp \
    	Effect.cpp \
    TextBox.cpp \
    SoundManager.cpp \
    DataManager.cpp \
    TextBoxManager.cpp \
    InputManager.cpp \
    SceneTest.cpp \
    Background.cpp \
    ScenePlayable.cpp \
    Player.cpp \
    Eyes.cpp \
    Hook.cpp \
    AnimatedCircle.cpp \
    Enemy.cpp \
    Bullet.cpp \
    EnemyBloc.cpp \
    EnemyFlying.cpp \
    SceneCutScene.cpp \
    EnemyBouncy.cpp \
    SceneTemporal.cpp \
    EnemyGhost.cpp \
    EnemyNinja.cpp \
    EnemyLog.cpp \
    EnemyShooter.cpp \
    EnemyBullet.cpp \
    EnemySnipper.cpp \
    EnemyBoss.cpp \
    SceneSelector.cpp \
    MyButton.cpp \
    SceneAnimation.cpp \
    ProgressionBar.cpp \
    LifeCounter.cpp

HEADERS += utils.hpp \
        Resources.cpp \
        Game.cpp \
        Scene.hpp \
        Collisionable.hpp \
    	Effect.hpp \
    TextBox.hpp \
    SoundManager.hpp \
    DataManager.hpp \
    TextBoxManager.hpp \
    InputManager.hpp \
    SceneTest.hpp \
    Background.hpp \
    ScenePlayable.hpp \
    Player.hpp \
    Eyes.hpp \
    Hook.hpp \
    AnimatedCircle.hpp \
    Enemy.hpp \
    Bullet.hpp \
    EnemyBloc.hpp \
    EnemyFlying.hpp \
    SceneCutScene.hpp \
    EnemyBouncy.hpp \
    SceneTemporal.hpp \
    EnemyGhost.hpp \
    EnemyNinja.hpp \
    EnemyLog.hpp \
    EnemyShooter.hpp \
    EnemyBullet.hpp \
    EnemySnipper.hpp \
    EnemyBoss.hpp \
    SceneSelector.hpp \
    MyButton.hpp \
    SceneAnimation.hpp \
    ProgressionBar.hpp \
    LifeCounter.hpp
