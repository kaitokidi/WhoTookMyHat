#ifndef IMGTEXTBUTTON_HPP
#define IMGTEXTBUTTON_HPP

#include "Label.hpp"
#include "Button.hpp"

class ImgTextButton : public Button {

public:
    ImgTextButton(const sf::Texture& pressedTexture, sf::Texture& releasedTexture,
                  std::string& text, sf::Font& font, Widget* parent=nullptr);
    virtual ~ImgTextButton();

    void setSize(sf::Vector2f size);
    void setSize(float width, float height);
    void setPressedTexture(sf::Texture& pressedTexture);
    void setReleassedTexture(sf::Texture& releassedTexture);

    virtual sf::Vector2f getSize()const override;
    virtual void onMouseLeft() override;
    virtual void onMouseEntered() override;

    void setText(const std::string &text);

    void setCharacterSize(unsigned int size);

    void setTextColor(const sf::Color &color);


private:

    Label _label;
    sf::Sprite _sprite;
    sf::RectangleShape _shape;
    sf::Texture _pressedTexture;
    sf::Texture _releassedTexture;

    void updateShape()override;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

};

#endif // IMGTEXTBUTTON_HPP
