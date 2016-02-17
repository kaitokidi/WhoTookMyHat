#ifndef __UTILS_HPP__
#define __UTILS_HPP__

#define FRAMERATE 60

#define SCENEEXTENSION ".scene"
#define SCENEEXTENSIONSIZE 6

#define DATAPATH "Resources/Data/"
#define TEXTPATH "Resources/Texts/"
#define SHADERPATH "Resources/Shaders/"
#define TEXTURETPATH "Resources/Textures/"
#define LVLDESCIPTPATH "Resources/LevelDescriptors/"
#define TEXTUREDESCRIPTIONEXTENSION ".description"

#define TILESIZE 16
#define TILEOFFSET 1
#define TILESETWIDTH 18
#define TILESETHEIGH 8

#define WINDOWRATIOX 256
#define WINDOWRATIOY 176

#define DUNGEONSIZEX 256
#define DUNGEONSIZEY 176

#define UIRATIOX 1117
#define UIRATIOY 768

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

//movement dir { down, left, right, up , none };
const int mx[5] = {0,  -1,     1,       0,   0   };
const int my[5] = {1,    0,     0,   -1,   0   };

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
      p2movementY   , 
      left          , 
      right         ,
      p1movementX   ,
      p2movementX   ,  
      action        ,
      fairyAction   , 
      pause         ,
	  reset			,
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

enum spriteSheetsDescriptions {
    linkSpritesDescriptions,
    spriteDescriptionsQtt
};

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
// Animations
enum linkActions {
    move            ,
    attack          ,
    linkActionsQtt
};

// Sword Types
enum swordtypes {
    first,
    second,
    third,
    fourth,
    qttSwordTypes
};

// Props Types
enum propTypes {
    treeGreen   ,
    treeBrown   ,
    treeWhite   ,
    statueGreen ,
    statueBrown ,
    statueWhite ,
    bushGreen   ,
    bushBrown   ,
    grave       ,
    soldierGreen,
    soldierBrown,
    soldierWhite,
    propsQtty
};

enum dungeonHorDoorTypes {
    openTop,
    openBot,
    closTop,
    closBot,
    keysTop,
    keysBot,
    dungeonHorDoorQtty
};

enum dungeonVerDoorTypes {
    openRight,
    openLeft ,
    closRight,
    closLeft ,
    keysRight,
    keysLeft ,
    dungeonVerDoorQtty
};

enum objectType {
    halfHeal ,
    fullHeal ,
    life     ,
    rupee    ,
    rupee5   ,
    bomb     ,
    key      ,
    triforce ,
    triblue  ,
    objectsQtty
};

enum enemyType {
  octorok,
  ortorokBlue,
  penguin,
  enemyTypeQtty
};

// Directions
enum directions { //u were afraid i could change it to make it beautiful dindn't u ? xd
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

enum collisionMapMask {
  water = 1, // blue
  passage = 2, // green
  rock = 4, // red
  ground = 0, // ground (it have to be white :( I cry everytime)
  wall = 7, // walls

  collisionMapMaskQtty = -1
};

bool isInt(std::string s);

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

int getSign(float n);

#endif
