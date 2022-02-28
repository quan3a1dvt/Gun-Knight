#include "Imp_SSpawn.h"

Imp_SSpawn::Imp_SSpawn(IMob* mob)
{
	m_mob = mob;
}

void Imp_SSpawn::Init()
{
	m_animation = new Animation(*ASSET->getTexture("Spawn"), sf::Vector2i(16, 1), 0.05f);
	m_animation->setScale(m_mob->getScale());
}

void Imp_SSpawn::Update(float deltaTime)
{
	if (m_animation->Play(deltaTime)) {
		m_mob->ChangeNextState(IMState::STATE_IDLE);
	}
	m_animation->setPosition(m_mob->getHitBox()->getPosition());
}

void Imp_SSpawn::Render(sf::RenderWindow* window)
{
	window->draw(*m_animation);
}

Animation* Imp_SSpawn::getSprite()
{
	return m_animation;
}
