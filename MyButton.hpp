#ifndef Button_GUI_H
#define Button_GUI_H
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <string.h>

class Button_GUI{

public:

    /* Initialize the private variables */
    Button_GUI();

    /* Set the size passed as parameter */
    void setSize(float x, float y);
    void setSize(sf::Vector2f size);

    /* Return the size of the Button_GUI*/
    sf::Vector2f getSize();

    /* The return indicates if the Button_GUI is
    clicked or not*/
    bool isClicked();

    /* Set the position of the Button_GUI */
    void setPosition(float x, float y);
    void setPosition(sf::Vector2f position);

    /* Return the position of the Button_GUI*/
    sf::Vector2f getPosition();

    /* Return true if the Button_GUI has been clicked */
    bool hasBeenClicked();

    /* Return the time since the last time the Button_GUI
    has been clicked (returned in a float as seconds)*/
    float timeSinceLastClick();

    /* Set the text on the Button_GUI */
    void setText(std::string s);

    /* Returns the string setted on the text*/
    std::string getText();

    /* Set the text on the Button_GUI and scale the Button_GUI
    so the text fits on it */
    void setTextResize(std::string s);

    /* Enable the change of texture when the Button_GUI is clicked */
    void enableClickEffect();

    /* Disable the change of texture when the Button_GUI is clicked */
    void disableClickEffect();

    /* Returns wether ClickEffect is activated or not */
    bool clickEffectActivated();

    /* Set the size of the characters of the Button_GUI text*/
    void setCharacterSize(uint u);

    /* Returns the characterSize*/
    uint getCharacterSize();

    /* Set the color of the Button_GUI's text*/
    void setTextColor(sf::Color c);

    /* Returns the color of the Button_GUI's text*/
    sf::Color getTextColor();

    /*Set the Font passed as a parameter as the one used by the Button_GUI*/
    void setFont(sf::Font f);

    /* Set the Texture that will be used as default Button_GUI image */
    void setTexture(std::string name);

    /* Set the Texture that will be used as default Button_GUI pressed image */
    void setPressedTexture(std::string name);

    /* Draw the Button_GUI on the window passed as parameter */
    void draw(sf::RenderWindow &w);

    /* Update the private variables if needed acordingly to the event*/
    void handleEvent(sf::Event e);

    void setOrigin(sf::Vector2f origin);

private:

    bool clicked;
    bool is_clicked;
    bool clickEffect;

    sf::Font font;
    sf::Text text;
    sf::Clock clock;
    sf::Sprite sprite;
    sf::Texture texture;
    sf::Texture pressed_texture;
    float time_since_last_click;

};

#endif // Button_GUI_H
