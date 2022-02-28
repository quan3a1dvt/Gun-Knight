#pragma once
#include "SFML/Graphics.hpp"
#include "../GameManager/Singleton.h"
#include "../GameConfig.h"

#define GConnect GameConnector::GetInstance()

class IPlayer;
class IMob;
class Bullet;
class Tile;
class TileBox;
class Coin;
class Exp;

class GameConnector :public CSingleton<GameConnector> {
public:
	GameConnector();
	
	void setPlayer(IPlayer* Player);
	IPlayer* getPlayer();

	void setView(sf::View* view);
	sf::View* getView();

	void setFloor(int* Floor);
	int* getFloor();

	void setLevel(int* Level);
	int* getLevel();

	std::vector<std::vector<Tile*>>* getTiles();
	std::vector<std::vector<TileBox*>>* getTileBoxes();

	void setRoomPos(sf::Vector2i* RoomPos);
	sf::Vector2i* getRoomPos();


	sf::Vector2f* getRoomSize();

	bool* getRoomActive();

	int* getWave();
	int* getWavesNum();
	std::vector<std::vector<int>>* getWavesData();

	void MobDeath(int mobid);

	void setMobs(std::vector<IMob*>* mobs);
	std::vector<IMob*>* getMobs();
	
	void setBullets(std::vector<Bullet*>* bullets);
	std::vector<Bullet*>* getBullets();

	void setCoins(std::vector<Coin*>* coins);
	std::vector<Coin*>* getCoins();

	void setExps(std::vector<Exp*>* exps);
	std::vector<Exp*>* getExps();
	
	sf::Vector2i getPExp();
	void setPExp(sf::Vector2i exp);

private:
	IPlayer* m_Player;

	sf::View* m_View;

	int* m_Floor;
	int* m_Level;

	std::vector<std::vector<Tile*>>* m_Tiles;
	std::vector<std::vector<TileBox*>>* m_TileBoxes;
	

	sf::Vector2i* m_RoomPos;
	sf::Vector2f* m_RoomSize;
	
	bool* m_RoomActive;

	int* m_Wave;
	int* m_WavesNum;
	std::vector<std::vector<int>>* m_WavesData;


	std::vector<IMob*>* m_Mobs;
	std::vector<Bullet*>* m_Bullets;
	
	std::vector<Coin*>* m_Coins;
	std::vector<Exp*>* m_Exps;

	sf::Vector2i PEXP;
};