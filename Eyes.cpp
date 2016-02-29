#include "Eyes.hpp"
#include "Resources.hpp"
#include "utils.hpp"

Eyes::Eyes() {
    setTexture();
}

void Eyes::setTexture(){
    sprite.setTexture(Resources::eyes);
    sprite.setOrigin(sprite.getLocalBounds().width/2, sprite.getLocalBounds().height/2);
    //print("init eyes");
}

void Eyes::setSize(float sizeX, float sizeY){
    sprite.setScale(sizeX/sprite.getLocalBounds().width, sizeY/sprite.getLocalBounds().height);
    sprite.setOrigin(sprite.getLocalBounds().width/2, sprite.getLocalBounds().height/2);
//    print("setsizeeyes");
}

void Eyes::draw(sf::RenderTarget * window){
    window->draw(sprite);
    //print("drawingeyes");
}

void Eyes::setPosition(sf::Vector2f pos){
    sprite.setPosition(pos);
    //print("setpositioneyes");
}

sf::Vector2f Eyes::getSize(){
    //print("getsizeeyes");
    return sf::Vector2f(sprite.getGlobalBounds().width, sprite.getGlobalBounds().height);
}
