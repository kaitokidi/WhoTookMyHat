#ifndef TEXTBUTTON_HPP
#define TEXTBUTTON_HPP

#include "Label.hpp"
#include "Button.hpp"

class TextButton : public Button {

public:
    TextButton(const std::string&text, sf::Font &font, Widget* parent=nullptr);
    virtual ~TextButton();

    void setText(const std::string& text);
    void setCharacterSize(unsigned int size);

    void setTextColor(const sf::Color& color);
    void setFillColor(const sf::Color& color);

    void setOutlineThickness(float thickness);
    void setOutlineColor(const sf::Color& color);

    virtual sf::Vector2f getSize()const override;

    virtual void onMouseLeft() override;
    virtual void onMouseEntered() override;
private:

    Label _label;
    sf::Color _fillColor;
    sf::Color _outlineColor;
    sf::RectangleShape _shape;

    void updateShape()override;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

};

#endif // TEXTBUTTON_HPP
