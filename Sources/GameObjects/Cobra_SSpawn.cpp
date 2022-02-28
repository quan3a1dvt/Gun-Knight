#include "Cobra_SSpawn.h"

Cobra_SSpawn::Cobra_SSpawn(IMob* mob)
{
	m_mob = mob;
}

void Cobra_SSpawn::Init()
{
	m_animation = new Animation(*ASSET->getTexture("Spawn"), sf::Vector2i(16, 1), 0.1f);
	m_animation->setScale(m_mob->getScale());
}

void Cobra_SSpawn::Update(float deltaTime)
{
	if (m_animation->Play(deltaTime)) {
		m_mob->ChangeNextState(IMState::STATE_IDLE);
	}
	m_animation->setPosition(m_mob->getHitBox()->getPosition());
}

void Cobra_SSpawn::Render(sf::RenderWindow* window)
{
	window->draw(*m_animation);
}

Animation* Cobra_SSpawn::getSprite()
{
	return m_animation;
}
