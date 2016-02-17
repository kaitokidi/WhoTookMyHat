#ifndef __COLLISIONABLE_HPP__
#define __COLLISIONABLE_HPP__

#include "utils.hpp"

class Collisionable {
 public:
     Collisionable(sf::Vector2f position = sf::Vector2f(0,0));
     virtual ~Collisionable();
     virtual void update(float deltaTime);
     virtual void draw(sf::RenderTarget* window);

     static bool collisioning(Collisionable* c1, Collisionable* c2);

     sf::Vector2f getPosition();
     virtual sf::Vector2f getBotPosition();
     sf::IntRect getGlobalBound();
     sf::IntRect getBounds();

     virtual void setPosition(sf::Vector2f pos);

     virtual void cmove(sf::Vector2f movement);
     virtual void resetMove();
     bool hasMoved();

     virtual void intersectsWith(Collisionable* c);

     void setIniCoord(sf::Vector2f coord);

 protected:
     sf::Sprite _sprite;
     sf::Vector2f _pastPosition;
     sf::Vector2f _speed;
     sf::IntRect _bounds; // IntRect(offset.x, offset.y, width, height)
     int8_t _collisionMask;
     sf::Vector2f _posOriginal;
 }; 


#endif