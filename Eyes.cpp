#include "Eyes.hpp"
#include "Resources.hpp"

Eyes::Eyes() {
    setTexture();
}

void Eyes::setTexture(){
    sprite.setTexture(Resources::eyes);
    sprite.setOrigin(sprite.getLocalBounds().width/2, sprite.getLocalBounds().height/2);
}

void Eyes::setSize(float sizeX, float sizeY){
    sprite.setScale(sizeX/sprite.getLocalBounds().width, sizeY/sprite.getLocalBounds().height);
    sprite.setOrigin(sprite.getLocalBounds().width/2, sprite.getLocalBounds().height/2);
}

void Eyes::draw(sf::RenderTarget * window){
    window->draw(sprite);
}

void Eyes::setPosition(sf::Vector2f pos){
    sprite.setPosition(pos);
}

sf::Vector2f Eyes::getSize(){
    return sf::Vector2f(sprite.getGlobalBounds().width, sprite.getGlobalBounds().height);
}
