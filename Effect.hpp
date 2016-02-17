#ifndef EFFECT_H
#define EFFECT_H

#include <string>
#include <sstream>
#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class Effect : public sf::Sprite {

    /* EFFECT IS A SPECIAL SPRITE IN WHICH YOU CAN:

    -LoadAnimation(~~~~); To load the desired animation, in order to do it,
    you can use the following functions:

        Loading individual images
        - bool loadFrame(std::string name);
        - bool loadFrame(std::string name, int position);
        Loading multiple images
        - bool loadAnimation(std::vector<sf::Texture>& vector);
        - int loadAnimation(std::string name, int qtty,std::string ext = "png");
        Loading spritesheets
        - bool loadVerticalSpriteSheet(std::string name, float qtty);
        - bool loadHorizontalSpriteSheet(std::string name, float qtty);
        - bool loadSpriteSheet(std::string name, float rows, float columns, int lastRowQtty =-1);

    -   SET AND GET
        - actualAnimation: set/get the position on the vector that must be used
        to display the animation (i.e. the second image on the loaded vector).
        - timeBetweenAnimations: set/get the time that will pass between each
        element of the animation (i.e time between one image and the next one).
        By default it will be setted at 1 second.

    -   set ACTIVE with the function active(); it will allow the draw method to display images.
    -   set INACTIVE with the function inactive(); it will not allow the draw method to display images.

    -   enable/disable AUTOMATIC ANIMATION.
        - the functions enableAutomaticAnimation() and disableAutomaticAnimation()
        enable/disable the ability of the update to change the actual animation image.

    -   increment / decrement the actual animation
        with inc_actualAnim() and dec_actualAnim();
        we can increment or decrement (go to the next or previous) actual image
        from the animation.

    - UPDATE with updateAnimation(float deltatime);
        if "enabled" and the time passed since last update is bigger than the deffined
        timeBetweenAnimations (as default 1second) will update the image that is displayed
        to the next one (will attach the propper texture to the Effect).

    - DRAW with draw(sf::RenderTarget& window);
        if "active", it will draw on the window passed as parameter the actual image of the animaiton.

     */

private:

    bool activated; //If activated the pictures will be displayed
    bool automatic; //If automatic the update will update to the next image
    float timeCounter; //Auxiliar time variable
    int actualAnimation; //Number of the animation which will be displayed in a draw function
    float timeBetweenAnimations; //Time that will wait to update to the next image
    std::vector<sf::Texture> animation; //Vector which have the textures

public:
//Creadora
    Effect();

//Destructora
    ~Effect();

//ANIMATION LOADERS
    //Caution: name will be the name of the file if it is
    //in the same directory, otherwhise it will have to be
    //the path where it is plus the name.

    //Load the animation using the name and the quantty
        //It will load animations with the names
        // "name0", "name1", ... "name(qtty-1)"
        // it will return the position where it failed if fails
        // it will return -1 otherwhise
    int loadAnimation(std::string name, int qtty,std::string ext = "png");

    //Load the animation using a Texture Vector
        //It set the animation using the textures on the vector
    bool loadAnimation(std::vector<sf::Texture>& vector);

    //Load the frame using name and position
        //It will load the animation frame on the position passed
    bool loadFrame(std::string name, int position);

    //Load the frame using name
        //It will load the animation frame on the animation
        //the new frame will go at the end of the actual animation
    bool loadFrame(std::string name);

    bool loadFrame(sf::Texture & text);
    bool loadFrame(sf::Texture & text, int position);



    //FROM SPRITESHEET LOADERS

    //Load the animation using a spritesheet.
        //You will have to pass the name of the spritesheet,
        //the quantity of rows that it have
        //the quantity of columns that each row have
        //and OPTIONALY how many images are in the last row.
            //with this option, it will be possible to load non
            //perfectly squared spritesheets, if you don't set this
            //parameter it will be lastRowQtty = columns;
        //The order will be from left to right and top to bottom.
    bool loadSpriteSheet(std::string name, float rows, float columns, int lastRowQtty =-1);
    bool loadSpriteSheet(sf::Image image, float rows, float columns, int lastRowQtty =-1);

    //Load the animation using a VerticalSpriteSheet.
        //You will need the name and the quantity of images it will have;
    bool loadVerticalSpriteSheet(std::string name, float qtty);
    bool loadVerticalSpriteSheet(sf::Image image, float qtty);

    //Load the animation using a HoritzontalSpriteSheet.
        //You will need the name and the quantity of images it will have;
    bool loadHorizontalSpriteSheet(std::string name, float qtty);
    bool loadHorizontalSpriteSheet(sf::Image image, float qtty);


//UPDATE
    void updateAnimation(float deltatime);

//DRAW
    void drawEffect(sf::RenderTarget& target);

//OTHER FUNCTIONS

    //Increments the image on the animation
    void inc_actualAnim();
    //Decrements the image on the animation
    void dec_actualAnim();

    //Enable animation
    void active();
    //Desable animation
    void inactive();

    //enable Automatic animation
    void enableAutomaticAnimation();
    //Disable automatic animation
    void disableAutomaticAnimation();

    //Get actualAnimation
    int getActualAnimation();
    //Get timeBetweenAnimations
    float getTimeBetweenAnimations();

    //Set actualAnimation
    void setActualAnimation(int newPosition);
    //Set timeBetweenAnimations
    void setTimeBetweenAnimations(float time);

    //Remember that it have all the functions from a Sprite
};

#endif // EFFECT_H
