#ifndef LIFECOUNTER_HPP
#define LIFECOUNTER_HPP
#include <SFML/Graphics.hpp>
#include "Resources.hpp"
#include "utils.hpp"

class LifeCounter
{
public:
    LifeCounter();
    LifeCounter(sf::Vector2f pos);

    void Update(float dt);
    void Draw(sf::RenderTarget *window);

    void hit();

    int lifes() const;
    void setLifes(int lifes, bool nohit=true);

    sf::Vector2f position() const;
    void setPosition(const sf::Vector2f &position);

    float scale() const;
    void setScale(float scale);

private:

    void init();

    int _lifes;
    bool _hitted;
    float _scale;
    float _dtime;
    sf::Sprite _sprite;
    sf::Vector2f _position;




};

#endif // LIFECOUNTER_HPP
