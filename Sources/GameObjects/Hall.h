#pragma once
#include "TileBox.h"
class Hall :public TileBox {
public:
	Hall();
	~Hall();
	void Init();
	void Update(float deltaTime);
	void Render(sf::RenderWindow* window);
	void Create(int tileset, TileBoxType type, sf::Vector2i pos);
	void Reset();
	sf::Vector2i getSize();
	sf::Vector2i getPos();
	bool getActive();
	void setActive(bool active);
	sf::Vector2i getStart();
	sf::Vector2i getEnd();
	TileBoxType getType();
	void setType(TileBoxType type);
	void RoomActive(bool active);
private:
	sf::Vector2f m_Scale;
	int m_Length;
	sf::Vector2i m_Pos;
	sf::Vector2i m_CurrentTiltePos;
	int m_TileSet;
	vector<vector<Tile*>>* m_Tiles;
	TileBoxType m_Type;
	int xstart, xend, ystart, yend;
	sf::IntRect m_preIntRect;
	sf::Texture m_preTexture;
};