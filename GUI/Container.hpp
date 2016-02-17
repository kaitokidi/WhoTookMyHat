#ifndef CONTAINER_HPP
#define CONTAINER_HPP

#ifdef _WIN32
#define NOMINMAX
#define M_PI 3.14159
#define and &&
#define or ||
#define not !
#endif

#include "Widget.hpp"
#include "Layout.hpp"

class Container : public Widget{

public:
    Container(Widget* parent=nullptr);
    virtual ~Container();

    void setLayout(Layout* layout);
    Layout* getLayout() const;

    virtual sf::Vector2f getSize()const override;

protected:
    virtual void draw(sf::RenderTarget& target,
                      sf::RenderStates states) const override;
    virtual bool processEvent(const sf::Event &event,
                              const sf::Vector2f &parent_pos,
                              const sf::RenderTarget& target)override;
    virtual void processEvents(const sf::Vector2f &parent_pos)override;

private:
    Layout* _layout;
};

#endif // CONTAINER_HPP
