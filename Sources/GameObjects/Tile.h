#pragma once
#include "../GameManager/ResourceManager.h"
enum TileType {
	TILE_WALL = 0,
	TILE_DOOR,
	TILE_FLOOR,
	TILE_DEFAULT,
};
class Tile :public sf::Sprite {
public:
	Tile();
	~Tile();
	void Init();
	void Update(float deltaTime);
	void Render(sf::RenderWindow* window);
	TileType getType();
	void setType(TileType type);
protected:
	TileType m_Type;
	sf::Shader m_Shader;
};