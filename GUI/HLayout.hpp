#ifndef HLAYOUT_HPP
#define HLAYOUT_HPP


#include "Layout.hpp"

class HLayout : public Layout {

public:

    HLayout(const HLayout&) = delete;
    HLayout(Widget* parent = nullptr);
    HLayout& operator=(const HLayout&) = delete;

    ~HLayout();

    void add(Widget* widget);

    Widget* at(unsigned int index)const;

    virtual sf::Vector2f getSize()const override;


protected:

    virtual bool processEvent(const sf::Event& event,
                              const sf::Vector2f& parent_pos,
                              const sf::RenderTarget& target) override;

    virtual void processEvents(const sf::Vector2f& parent_pos) override;

    std::vector<Widget*> _widgets;

private:

    virtual void updateShape() override;
    virtual void draw(sf::RenderTarget& target,
                      sf::RenderStates states) const override;
};


#endif // HLAYOUT_HPP
