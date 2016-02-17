#ifndef __DUNGEONSCENE_HPP__
#define __DUNGEONSCENE_HPP__

#include "ScenePlayable.hpp"
#include "DungeonDoor.hpp"

class DungeonScene : public ScenePlayable {
friend class Game;
public:
    DungeonScene(Game* g, sf::RenderWindow* w, sceneTypes sT, std::string name, std::string description);
    ~DungeonScene();

    void init(sf::Vector2f sceneIniCoord);
    void addDoor(DungeonDoor door,directions dir);

    sceneTypes getType();

protected:
    void update(float deltaTime);
    void render(sf::RenderTarget* target);
    void openDoors();
    void closeDoors();
    DungeonDoor _topDoor;
    DungeonDoor _botDoor;
    DungeonDoor _leftDoor;
    DungeonDoor _rightDoor;


};

#endif