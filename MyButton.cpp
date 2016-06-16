#include "Button.hpp"

Button_GUI::Button_GUI(){
    text.setString("");
    clicked = false;
    is_clicked = false;
    clickEffect = true;

   /* if(!font.loadFromFile("defaultFont.otf")){ std::cerr << "Can't find the font file" << std::endl; }
    else setFont(font); setCharacterSize(30); setTextColor(sf::Color::White);

    if(!texture.loadFromFile("defaultButton_GUI.png")) std::cerr << "Default texture not loaded" << std::endl;
    else sprite.setTexture(texture);

    if(!pressed_texture.loadFromFile("defaultPressedButton_GUI.png")) std::cerr << "presedButton_GUI text. not loaded" << std::endl;
*/
    setPosition(0,0);
}

void Button_GUI::setTextColor(sf::Color c){text.setColor(c); }
sf::Color Button_GUI::getTextColor(){ return text.getColor(); }

void Button_GUI::setCharacterSize(uint u){ text.setCharacterSize(u); }
uint Button_GUI::getCharacterSize(){ return text.getCharacterSize(); }

void Button_GUI::setFont(sf::Font f){ font = f; text.setFont(font); }


void Button_GUI::setPosition(sf::Vector2f position){
    sprite.setPosition(position);
    text.setPosition(position.x +
                     sprite.getGlobalBounds().width/2 -
                     text.getGlobalBounds().width/2,
        position.y + sprite.getGlobalBounds().height/2 - (text.getGlobalBounds().height/2));
}

void Button_GUI::setPosition(float x, float y){
    setPosition(sf::Vector2f(x, y));
}

sf::Vector2f Button_GUI::getPosition(){
    return sprite.getPosition();
}

sf::Vector2f Button_GUI::getSize(){
    return sf::Vector2f(sprite.getGlobalBounds().width,sprite.getGlobalBounds().height);
}


void Button_GUI::setSize(sf::Vector2f size){
    sprite.setScale(size.x/sprite.getGlobalBounds().width, size.y/sprite.getGlobalBounds().height);
    this->setText(text.getString());
}

void Button_GUI::setSize(float x, float y){ setSize(sf::Vector2f(x,y)); }

bool Button_GUI::isClicked(){ return is_clicked; }

bool Button_GUI::hasBeenClicked(){
    bool r = clicked;
    if(clicked) clicked = false;
    return r;
}

float Button_GUI::timeSinceLastClick(){ return clock.getElapsedTime().asSeconds(); }

void Button_GUI::setText(std::string s = "Click"){
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

std::string Button_GUI::getText(){ return text.getString();}

//TODO should be a resize for text and a resize for Button_GUI
void Button_GUI::setTextResize(std::string s = "Click"){
    text.setString(s);
    if(s.size() != 0){
        float actualTextSize, factor;
        actualTextSize = text.getGlobalBounds().width;
        //WTF THIS 10?¿?¿?¿? well... it works :$
        factor = (actualTextSize)/10/sprite.getGlobalBounds().width;
        sprite.setScale(factor, factor);
    }
}

void Button_GUI::draw(sf::RenderWindow& w){
    sf::Vector2f position = getPosition();
    text.setPosition(position.x + sprite.getGlobalBounds().width/2 - text.getGlobalBounds().width/2, position.y + sprite.getGlobalBounds().height/2 - text.getGlobalBounds().height);
    w.draw(sprite);
    w.draw(text);
}

void Button_GUI::setOrigin(sf::Vector2f origin){
    sprite.setOrigin(origin);
}

void Button_GUI::setTexture(std::string name){
    if(!texture.loadFromFile(name)) std::cerr << "Default texture not loaded on setTexture" << std::endl;
    else sprite.setTexture(texture); }

void Button_GUI::setPressedTexture(std::string name){
    if(!pressed_texture.loadFromFile(name)) std::cerr << "presedButton_GUI text. not loaded on Setter" << std::endl; }

void Button_GUI::enableClickEffect(){ clickEffect = true; }
void Button_GUI::disableClickEffect(){ clickEffect = false; }
bool Button_GUI::clickEffectActivated(){ return clickEffect; }

void Button_GUI::handleEvent(sf::Event e){

    float delayx, delayy;
    delayx = sprite.getOrigin().x*sprite.getScale().x;
    delayy = sprite.getOrigin().y*sprite.getScale().y;
    sprite.move(-delayx, -delayy);
    if(e.type == sf::Event::MouseButton_GUIPressed){
        if (e.mouseButton_GUI.Button_GUI == sf::Mouse::Left) {
            sf::Vector2f click(e.mouseButton_GUI.x, e.mouseButton_GUI.y);
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
    if(e.type == sf::Event::MouseButton_GUIReleased){
        if (e.mouseButton_GUI.Button_GUI == sf::Mouse::Left) {
            is_clicked = false;
            if(clickEffect && sprite.getTexture() != &texture) sprite.setTexture(texture);
        }
    }
    sprite.move(delayx, delayy);
}
