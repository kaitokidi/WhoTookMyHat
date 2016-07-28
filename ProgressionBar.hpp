#ifndef PROGRESSIONBAR_HPP
#define PROGRESSIONBAR_HPP
#include "SFML/Graphics.hpp"
#include "Resources.hpp"
#include "utils.hpp"

class ProgressionBar {

public:

    ProgressionBar(sf::FloatRect rectangle);

    void Update(float dt);
    void SetMaxTime(float time);

    bool finish() const;

    void Draw(sf::RenderTarget *window);
private:

    float _time;
    bool _finish;
    float _maxTime;
    sf::RectangleShape _progress;
    sf::RectangleShape _background;

};

#endif // PROGRESSIONBAR_HPP
