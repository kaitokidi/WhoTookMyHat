#ifndef TEXTBOXMANAGER_HPP
#define TEXTBOXMANAGER_HPP

#include <map>
#include <iostream>
#include "TextBox.hpp"
#include "Resources.hpp"
#include <SFML/Graphics.hpp>

class TextBoxManager {

public:
    //TextBoxManager();

    static void load();
    static void loadTexts(std::string fileName);

    static sf::Vector2f getSize();
    static bool getTextFinished();

    static void processEvent(sf::Event event);

    static void setTexture(int value);
    static void setText(std::string name);
    static void setSize(float sizeX, float sizeY);
    static void setText(std::string name, int charSize);

    static void drawText(sf::RenderTarget *window);
    static void drawText(sf::RenderTarget *window, float posX, float posY);

private:

    static TextBox _textBox;
    static std::map<std::string, std::string> texts;

};

#endif // TEXTBOXMANAGER_HPP

