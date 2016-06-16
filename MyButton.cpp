#include "MyButton.hpp"

Button::Button(){
    text.setString("");
    clicked = false;
    is_clicked = false;
    clickEffect = true;

   /* if(!font.loadFromFile("defaultFont.otf")){ std::cerr << "Can't find the font file" << std::endl; }
    else setFont(font); setCharacterSize(30); setTextColor(sf::Color::White);

    if(!texture.loadFromFile("defaultButton.png")) std::cerr << "Default texture not loaded" << std::endl;
    else sprite.setTexture(texture);

    if(!pressed_texture.loadFromFile("defaultPressedButton.png")) std::cerr << "presedButton text. not loaded" << std::endl;
*/
    setPosition(0,0);
}

void Button::setTextColor(sf::Color c){text.setColor(c); }
sf::Color Button::getTextColor(){ return text.getColor(); }

void Button::setCharacterSize(uint u){ text.setCharacterSize(u); }
uint Button::getCharacterSize(){ return text.getCharacterSize(); }

void Button::setFont(sf::Font f){ font = f; text.setFont(font); }


void Button::setPosition(sf::Vector2f position){
    sprite.setPosition(position);
    text.setPosition(position.x +
                     sprite.getGlobalBounds().width/2 -
                     text.getGlobalBounds().width/2,
        position.y + sprite.getGlobalBounds().height/2 - (text.getGlobalBounds().height/2));
}

void Button::setPosition(float x, float y){
    setPosition(sf::Vector2f(x, y));
}

sf::Vector2f Button::getPosition(){
    return sprite.getPosition();
}

sf::Vector2f Button::getSize(){
    return sf::Vector2f(sprite.getGlobalBounds().width,sprite.getGlobalBounds().height);
}


void Button::setSize(sf::Vector2f size){
    sprite.setScale(size.x/sprite.getGlobalBounds().width, size.y/sprite.getGlobalBounds().height);
    this->setText(text.getString());
}

void Button::setSize(float x, float y){ setSize(sf::Vector2f(x,y)); }

bool Button::isClicked(){ return is_clicked; }

bool Button::hasBeenClicked(){
    bool r = clicked;
    if(clicked) clicked = false;
    return r;
}

float Button::timeSinceLastClick(){ return clock.getElapsedTime().asSeconds(); }

void Button::setText(std::string s = "Click"){
    text.setString(s);
    if(s.size() != 0){
        float actualCharSize, desiredCharSize;
        float actualTextSize, desiredTextSize;
        actualCharSize = text.getCharacterSize();
        actualTextSize = text.getGlobalBounds().width+2;
        desiredTextSize = sprite.getGlobalBounds().width;
        desiredCharSize = actualCharSize*desiredTextSize/actualTextSize;
        text.setCharacterSize(desiredCharSize);
    }
}

std::string Button::getText(){ return text.getString();}

//TODO should be a resize for text and a resize for button
void Button::setTextResize(std::string s = "Click"){
    text.setString(s);
    if(s.size() != 0){
        float actualTextSize, factor;
        actualTextSize = text.getGlobalBounds().width;
        //WTF THIS 10?¿?¿?¿? well... it works :$
        factor = (actualTextSize)/10/sprite.getGlobalBounds().width;
        sprite.setScale(factor, factor);
    }
}

void Button::draw(sf::RenderWindow& w){
    sf::Vector2f position = getPosition();
    text.setPosition(position.x + sprite.getGlobalBounds().width/2 - text.getGlobalBounds().width/2, position.y + sprite.getGlobalBounds().height/2 - text.getGlobalBounds().height);
    w.draw(sprite);
    w.draw(text);
}

void Button::setOrigin(sf::Vector2f origin){
    sprite.setOrigin(origin);
}

void Button::setTexture(std::string name){
    if(!texture.loadFromFile(name)) std::cerr << "Default texture not loaded on setTexture" << std::endl;
    else sprite.setTexture(texture); }

void Button::setPressedTexture(std::string name){
    if(!pressed_texture.loadFromFile(name)) std::cerr << "presedButton text. not loaded on Setter" << std::endl; }

void Button::enableClickEffect(){ clickEffect = true; }
void Button::disableClickEffect(){ clickEffect = false; }
bool Button::clickEffectActivated(){ return clickEffect; }

void Button::handleEvent(sf::Event e){

    float delayx, delayy;
    delayx = sprite.getOrigin().x*sprite.getScale().x;
    delayy = sprite.getOrigin().y*sprite.getScale().y;
    sprite.move(-delayx, -delayy);
    if(e.type == sf::Event::MouseButtonPressed){
        if (e.mouseButton.button == sf::Mouse::Left) {
            sf::Vector2f click(e.mouseButton.x, e.mouseButton.y);
            if(click.x > sprite.getPosition().x && click.x < sprite.getPosition().x+sprite.getGlobalBounds().width){
                if(click.y > sprite.getPosition().y && click.y < sprite.getPosition().y+sprite.getGlobalBounds().height){
                    clicked = true;
                    is_clicked = true;
                    clock.restart();
                    if(clickEffect && sprite.getTexture() == &texture) sprite.setTexture(pressed_texture);
                }
            }
        }

    }
    if(e.type == sf::Event::MouseButtonReleased){
        if (e.mouseButton.button == sf::Mouse::Left) {
            is_clicked = false;
            if(clickEffect && sprite.getTexture() != &texture) sprite.setTexture(texture);
        }
    }
    sprite.move(delayx, delayy);
}
