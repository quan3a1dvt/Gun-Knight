#pragma once
#include "Tile.h"
enum TileBoxType {
	BOX_DEFAULT = 0,
	ROOM_START,
	ROOM_CHEST,
	ROOM_BOSS,
	ROOM_END,
	ROOM_NORMAL,
	HALL_VERTICAL,
	HALL_HORIZONTAL,
};
class TileBox {
public:
	virtual void Init() = 0;
	virtual void Update(float deltaTime) = 0;
	virtual void Render(sf::RenderWindow* window) = 0;
	virtual void Reset() = 0;
	virtual void Create(int tileset, TileBoxType type, sf::Vector2i pos) = 0;
	virtual sf::Vector2i getSize() = 0;
	virtual sf::Vector2i getPos() = 0;
	virtual bool getActive() = 0;
	virtual void setActive(bool active) = 0;
	virtual void RoomActive(bool active) = 0;
	virtual sf::Vector2i getStart() = 0;
	virtual sf::Vector2i getEnd() = 0;
	virtual TileBoxType getType() = 0;
	virtual void setType(TileBoxType type) = 0;
};