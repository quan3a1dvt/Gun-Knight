#include "Mage_SRun.h"

Mage_SRun::Mage_SRun(IMob* mob)
{
	m_mob = mob;
}

void Mage_SRun::Init()
{
	m_animation = new Animation(*ASSET->getTexture("Mob/Mage/Mage_Run_Sprite_Sheet"), sf::Vector2i(3, 1), 0.1f);
	//printf("%f %f\n", m_animation->getTexture()->getSize().x * 3.f / 8, m_animation->getTexture()->getSize().y * 3.f / 4);

	m_animation->setScale(m_mob->getScale());
	m_animation->setOrigin(m_animation->getOrigin().x - m_animation->GetRectSize().x * m_mob->getScale().x / 14, m_animation->getOrigin().y);
}

void Mage_SRun::Update(float deltaTime)
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

void Mage_SRun::Render(sf::RenderWindow* window)
{
	window->draw(*m_animation, m_mob->getShader());
}

Animation* Mage_SRun::getSprite()
{
	return m_animation;
}
