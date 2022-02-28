#include "Cobra_SAttack.h"

Cobra_SAttack::Cobra_SAttack(IMob* mob)
{
	m_mob = mob;
}

void Cobra_SAttack::Init()
{
	m_animation = new Animation(*ASSET->getTexture("Mob/Cobra/Cobra_Attack_Sprite_Sheet"), sf::Vector2i(6, 1), 0.1f);
	//printf("%f %f\n", m_animation->getTexture()->getSize().x * 3.f / 8, m_animation->getTexture()->getSize().y * 3.f / 4);
	m_animation->setScale(m_mob->getScale());
	m_animation->setOrigin(m_animation->GetRectSize().x * 3.f / 8, m_animation->GetRectSize().y * 4.f / 5);
}

void Cobra_SAttack::Update(float deltaTime)
{
	if (m_animation->Play(deltaTime)) {
		if (Collision::BoundingBoxTest(m_mob->getHitBox(), GConnect->getPlayer()->getHitBox())) {
			GConnect->getPlayer()->LoseHp(m_mob->getDamage());
		}
		m_mob->ChangeNextState(STATE_IDLE);
	}

	m_animation->setPosition(m_mob->getHitBox()->getPosition());
	if (m_mob->getCW()) {
		m_animation->setScale(fabs(m_animation->getScale().x), fabs(m_animation->getScale().y));
	}
	else {
		m_animation->setScale(-fabs(m_animation->getScale().x), fabs(m_animation->getScale().y));
	}
}

void Cobra_SAttack::Render(sf::RenderWindow* window)
{
	window->draw(*m_animation);
}

Animation* Cobra_SAttack::getSprite()
{
	return m_animation;
}
