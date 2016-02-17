#ifndef WIDGET_HPP
#define WIDGET_HPP

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class Widget : public sf::Drawable {

    public:

        Widget(Widget* parent= nullptr);
        virtual ~Widget();

        void setPosition(const sf::Vector2f& pos);
        void setPosition(float x ,float y);

        const sf::Vector2f& getPosition()const;
        virtual sf::Vector2f getSize()const = 0;

//  protected:
        Widget* _parent;

        virtual bool processEvent(const sf::Event& event,
                                  const sf::Vector2f& parent_pos,
                                  const sf::RenderTarget& target);
        virtual void processEvents(const sf::Vector2f& parent_pos);
        virtual void updateShape();

        sf::Vector2f _position;
};

#endif // WIDGET_HPP
