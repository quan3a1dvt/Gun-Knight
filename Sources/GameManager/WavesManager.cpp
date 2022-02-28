#include "WavesManager.h"
#include "../GameObjects/Room.h"
WavesManager::WavesManager()
{
	m_Map = GConnect->getFloor();
	m_Round = GConnect->getLevel();
	m_RoomPos = GConnect->getRoomPos();
	m_Wave = GConnect->getWave();
	m_WavesNum = GConnect->getWavesNum();
	m_WavesData = GConnect->getWavesData();
}

WavesManager::~WavesManager()
{
}

void WavesManager::Init()
{

}

void WavesManager::Update(float deltaTime)
{
	if (*GConnect->getRoomActive()) {
		if (DoChangeWave()) {
			ChangeWave();
		}
	}
	
}

void WavesManager::Render(sf::RenderWindow* window)
{
}

void WavesManager::Reset()
{
	
}

void WavesManager::RoomActive(bool active)
{
	if (active) {
		*m_Wave = 0;
		(*GConnect->getTileBoxes())[m_RoomPos->y][m_RoomPos->x]->RoomActive(true);
	}
	else {

	}
}

bool WavesManager::DoChangeWave()
{
	FOR(i, 0, 3) {
		if ((*m_WavesData)[*m_Wave][i] != 0) {
			return false;
		}
	}
	return true;
}

void WavesManager::ChangeWave()
{
	if ((*m_Wave) < (*m_WavesNum)) {
		(*m_Wave) += 1;
		FOR(mobid, 1, 3) {
			MManager->Spawn(mobid, (*m_WavesData)[*m_Wave][mobid - 1]);
		}
	}
	else {
		(*GConnect->getTileBoxes())[m_RoomPos->y][m_RoomPos->x]->RoomActive(false);
	}
}

void WavesManager::MobDeath(int mobid)
{
	(*m_WavesData)[*m_Wave][mobid - 1] -= 1;
}
