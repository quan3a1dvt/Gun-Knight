#include "GameConnector.h"

GameConnector::GameConnector()
{
	m_Player = nullptr;
	
	m_RoomSize = new sf::Vector2f;

	m_Floor = new int;
	m_Level = new int;

	m_Tiles = new std::vector<std::vector<Tile*>>(RoomMaxSize * 9, std::vector<Tile*>(RoomMaxSize * 9));
	m_TileBoxes = new std::vector<std::vector<TileBox*> >(9, std::vector<TileBox*>(9));
	

	m_RoomPos = new sf::Vector2i(-1,-1);

	m_RoomActive = new bool;
	*m_RoomActive = false;

	m_Wave = new int(0);
	m_WavesNum = new int(0);
	m_WavesData = new std::vector<std::vector<int> >(4, std::vector<int>(4));
	PEXP = sf::Vector2i(95, 100);
	
}

void GameConnector::setPlayer(IPlayer* Player)
{
	m_Player = Player;
}

IPlayer* GameConnector::getPlayer()
{
	return m_Player;
}

void GameConnector::setView(sf::View* view)
{
	m_View = view;
}

sf::View* GameConnector::getView()
{
	return m_View;
}

void GameConnector::setFloor(int* Floor)
{
	m_Floor = Floor;
}

int* GameConnector::getFloor()
{
	return m_Floor;
}

void GameConnector::setLevel(int* Level)
{
	m_Level = Level;
}

int* GameConnector::getLevel()
{
	return m_Level;
}

std::vector<std::vector<TileBox*>>* GameConnector::getTileBoxes()
{
	return m_TileBoxes;
}


std::vector<std::vector<Tile*>>* GameConnector::getTiles()
{
	return m_Tiles;
}

void GameConnector::setRoomPos(sf::Vector2i* RoomPos)
{
	m_RoomPos = RoomPos;
}

sf::Vector2i* GameConnector::getRoomPos()
{
	return m_RoomPos;
}


sf::Vector2f* GameConnector::getRoomSize()
{
	return m_RoomSize;
}


bool* GameConnector::getRoomActive()
{
	return m_RoomActive;
}

int* GameConnector::getWave()
{
	return m_Wave;
}

int* GameConnector::getWavesNum()
{
	return m_WavesNum;
}

std::vector<std::vector<int>>* GameConnector::getWavesData()
{
	return m_WavesData;
}

void GameConnector::MobDeath(int mobid)
{
	(*m_WavesData)[*m_Wave][mobid -1] -= 1;
}

void GameConnector::setMobs(std::vector<IMob*>* mobs)
{
	m_Mobs = mobs;
}

std::vector<IMob*>* GameConnector::getMobs()
{
	return m_Mobs;
}

void GameConnector::setBullets(std::vector<Bullet*>* bullets)
{
	m_Bullets = bullets;
}

std::vector<Bullet*>* GameConnector::getBullets()
{
	return m_Bullets;
}

void GameConnector::setCoins(std::vector<Coin*>* coins)
{
	m_Coins = coins;
}

std::vector<Coin*>* GameConnector::getCoins()
{
	return m_Coins;
}

void GameConnector::setExps(std::vector<Exp*>* exps)
{
	m_Exps = exps;
}

std::vector<Exp*>* GameConnector::getExps()
{
	return m_Exps;
}

sf::Vector2i GameConnector::getPExp()
{
	return PEXP;
}

void GameConnector::setPExp(sf::Vector2i exp)
{
	PEXP = exp;
}

