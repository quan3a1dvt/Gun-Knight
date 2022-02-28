#pragma once
#include "TileBox.h"
class ShopItem;
class Room: public TileBox {
public:
	Room();
	~Room();
	void Init();
	void Update(float deltaTime);
	void Render(sf::RenderWindow* window);
	void Reset();
	void Create(int tileset, TileBoxType type, sf::Vector2i pos);
	sf::Vector2i getSize();
	sf::Vector2i getPos();
	bool getActive();
	void setActive(bool active);
	void RoomActive(bool active);
	sf::Vector2i getStart();
	sf::Vector2i getEnd();
	TileBoxType getType();
	void setType(TileBoxType type);
protected:
	sf::Vector2f m_Scale;
	sf::Vector2i m_Size;
	sf::Vector2i m_Pos;
	sf::Vector2i m_CurrentTiltePos;
	bool m_Active;
	int m_TileSet;
	TileBoxType m_Type;
	vector<vector<Tile*>>* m_Tiles;
	int xstart, xend, ystart, yend;
	int m_WavesNum;
	int m_WavesData[4][5];

	vector<ShopItem> m_ShopItems;
};