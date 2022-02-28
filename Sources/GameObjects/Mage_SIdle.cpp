#include "Mage_SIdle.h"

Mage_SIdle::Mage_SIdle(IMob* mob)
{
	m_mob = mob;
}

void Mage_SIdle::Init()
{
	m_animation = new Animation(*ASSET->getTexture("Mob/Mage/Mage_Idle_Sprite_Sheet"), sf::Vector2i(12, 1), 0.1f);
	//printf("%f %f\n", m_animation->getTexture()->getSize().x * 3.f / 8, m_animation->getTexture()->getSize().y * 3.f / 4);
	
	m_animation->setScale(m_mob->getScale());
	m_animation->setOrigin(m_animation->getOrigin().x - m_animation->GetRectSize().x * m_mob->getScale().x / 14, m_animation->getOrigin().y);
}

void Mage_SIdle::Update(float deltaTime)
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

void Mage_SIdle::Render(sf::RenderWindow* window)
{
	window->draw(*m_animation, m_mob->getShader());
}

Animation* Mage_SIdle::getSprite()
{
	return m_animation;
}
