#ifndef FRAME_HPP
#define FRAME_HPP

#ifdef _WIN32
#define NOMINMAX
#define M_PI 3.14159
#define and &&
#define or ||
#define not !
#endif

#include "Widget.hpp"
#include "Button.hpp"
#include "Container.hpp"

class Frame : public Container {

public:

    using FuncType = std::function<void(const sf::Event& event,Button& self)>;

    Frame(sf::RenderWindow& window, const sf::View& view);
    virtual ~Frame();
	Frame& operator= (Frame&& original);
    void processEvents();

    bool processEvent(const sf::Event& event);
    void draw();
    virtual sf::Vector2f getSize()const override;

private:

    sf::RenderWindow& _window;
    const sf::View& _view;

    virtual bool processEvent(const sf::Event& event,
                              const sf::Vector2f& parent_pos,
                              const sf::RenderTarget& target)override;

    virtual void processEvents(const sf::Vector2f& parent_pos)override;

};

#endif // FRAME_HPP
