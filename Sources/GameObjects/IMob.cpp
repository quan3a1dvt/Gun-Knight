#include "IMob.h"
#include "Room.h"
#include "IPlayer.h"

HitBox* IMob::getHitBox()
{
	return m_HitBox;
}

sf::Vector2f IMob::getScale()
{
	return m_scale;
}

bool IMob::getCW()
{
	return m_cw;
}

void IMob::setCW(bool cw)
{
	m_cw = cw;
}


void IMob::SetCanMove(bool canmove)
{
	m_canMove = canmove;
}

void IMob::setActive(bool active)
{
	m_Active = active;
}

bool IMob::getActive()
{
	return m_Active;
}

int IMob::getDamage()
{
	return m_damage;
}
