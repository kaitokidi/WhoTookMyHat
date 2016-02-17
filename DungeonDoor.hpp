#ifndef __DUNGEONDOOR_HPP__
#define __DUNGEONDOOR_HPP__

#include "utils.hpp"
#include "Collisionable.hpp"
#include "Resources.hpp"

class DungeonScene;
class DungeonDoor : public Collisionable{
public:
	DungeonDoor(int gid, sf::Vector2f pos, directions orientation);
	~DungeonDoor();
	void setScene(DungeonScene* scene);
	void draw(sf::RenderTarget* window);
	void open();
	void openWithKey();
	void close();
	sf::Vector2f getBotPosition();
	bool isOpened();
	bool needKey();
private:
	DungeonScene* _scene;
    SpriteSheetDescription _description;
    directions _orientation;
	int _gid;
	void updateSprite();
};

#endif