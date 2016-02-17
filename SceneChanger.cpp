#include "SceneChanger.hpp"

SceneChanger::SceneChanger() {}
/*
SceneChanger::SceneChanger(sf::Vector2f pos, std::string nextScene, sf::Vector2f nextScenePos) :
    _pos(pos),
    _nextScene(nextScene),
    _nextScenePos(nextScenePos) {}

SceneChanger::~SceneChanger() {}

std::string SceneChanger::getNextSceneName() {
    return _nextScene;
    _dir = directions::none;
}


sf::FloatRect SceneChanger::getRect(sf::Vector2f offset) {
    return sf::FloatRect(_bound.left+offset.x, _bound.top+offset.y, _bound.width, _bound.height);
}


directions SceneChanger::getChangeDirection() {
    return _dir;
}

void SceneChanger::setBounds(sf::FloatRect rect) {
    _bound = rect;
}

void SceneChanger::setDirection(directions dir) {
    _dir = dir;
}

directions SceneChanger::getOutsideDirection() {  
    if (int(_pos.x) == 0) return directions::left;
    else if (int(_pos.y) == 0) return directions::up;
    else if (int(_nextScenePos.x)==0) return directions::right;
    else if (int(_nextScenePos.y)==0) return directions::down;
    else return directions::directionsQtty;
}
*/
