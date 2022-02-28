#include "Mage_SSpawn.h"

Mage_SSpawn::Mage_SSpawn(IMob* mob)
{
	m_mob = mob;
}

void Mage_SSpawn::Init()
{
	m_animation = new Animation(*ASSET->getTexture("Spawn"), sf::Vector2i(16, 1), 0.05f);
	m_animation->setScale(m_mob->getScale());
}

void Mage_SSpawn::Update(float deltaTime)
{
	if (m_animation->Play(deltaTime)) {
		m_mob->ChangeNextState(IMState::STATE_IDLE);
	}
	m_animation->setPosition(m_mob->getHitBox()->getPosition());
}

void Mage_SSpawn::Render(sf::RenderWindow* window)
{
	window->draw(*m_animation);
}

Animation* Mage_SSpawn::getSprite()
{
	return m_animation;
}
