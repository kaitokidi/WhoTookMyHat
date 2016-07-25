#ifndef __UTILS_HPP__
#define __UTILS_HPP__

#define FRAMERATE 60

#define DATAPATH "Resources/Data/"
#define TEXTPATH "Resources/Texts/"
#define HATSPATH "Resources/Documents/"
#define SHADERPATH "Resources/Shaders/"
#define OPTIONSPATH "Resources/Options/"
#define TEXTURETPATH "Resources/Textures/"
#define LVLDESCIPTPATH "Resources/LevelDescriptors/"
#define TEXTUREDESCRIPTIONEXTENSION ".description"


#ifdef _WIN32
#define NOMINMAX
#define M_PI 3.14159
#define and &&
#define or ||
#define not !
#include "windirent.h" // read directory
#else
#include <dirent.h> // read directory
#endif


#include <map>
#include <list>
#include <memory>
#include <queue> // priority queue
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cfloat>
#include <climits>
#include <functional> // priority queue stuff

#include "DataManager.hpp"
#include "SoundManager.hpp"
#include "InputManager.hpp"

#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

static const bool DEBUGDRAW = false;

extern int hardmode;
extern std::string LANGUAGE;

template <class T>
void printError(T t){
    std::cout << " Resources:: Error loading... " << t << std::endl;
}

template <class T>
void internalPrintAll(T t) {
    std::cout << t;
}

template <class T, class... Args>
void internalPrintAll(const T& t, const Args&... args) {
    std::cout << t << " , ";
    internalPrintAll(args...);
}

template <class... Args>
void log(const Args&... args) {
    std::cout << "[";
    internalPrintAll(args...);
    std::cout << "]" << std::endl;
}

template <class... Args>
void m_log(const Args&... args) {
    std::cout << "[";
    internalPrintAll(args...);
    std::cout << "]" << std::endl;
}


//movement dir { down, left, right, up , none };
namespace direction {
    enum dir { down, left, right, up , none };
}
const int mx[5] = {0,   -1,     1,   0,   0   };
const int my[5] = {1,    0,     0,  -1,   0   };

const float TO_RADIANS = (1 / 180.0f) * (float ) M_PI;
const float TO_DEGREES = (1 / (float ) M_PI) * 180;
// Scene Status
namespace status{
    enum gameStatus {running, onMenu};
}

namespace InputAction {
  enum action {
      menuDown      ,
      menuUp        ,
      menuMovement  , // gamepad axis
      menuEnter     ,
      menuBack      ,
      down          , 
      up            ,
      p1movementY   , 
      left          , 
      right         ,
      p1movementX   ,
      action        ,
      pause         ,
	  reset			,
      shoot         ,
      hook          ,
      inputQtt
  };
}

//Scenes
enum sceneTypes {
    menu = -1,
    testScene = 0
};

// SpriteSheets
typedef std::vector< std::vector < sf::IntRect> > SpriteSheetDescription;

enum animationActions {
    action_none,
    action_skip,
    scrollUp,
    scrollDown,
    scrollLeft,
    scrollRight,
    rotateClockwhise,
    rotateCounterClockwhise,
    qttyAnimationActions
};

// Directions
enum directions {
    down    , // This have
    left    , // to be
    up      , // in this
    right   , // order
    none    ,
    topRight,
    topLeft ,
    botRight,
    botLeft ,

    directionsQtty
};

namespace constant{
    static const float gravity = 5;
    static const float friction = 4;
    static const float hookForce = 0.05;
    static const float playerJump = 850;
    static const float playerSpeed = 20;
    static const float playerRadious = 30;
    static const float shootMaxTime = 0.8;
    static const float playerMaxSpeed = 4.5;
}

//void log(std::string s);

void mlog(std::string s);

bool isInt(std::string s);

float myStof(std::string s);

int myStoi(std::string s);

bool myStob(std::string s);

float radToAngle(float rad);

float difference(float a, float b);

float floatangleToRad(float angle);

float getAngle(const sf::Vector2f &orig,const sf::Vector2f &des);

float getModule(const sf::Vector2f &orig, const sf::Vector2f &des);

bool isCollisioning(sf::Vector2f point1, float radius1, sf::Vector2f point2, float radius2);

directions pointsToDirection8(sf::Vector2f pos1, sf::Vector2f pos2, float rotation);

directions pointsToDirection4(sf::Vector2f pos1, sf::Vector2f pos2);

float directionsToAngle(directions dir);

sf::Vector2f getRelativeCenter(sf::Vector2f origen, sf::IntRect boundOr, sf::IntRect boundDest);

bool counterDirection(directions d1, directions d2);

int getHorizontal(directions dir);

int getVertical(directions dir);

sf::Vector2f getRandBounce(float speed, directions dir);

void print(std::string s);

int getSign(float n);

#endif
