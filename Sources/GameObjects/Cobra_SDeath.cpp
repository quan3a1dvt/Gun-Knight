#include "Cobra_SDeath.h"

Cobra_SDeath::Cobra_SDeath(IMob* mob)
{
	m_mob = mob;
}

void Cobra_SDeath::Init()
{
	m_animation = new Animation(*ASSET->getTexture("Mob/Cobra/Cobra_Death_Sprite_Sheet"), sf::Vector2i(6, 1), 0.1f);
	m_animation->setScale(m_mob->getScale());
	m_animation->setOrigin(m_animation->GetRectSize().x * 3.f / 8, m_animation->GetRectSize().y * 4.f / 5);
}

void Cobra_SDeath::Update(float deltaTime)
{
	if (m_animation->Play(deltaTime)) {
		m_mob->setActive(false);
		GConnect->MobDeath(1);
	}

	m_animation->setPosition(m_mob->getHitBox()->getPosition());
	if (m_mob->getCW()) {
		m_animation->setScale(fabs(m_animation->getScale().x), fabs(m_animation->getScale().y));
	}
	else {
		m_animation->setScale(-fabs(m_animation->getScale().x), fabs(m_animation->getScale().y));
	}
}

void Cobra_SDeath::Render(sf::RenderWindow* window)
{
	window->draw(*m_animation);
}

Animation* Cobra_SDeath::getSprite()
{
	return m_animation;
}
