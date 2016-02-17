#ifndef TEXTBOX_H
#define TEXTBOX_H
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <string.h>

class TextBox{

public:

    /* Initialize the private variables */
    TextBox();
    TextBox(std::string myText, std::string texturePath, std::string fontPath, float sizeX, float sizeY);
    

    /* Return the size of the TextBox*/
    sf::Vector2f getSize();


    /* The return indicates if the TextBox is
    clicked or not*/
    bool isClicked();

    /* Return true if the TextBox has been clicked */
    bool hasBeenClicked();

    /* Return the time since the last time the TextBox
    has been clicked (returned in a float as seconds)*/
    float timeSinceLastClick();


    /* Return the position of the TextBox*/
    sf::Vector2f getPosition();

    /* Set the position of the TextBox */
    void setPosition(float x, float y);
    void setPosition(sf::Vector2f position);

    /*set the Origin of the TextBox*/
    void setOrigin(sf::Vector2f origin);


    /* Returns the string setted on the text*/
    std::string getText();
    /* Set the text on the TextBox */
    void setTextBestFit(std::string s, float charSize);
    
    
    /* Returns the characterSize*/
    int getCharacterSize();
    /* Set the size of the characters of the TextBox text*/
    void setCharacterSize(int);

    
    /* Returns the color of the TextBox's text*/
    sf::Color getTextColor();
    /* Set the color of the TextBox's text*/
    void setTextColor(sf::Color c);

    
    /*Set the Font passed as a parameter as the one used by the TextBox*/
    void setFont(sf::Font f);

    
    /* Set the Texture that will be used as default TextBox image.
    This function takes as parameter the path of the image*/
    void setTexture(std::string name);
    /*different version taking the reference of texture*/
    void setTexture(sf::Texture tex);

    
    
    /* Draw the TextBox on the window passed as parameter */
    void draw(sf::RenderTarget &w);

    
    /* Update the private variables if needed acordingly to the event*/
    void handleEvent(sf::Event e);
    
    bool getTextFinished();
    
    /* Set the size passed as parameter */
    void setSize(float x, float y);
    void setSize(sf::Vector2f size);

private:

    bool clicked;
    bool is_clicked;
    bool textFinished;
    
    sf::Font font;
    sf::Text text;
    sf::Clock clock;
    sf::Sprite sprite;
    sf::Texture texture;
    float lecturePointer;
    std::string totalText;
    float time_since_last_click;
    std::vector < std::string > boxTexts;
    
    std::string getFractionText(std::string text, int ini, int end);

    void setText(float charSize);
    
    
};

#endif // TEXTBOX_H
