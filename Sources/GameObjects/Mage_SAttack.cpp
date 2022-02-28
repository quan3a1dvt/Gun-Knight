#include "Mage_SAttack.h"
#include "../GameManager/BulletsManager.h";
Mage_SAttack::Mage_SAttack(IMob* mob)
{
	m_mob = mob;
}

void Mage_SAttack::Init()
{
	m_animation = new Animation(*ASSET->getTexture("Mob/Mage/Mage_Attack_Sprite_Sheet"), sf::Vector2i(4, 1), 0.1f);
	//printf("%f %f\n", m_animation->getTexture()->getSize().x * 3.f / 8, m_animation->getTexture()->getSize().y * 3.f / 4);
	m_animation->setScale(m_mob->getScale());
	m_animation->setOrigin(m_animation->getOrigin().x - m_animation->GetRectSize().x * m_mob->getScale().x / 14, m_animation->getOrigin().y);
}

void Mage_SAttack::Update(float deltaTime)
{

	if (m_animation->Play(deltaTime)) {
		int rand = random::random(2, 3);
		if (rand == 1) {
			vector<float> temp(3, -1);
			temp[0] = 200.f;
			temp[1] = 2.f;
			temp[2] = 0.f;
			BManager->Create(ShootType::SHOOT_1, BulletType::BULLET_ROUND2, "ROUND1", m_mob->getHitBox()->getPosition(), sf::Vector2f(20.f * GlobalScale.x, 20.f * GlobalScale.y), false, 10, temp),
			m_mob->ChangeNextState(STATE_IDLE);
		}
		else if (rand == 2){
			vector<float> temp(3, -1);
			temp[0] = 200.f;
			temp[1] = 10.f;
			temp[2] = 0.f;
			BManager->Create(ShootType::SHOOT_1, BulletType::BULLET_ROUND1, "ROUND1", m_mob->getHitBox()->getPosition(), sf::Vector2f(20.f * GlobalScale.x, 20.f * GlobalScale.y), false, 10, temp),
			m_mob->ChangeNextState(STATE_IDLE);
		}
		else if (rand == 3) {
			vector<float> temp(5, -1);
			temp[0] = 200.f;
			temp[1] = 3.f;
			temp[2] = Collision::degree(m_mob->getHitBox()->getPosition(), GConnect->getPlayer()->getHitBox()->getPosition());
			temp[3] = 4.f;
			temp[4] = 0.f;
			BManager->Create(ShootType::SHOOT_3, BulletType::BULLET_ROUND1, "ROUND1", m_mob->getHitBox()->getPosition(), sf::Vector2f(20.f * GlobalScale.x, 20.f * GlobalScale.y), false, 10, temp),
			m_mob->ChangeNextState(STATE_IDLE);
		}
	}

	m_animation->setPosition(m_mob->getHitBox()->getPosition());
	if (m_mob->getCW()) {
		m_animation->setScale(fabs(m_animation->getScale().x), fabs(m_animation->getScale().y));
	}
	else {
		m_animation->setScale(-fabs(m_animation->getScale().x), fabs(m_animation->getScale().y));
	}
}

void Mage_SAttack::Render(sf::RenderWindow* window)
{
	window->draw(*m_animation, m_mob->getShader());
}

Animation* Mage_SAttack::getSprite()
{
	return m_animation;
}
