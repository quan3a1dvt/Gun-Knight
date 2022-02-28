#pragma once
#include "IPlayer.h"
#include "Cobra.h"
#include "Bullet.h"
#include "Shoot.h"
#include "MiniMap.h"
#include "Room.h"
#include "Hall.h"
#include "../GameManager/Singleton.h"
#define TM TiledMap::GetInstance()
class TiledMap :public CSingleton <TiledMap> {
public:
	TiledMap();
	~TiledMap();
	void Init();
	void Update(float deltaTime);
	void Render(sf::RenderWindow* window);
	void Reset();
	void ChangeMap();
	void ConnectRooms(TileBox* room1, TileBox* room2);
	void RoomActive(bool active);
	sf::Vector2i m_getRes();
protected:

	int* m_Floor;
	int* m_Level;


	Animation* m_PortalStart;
	string PortalStartState;
	Animation* m_PortalEnd;
	string PortalEndState;

	vector<vector<Tile*>>* m_Tiles;
	vector<vector<TileBox*>>* m_TileBoxes;
	
	int m_TileSet;
	sf::Vector2i* m_RoomPos;
	sf::Vector2i* m_BoundRoomPos;
	sf::Vector2f* m_RoomSize;
	int m_RoomActiving[4][4];
	int m_mobsWavesData[4][4];

	bool* m_RoomActive;


	MiniMap* m_MiniMap;

	Shoot test;

	float m_tempTime;

	sf::Shader* m_Shader;

	sf::RectangleShape* m_Rect;

	float m_currentDeadWait;
	float m_waitDead;
};