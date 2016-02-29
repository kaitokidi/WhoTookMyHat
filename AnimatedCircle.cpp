#include "AnimatedCircle.hpp"

AnimatedCircle::AnimatedCircle(){

}

AnimatedCircle::AnimatedCircle(float radius=0, unsigned int pointCount=30){
    circle.setOutlineThickness(4);
    circle.setOutlineColor(sf::Color::Black);
    circle.setRadius(radius);
    circle.setPointCount(pointCount);
    circle.setOrigin(circle.getRadius(), circle.getRadius());
}

AnimatedCircle::AnimatedCircle(float radius, unsigned int pointCount, sf::Texture* tex){
    texture = tex;
    circle.setRadius(radius);
    circle.setTexture(texture);
    circle.setPointCount(pointCount);
    circle.setOrigin(circle.getRadius(), circle.getRadius());
}

AnimatedCircle::AnimatedCircle(float radius, unsigned int pointCount, sf::Texture* tex, float posX, float posY){
    texture = tex;
    circle.setRadius(radius);
    circle.setTexture(texture);
    circle.setPosition(posX, posY);
    circle.setPointCount(pointCount);
    circle.setOrigin(circle.getRadius(), circle.getRadius());
}


void AnimatedCircle::draw(sf::RenderTarget* window) {
    window->draw(circle);
    if(animation.size() > 0){
        circle.setTexture(animation[animationPointer]);
        window->draw(circle);
    }
    if(effect.size() > 0){
        circle.setTexture(effect[effectPointer]);
        window->draw(circle);
    }
}

void AnimatedCircle::setEffect(VpT& newEffect)      { effect = newEffect;         }

void AnimatedCircle::setPosition(sf::Vector2f pos)  { circle.setPosition(pos);    }

void AnimatedCircle::setColor(sf::Color c)          { circle.setFillColor(c);     }

void AnimatedCircle::setAnimation(VpT& newAnimaiton){ animation = newAnimaiton;   }

void AnimatedCircle::setPosition(float pX, float pY){ circle.setPosition(pX, pY); }

sf::Vector2f AnimatedCircle::getPosition()          { return circle.getPosition();}

float AnimatedCircle::getRadius()                   { return circle.getRadius();  }

void AnimatedCircle::nextEffectFrame()   {effectPointer = (effectPointer+1)%animation.size();}

void AnimatedCircle::nextAnimationFrame(){animationPointer = (animationPointer+1)%animation.size();}
