#pragma once
#include "../GameObjects/IMob.h"
#include "../GameManager/Singleton.h"
#include "ResourceManager.h"
#include "MobsManager.h"
#define WManager WavesManager::GetInstance()

class WavesManager:public CSingleton <WavesManager> {
public:
	WavesManager();
	~WavesManager();
	void Init();
	void Update(float deltaTime);
	void Render(sf::RenderWindow* window);
	void Reset();
	void RoomActive(bool active);
	bool DoChangeWave();
	void ChangeWave();
	void MobDeath(int mobid);
protected:

	int* m_Map;
	int* m_Round;
	sf::Vector2i* m_RoomPos;

	int* m_Wave;
	int* m_WavesNum;
	std::vector<vector<int>>* m_WavesData;

	int m_RoomMobsTypeNumber;
	int m_RoomWavesNumber;
	int m_WavesNumber;

};