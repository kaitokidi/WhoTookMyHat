#include <iostream>
#include "Hook.hpp"
#include "Resources.hpp"
//#include "ResourceManager.hpp"

Hook::Hook(){
    simple = true;
    size = 20;
}

Hook::Hook(float w){
    simple = true;
    size = w;
}

Hook::Hook(float w, sf::Vector2f orig, sf::Vector2f dest) {
    simple = true;
    size = w;
    origin = orig;
    destiny = dest;
}

float Hook::getAngle(){
    return getAngle(origin, destiny);
}

float Hook::getWidth() const {
    return size;
}
sf::Vector2f Hook::getDestiny() const{
    return destiny;
}
sf::Vector2f Hook::getOrigin() const{
    return origin;
}


void Hook::setWidth(float value) {
    size = value;
}
void Hook::setDestiny(const sf::Vector2f &value){
    destiny = value;
}
void Hook::setOrigin(const sf::Vector2f &value){
    origin = value;
}


void Hook::setTexture(std::string path) {
    path = path;
    texture = Resources::chain;
    simple = false;
}

bool Hook::makeTextureRepeteable(){
    if(texture.getSize().x <= 0) return false;
    else texture.setRepeated(true);
    return true;
}

void Hook::draw(sf::RenderTarget * window){

    if(simple) {
        sf::Vertex line[] = { origin, destiny };
        window->draw(line, 2, sf::Lines);
    }
    else {
        sprite.setTexture(texture);
        makeTextureRepeteable();
        if(texture.isRepeated()){
            sprite.setTextureRect(sf::IntRect(0,0,getModule(destiny,origin),texture.getSize().y));
        }
        sprite.setScale(getModule(destiny,origin)/sprite.getLocalBounds().width,
                             size/sprite.getLocalBounds().height);

        sprite.setOrigin(0, sprite.getLocalBounds().height/2);
        sprite.setPosition(origin);
        //godoy knows
        sprite.setRotation(getAngle(origin,destiny));
        window->draw(sprite);
    }


}

float Hook::getAngle(sf::Vector2f &orig, sf::Vector2f &des) {
    return std::atan2(des.y - orig.y, des.x - orig.x)*180/(M_PI);
}

float Hook::getModule(sf::Vector2f &orig, sf::Vector2f &des) {
    return std::sqrt(std::pow(std::abs(des.x-orig.x), 2) + std::pow(std::abs(des.y-orig.y), 2));
}
