#include "Cobra_SHit.h"

Cobra_SHit::Cobra_SHit(IMob* mob)
{
	m_mob = mob;
}

void Cobra_SHit::Init()
{
	m_animation = new Animation(*ASSET->getTexture("Mob/Cobra/Cobra_Hit_Sprite_Sheet"), sf::Vector2i(4, 1), 0.1f);
	//printf("%f %f\n", m_animation->getTexture()->getSize().x * 3.f / 8, m_animation->getTexture()->getSize().y * 3.f / 4);

	m_animation->setScale(m_mob->getScale());
	m_animation->setOrigin(m_animation->GetRectSize().x * 3.f / 8, m_animation->GetRectSize().y * 4.f / 5);
}

void Cobra_SHit::Update(float deltaTime)
{
	if (m_animation->Play(deltaTime)) {
		m_mob->ChangeNextState(STATE_IDLE);
		m_mob->SetCanMove(true);
	}

	m_animation->setPosition(m_mob->GetHitBox()->getPosition());
	if (m_mob->getCW()) {
		m_animation->setScale(fabs(m_animation->getScale().x), fabs(m_animation->getScale().y));
	}
	else {
		m_animation->setScale(-fabs(m_animation->getScale().x), fabs(m_animation->getScale().y));
	}
}

void Cobra_SHit::Render(sf::RenderWindow* window)
{
	window->draw(*m_animation);
}
