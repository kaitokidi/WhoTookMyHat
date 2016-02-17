#include "DungeonScene.hpp"
#include "Game.hpp"

DungeonScene::DungeonScene(Game* g, sf::RenderWindow* w, sceneTypes sT, std::string name, std::string description) :
    ScenePlayable(g,w,sT,name,description),
    _topDoor(0,sf::Vector2f(120,16),directions::up),
    _botDoor(0,sf::Vector2f(120,144),directions::down),
    _leftDoor(0,sf::Vector2f(16,80),directions::left),
    _rightDoor(0,sf::Vector2f(224,80),directions::right)
{
    _sceneIniCoord = sf::Vector2f(FLT_MAX,FLT_MAX);
}

DungeonScene::~DungeonScene() {

}

void DungeonScene::init(sf::Vector2f sceneIniCoord = sf::Vector2f(0,0)) {
	sf::Vector2f aux = _sceneIniCoord;
    ScenePlayable::init(sceneIniCoord);
    if (sceneIniCoord == aux) return;
    if (aux == sf::Vector2f(FLT_MAX,FLT_MAX)) {
        auto mapDoors = _map.getDungeonDoors();
        for (auto it = mapDoors.begin(); it != mapDoors.end(); ++it) addDoor(*(*it).first,(*it).second);
        addProp(&_topDoor);
    	addProp(&_botDoor);
    	addProp(&_leftDoor);
    	addProp(&_rightDoor);
	}
	_topDoor.setIniCoord(_sceneIniCoord);
	_botDoor.setIniCoord(_sceneIniCoord);
	_leftDoor.setIniCoord(_sceneIniCoord);
	_rightDoor.setIniCoord(_sceneIniCoord);
    _topDoor.setScene(this);
    _botDoor.setScene(this);
    _leftDoor.setScene(this);
    _rightDoor.setScene(this);
    if (DataManager::getBool(_sceneName+std::to_string(directions::up   ), false)) _topDoor.openWithKey();
    if (DataManager::getBool(_sceneName+std::to_string(directions::down ), false)) _botDoor.openWithKey();
    if (DataManager::getBool(_sceneName+std::to_string(directions::left ), false)) _leftDoor.openWithKey();
    if (DataManager::getBool(_sceneName+std::to_string(directions::right), false)) _rightDoor.openWithKey();
}

void DungeonScene::update(float deltaTime) {
    ScenePlayable::update(deltaTime);
    if (_enemies.empty()) openDoors();
    else closeDoors();
}

void DungeonScene::render(sf::RenderTarget* target) {
    ScenePlayable::render(target);
}

sceneTypes DungeonScene::getType(){
    return sceneTypes::dungeon;
}


void DungeonScene::addDoor(DungeonDoor door,directions dir) {
	if (dir == directions::up) _topDoor = door;
	else if (dir == directions::down) _botDoor = door;
	else if (dir == directions::left) _leftDoor = door;
	else if (dir == directions::right) _rightDoor = door;
	else {
		std::cout << "Wrong direction adding a door " << std::endl;
		exit(EXIT_FAILURE);
	}
}

void DungeonScene::openDoors() {
	_topDoor.open();
    _botDoor.open();
    _leftDoor.open();
    _rightDoor.open();
}

void DungeonScene::closeDoors() {
	_topDoor.close();
    _botDoor.close();
    _leftDoor.close();
    _rightDoor.close();
}
