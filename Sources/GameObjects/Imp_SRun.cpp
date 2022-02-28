#include "Imp_SRun.h"

Imp_SRun::Imp_SRun(IMob* mob)
{
	m_mob = mob;
}

void Imp_SRun::Init()
{
	m_animation = new Animation(*ASSET->getTexture("Mob/Imp/Imp_Run_Sprite_Sheet"), sf::Vector2i(8, 1), 0.1f);
	//printf("%f %f\n", m_animation->getTexture()->getSize().x * 3.f / 8, m_animation->getTexture()->getSize().y * 3.f / 4);

	m_animation->setScale(m_mob->getScale());
	m_animation->setOrigin(m_animation->getOrigin().x, m_animation->getOrigin().y + m_animation->GetRectSize().y * m_mob->getScale().y / 12);
}

void Imp_SRun::Update(float deltaTime)
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

void Imp_SRun::Render(sf::RenderWindow* window)
{
	window->draw(*m_animation, m_mob->getShader());
}

Animation* Imp_SRun::getSprite()
{
	return m_animation;
}
