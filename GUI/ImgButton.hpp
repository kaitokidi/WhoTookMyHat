#ifndef IMGBUTTON_HPP
#define IMGBUTTON_HPP

#include "Label.hpp"
#include "Button.hpp"

class ImgButton : public Button {

public:
    ImgButton(const sf::Texture& pressedTexture, sf::Texture& releasedTexture, Widget* parent=nullptr);
    virtual ~ImgButton();

    void setSize(sf::Vector2f size);
    void setSize(float width, float height);
    void setPressedTexture(sf::Texture& pressedTexture);
    void setReleassedTexture(sf::Texture& releassedTexture);

    virtual sf::Vector2f getSize()const override;

    virtual void onMouseLeft() override;
    virtual void onMouseEntered() override;

private:
    //old
//    Label _label;
  //  sf::Color _fillColor;
    //sf::Color _outlineColor;
    sf::RectangleShape _shape;
    //new
    sf::Sprite _sprite;
    sf::Texture _pressedTexture;
    sf::Texture _releassedTexture;

    void updateShape()override;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

};

#endif // IMGBUTTON_HPP
