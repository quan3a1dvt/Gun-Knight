#include "Imp_SAttack.h"
#include "../GameManager/BulletsManager.h";
Imp_SAttack::Imp_SAttack(IMob* mob)
{
	m_mob = mob;
}

void Imp_SAttack::Init()
{
	m_animation = new Animation(*ASSET->getTexture("Mob/Imp/Imp_Attack_Sprite_Sheet"), sf::Vector2i(14, 1), 0.05f);
	//printf("%f %f\n", m_animation->getTexture()->getSize().x * 3.f / 8, m_animation->getTexture()->getSize().y * 3.f / 4);
	m_animation->setScale(m_mob->getScale() * 2.f);
	m_animation->setOrigin(m_animation->getOrigin().x, m_animation->getOrigin().y);
}

void Imp_SAttack::Update(float deltaTime)
{

	if (m_animation->Play(deltaTime)) {
		m_mob->setActive(false);
		GConnect->MobDeath(3);
		CManager->Create(2, 1, m_mob->getHitBox()->getPosition());
		EManager->Create(2, 1, m_mob->getHitBox()->getPosition());
	}

	m_animation->setPosition(m_mob->getHitBox()->getPosition());
	if (m_mob->getCW()) {
		m_animation->setScale(fabs(m_animation->getScale().x), fabs(m_animation->getScale().y));
	}
	else {
		m_animation->setScale(-fabs(m_animation->getScale().x), fabs(m_animation->getScale().y));
	}
}

void Imp_SAttack::Render(sf::RenderWindow* window)
{
	window->draw(*m_animation, m_mob->getShader());
}

Animation* Imp_SAttack::getSprite()
{
	return m_animation;
}
