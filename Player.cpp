#include "Player.hpp"
#include <random>
#include <iostream>
#define PLAYERSPEED 50

Player::Player(): body(40,100), guide(10,100){
    angle = 0;
    speed = PLAYERSPEED;
    radius = 35;
    lastUpdate = 0;
    hooking = false;
    hookPos.x = hookPos.y = 1;
    hook.setOrigin(hookPos);
    hook.setDestiny(hookPos);
    vel.x = vel.y = 0.01;
    cameraPos = mousePos = sf::Vector2f(0,0);
    //eyes.setTexture();
    body.setColor(sf::Color(100,100,100));
    guide.setColor(sf::Color(100,100,100));
    hook.setTexture(std::string(TEXTURETPATH)+("hook.png"));
}


sf::Vector2f colisionPoint(sf::Vector2f pos, sf::Vector2f lpos){

}

void Player::setDistantHookPos(sf::Vector2i mousePos, Background* bg){

    sf::Vector2i intersection = bg->getIntersection(sf::Vector2i(getPosition()), mousePos);
    if(intersection.x == intersection.y == 1) {
        intersection.x = getPosition().x;
        intersection.y = getPosition().y;
    }
    setHookPos(sf::Vector2f(intersection.x, intersection.y));

}

float Player::getRadius() const{ return radius; }

void Player::update(float deltaTime, sf::Vector2i auxMousePos, Background* bg) {

    mousePos.x = auxMousePos.x;
    mousePos.y = auxMousePos.y;

    float dX = mousePos.x-getPos().x;
    float dY = mousePos.y-getPos().y;
    angle = std::atan2(dY,dX)*180/M_PI;

    if( InputManager::action(InputAction::up) > 0){
        vel.y = -constant::playerJump*deltaTime;
    }
    if( InputManager::action(InputAction::down) > 0){
        //cry me a river
    }
    if( InputManager::action(InputAction::left) > 0){
        vel.x -= constant::playerSpeed*deltaTime;
    }
    if( InputManager::action(InputAction::right) > 0){
        vel.x += constant::playerSpeed*deltaTime;
    }
    if( InputManager::action(InputAction::hook) > 0){
       hooking = true;
       //std::cout << "auxmousepos " << auxMousePos.x << " , " << auxMousePos.y << std::endl;
       setDistantHookPos(auxMousePos, bg);
    } else {
       hooking = false;
       hookPos = mousePos;
    }
    if( InputManager::action(InputAction::shoot) > 0){

    }

    //Add gravity to the y speed
    vel.y += constant::gravity * deltaTime;
    if(vel.x > 0) vel.x -= constant::friction * deltaTime;
    if(vel.x < 0) vel.x += constant::friction * deltaTime;

    //Add velocity generated by the hook to the player
    if(hooking){
        float deltaX = getHookPos().x-getPos().x;
        float deltaY = getHookPos().y-getPos().y;
        float angle = std::atan(deltaY / deltaX)*180/M_PI;
        float mod = std::sqrt(std::pow(deltaX,2) + std::pow(deltaY,2));
        if(deltaX >= 0) vel.x += std::cos(angle*M_PI/180) * mod * constant::hookForce *deltaTime;
        else vel.x -= std::cos(angle*M_PI/180) * mod * constant::hookForce * deltaTime;
        if(deltaY >= 0) vel.y += std::abs(std::sin(angle*M_PI/180)) * mod * constant::hookForce * deltaTime;
        else vel.y -= std::abs(std::sin(angle*M_PI/180)) * mod * constant::hookForce * deltaTime;
    }


    //Check that the speed on y is not higher than the maximum speed
    if(vel.y > constant::playerMaxSpeed) vel.y = constant::playerMaxSpeed;
    if(vel.y < -1*constant::playerMaxSpeed) vel.y = -1*constant::playerMaxSpeed;


    //Check COLISIONS
    sf::Vector2f orig = pos;
    sf::Vector2f dest = pos + vel;
    float rad = radius; bool stopX = false;


    //CHECK on X
    if(        ! bg->colision(dest.x+rad, orig.y)
            && ! bg->colision(dest.x-rad, orig.y)
            && ! bg->colision(dest.x+rad, orig.y+rad)
            && ! bg->colision(dest.x+rad, orig.y-rad)
            && ! bg->colision(dest.x-rad, orig.y+rad)
            && ! bg->colision(dest.x-rad, orig.y-rad) ){
        pos.x = dest.x;
    }
    else {//THERE IS A COLISION ON X
        stopX = true;
    }
    //CHECK on Y
    if(        ! bg->colision(orig.x, dest.y+rad)
            && ! bg->colision(orig.x, dest.y-rad)
            && ! bg->colision(orig.x+rad, dest.y+rad)
            && ! bg->colision(orig.x+rad, dest.y-rad)
            && ! bg->colision(orig.x-rad, dest.y+rad)
            && ! bg->colision(orig.x-rad, dest.y-rad) ){
        pos.y = dest.y;
    }
    else {//THERE IS A COLISION ON Y
        vel.y = 0;
        vel.x -= vel.x/1.7  * deltaTime;

    }
//    rad = radius;
//    pos.x = dest.x;
  //  pos.y = dest.y;
    //orig.x = orig.x;

    //if(pos.y > 660) pos.y = 660;
    setPosition(pos);
    //If it colisioned on x stop movint on that axe
    //(is done now, not in the oclision because) we need the speed on x to check Y colisions.
    if (stopX) vel.x = 0;
}

float Player::getSpeed() const { return speed; }
void Player::setSpeed(float value) { speed = value; }

sf::Vector2f Player::getHookPos() const { return hookPos; }

sf::Vector2f Player::getMousePos() const { return mousePos; }
void Player::setMousePos(const sf::Vector2f &value) { mousePos = value;}

sf::Vector2f Player::getPos() const { return pos; }

void Player::setPos(const sf::Vector2f &value) { pos = value; log("setPos");}

sf::Vector2f Player::getPosition(){ return body.getPosition(); }

void Player::draw(sf::RenderTarget * w){
    sf::Vector2f guiaPos;
    guiaPos.x = body.getPosition().x + std::cos(angle*M_PI/180) * (body.getRadius() + guide.getRadius() + 10);
    guiaPos.y = body.getPosition().y + std::sin(angle*M_PI/180) * (body.getRadius() + guide.getRadius() + 10);
    guide.setPosition(guiaPos);

    sf::Vector2f hatpos;
    float anglehat = -(90+35);
    hatpos.x = body.getPosition().x + std::cos(anglehat*M_PI/180) * (body.getRadius());
    hatpos.y = body.getPosition().y + std::sin(anglehat*M_PI/180) * (body.getRadius());
    hat.setPosition(hatpos);

    if(hooking) hook.draw(w);
    body.draw(w);
    eyes.draw(w);
    w->draw(hat);
    guide.draw(w);
}


void Player::setPosition(const sf::Vector2f pos){
    hook.setOrigin(pos);
    body.setPosition(pos);

    //EYES
    sf::Vector2f eyesPos;
    eyesPos.x = body.getPosition().x + std::cos(angle*M_PI/180) * (body.getRadius() - eyes.getSize().x/1.5);
    eyesPos.y = body.getPosition().y + std::sin(angle*M_PI/180) * (body.getRadius() - eyes.getSize().y);
    eyes.setSize(body.getRadius()*3/5,body.getRadius()*3/5);
    eyes.setPosition(eyesPos);

    sf::Vector2f guiaPos;
    guiaPos.x = body.getPosition().x + std::cos(angle*M_PI/180) * (body.getRadius() + guide.getRadius()*2);
    guiaPos.y = body.getPosition().y + std::sin(angle*M_PI/180) * (body.getRadius() + guide.getRadius()*2);
    guide.setPosition(guiaPos);
    this->pos = pos;
}

void Player::setAngle(float a){ angle = a; }

void Player::setHookPos(sf::Vector2f pos){
    hookPos = pos;
    hook.setDestiny(pos);
}

void Player::setHat(sf::Sprite& spr) {
    hat.setTexture((*spr.getTexture()));
    hat.setOrigin(hat.getLocalBounds().width/2, hat.getLocalBounds().height/2);
}

void Player::setHookPos(float posX, float posY) { hookPos.x = posX; hookPos.y = posY; hook.setDestiny(sf::Vector2f(posX,posY)); }

void Player::setPosition(float posX, float posY){ setPosition(sf::Vector2f(posX, posY)); }

