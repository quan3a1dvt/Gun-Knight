#include "Cobra_SIdle.h"

Cobra_SIdle::Cobra_SIdle(IMob* mob)
{
	m_mob = mob;
}

void Cobra_SIdle::Init()
{
	m_animation = new Animation(*ASSET->getTexture("Mob/Cobra/Cobra_Idle_Sprite_Sheet"), sf::Vector2i(8, 1), 0.1f);
	//printf("%f %f\n", m_animation->getTexture()->getSize().x * 3.f / 8, m_animation->getTexture()->getSize().y * 3.f / 4);
	
	m_animation->setScale(m_mob->getScale());
	m_animation->setOrigin(m_animation->GetRectSize().x * 3.f / 8, m_animation->GetRectSize().y * 4.f / 5);
}

void Cobra_SIdle::Update(float deltaTime)
{
	m_animation->Update(deltaTime);

	m_animation->setPosition(m_mob->getHitBox()->getPosition());
	if (m_mob->getCW()) {
		m_animation->setScale(fabs(m_animation->getScale().x), fabs(m_animation->getScale().y));
	}
	else {
		m_animation->setScale(-fabs(m_animation->getScale().x), fabs(m_animation->getScale().y));
	}
}

void Cobra_SIdle::Render(sf::RenderWindow* window)
{
	window->draw(*m_animation);
}

Animation* Cobra_SIdle::getSprite()
{
	return m_animation;
}
