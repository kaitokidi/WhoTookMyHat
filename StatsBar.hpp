#ifndef STATSBAR_HPP
#define STATSBAR_HPP
#include "utils.hpp"
#include "GUI/Label.hpp"
#include "GUI/Frame.hpp"
#include "GUI/Layout.hpp"
#include "GUI/Widget.hpp"
#include "GUI/Button.hpp"
#include "GUI/VLayout.hpp"
#include "GUI/HLayout.hpp"
#include "GUI/Container.hpp"
#include "GUI/ImgButton.hpp"
#include "GUI/TextButton.hpp"
#include "GUI/ImgTextButton.hpp"

class StatsBar : public HLayout {

public:
    StatsBar(int maxHP, sf::Texture heart, sf::Texture halfHeart, sf::Texture emptyHeart);
    ~StatsBar();

    void updatePics();
    void updateShape();
    void setMaxHP(int value);
    void setActualHP(float value);

    sf::Vector2f getSize() const;
    void setSize(const sf::Vector2f &value);

private:

    float _maxHP;
    float _actualHP;
    sf::Vector2f size;
    ImgButton* _heart;
    ImgButton* _halfHeart;
    ImgButton* _emptyHeart;

};

#endif // STATSBAR_HPP
