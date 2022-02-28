#include "WPSword.h"

WPSword::WPSword(IPlayer* Player)
{
	m_Player = Player;
	m_weapon = new sf::Sprite;
	m_hitMob = new vector<IMob*>;
	m_damage = 30;

	m_isAttacking = false;
	m_attackTime = 0.01f;
	m_waitTime = 0.3f;
}

WPSword::~WPSword()
{
}

void WPSword::Init()
{
	m_weapon->setTexture(*ASSET->getTexture("Sword/all_swords-23"));
	m_weapon->setOrigin(0.f, m_weapon->getTexture()->getSize().y);
	m_weapon->setScale(2.0f, 2.0f);
	
	m_HitBox = new HitBox(sf::Vector2i(m_weapon->getTexture()->getSize().x * m_weapon->getScale().x * 10 / 64, m_weapon->getTexture()->getSize().y * m_weapon->getScale().y * 45 / 64));
	m_HitBox->Init(1400.0f);
	m_HitBox->setOrigin(m_HitBox->getSize().x / 2, m_HitBox->getSize().y + float(wpSize.y) * wpScale.y * sqrt(2) / 3);

}


void WPSword::Update(float deltaTime)
{	
	
	phitboxPos = m_Player->getHitBox()->getPosition();
	phitboxScale = m_Player->getHitBox()->getScale();
	phitboxSize = m_Player->getHitBox()->getSize();
	mousePos = sf::Vector2f(sf::Mouse::getPosition(*WConnect->getWindow()).x + phitboxPos.x - screenWidth / 2, sf::Mouse::getPosition(*WConnect->getWindow()).y + phitboxPos.y - screenHeight / 2);
	wpScale = m_weapon->getScale();
	wpPos = m_weapon->getPosition();
	wpSize = m_weapon->getTexture()->getSize();
	isPlayerCW = m_Player->getCW();
	m_weapon->setPosition(phitboxPos.x + (isPlayerCW ? 1 : -1) * phitboxSize.x / 4, phitboxPos.y + phitboxSize.y/4);
	m_weapon->setScale((isPlayerCW ? 1 : -1) * fabs(wpScale.x), fabs(wpScale.y));

	m_HitBox->setPosition(wpPos);
	m_HitBox->setOrigin(m_HitBox->getSize().x / 2, m_HitBox->getSize().y + float(wpSize.y) * wpScale.y * sqrt(2) / 3);
	if (not m_isAttacking) {
		if (isPlayerCW) {

			if ((mousePos.x >= (phitboxPos.x - phitboxSize.x / 4)) && (mousePos.x <= (phitboxPos.x + phitboxSize.x / 4))) {
				angle = atan((wpPos.y - mousePos.y) / (-mousePos.x + wpPos.x)) * 57.2957795 + 45.f + 180.f;
				m_weapon->setRotation(angle);
			}
			else {
				angle = 45.f - atan((wpPos.y - mousePos.y) / (mousePos.x - wpPos.x)) * 57.2957795;
			}
			m_weapon->setRotation(angle);
			m_HitBox->setRotation(angle + 45.f);
		}
		else {

			if ((mousePos.x > (phitboxPos.x - phitboxSize.x / 4)) && (mousePos.x < (phitboxPos.x + phitboxSize.x / 4))) {
				angle = 90.f + 45.f - atan((wpPos.y - mousePos.y) / (mousePos.x - wpPos.x)) * 57.2957795;
				m_weapon->setRotation(angle);
			}
			else {
				angle = atan((wpPos.y - mousePos.y) / (-mousePos.x + wpPos.x)) * 57.2957795 - 45.f;

			}
			m_weapon->setRotation(angle);
			m_HitBox->setRotation(angle - 45.f);
		}
	}
	m_currentTime += deltaTime;
	if (m_isAttacking == true) {
		
		PerformAttackAnimation(deltaTime);
	}
	//printf("%d\n", m_isAttacking);
}



void WPSword::Render(sf::RenderWindow* window)
{
	window->draw(*m_weapon);
	//window->draw(*m_HitBox);
}

float WPSword::GetDamage()
{
	return m_damage;
}

float angleHitBox;
float angleWPState1;
float angleWPState2;
float velocity;
float state;

void WPSword::Attack(float deltaTime)
{
	if (not m_isAttacking && m_currentTime >= m_waitTime) {
		m_isAttacking = true;
		angleHitBox = m_HitBox->getRotation();
		isPlayerCW = m_Player->getCW();
		angleWPState1 = angleHitBox - (isPlayerCW ? 1 : -1) * 45.f;
		angleWPState2 = angleWPState1 + (isPlayerCW ? 1 : -1) * 120.f;
		velocity = m_HitBox->GetVelocity() * deltaTime;
		state = 1;
		m_currentTime -= m_waitTime;
		m_currentTime = 0;
	}
}

bool WPSword::isAttacking()
{
	return m_isAttacking;
}

void WPSword::PerformAttackAnimation(float deltaTime)
{
	if (isPlayerCW) {
		if (state == 1) {
			if (angleHitBox >= angleWPState1) {
				if (m_currentTime >= m_attackTime) {
					angleHitBox -= velocity;
					m_HitBox->setRotation(angleHitBox);
					m_weapon->setRotation(angleHitBox - 45.f);
					m_currentTime -= m_attackTime;
				}
			}
			else {
				state = 2;
			}
			
		}
		if (state == 2) {
			if (angleHitBox <= angleWPState2) {
				
				if (m_currentTime >= m_attackTime) {
					angleHitBox += velocity;
					m_HitBox->setRotation(angleHitBox);
					m_weapon->setRotation(angleHitBox - 45.f);
					m_currentTime -= m_attackTime;
				}
			}
			else {
				m_isAttacking = false;
				m_hitMob->clear();
			}
		}
	}
	else {
		if (state == 1) {
			if (angleHitBox <= angleWPState1) {
				if (m_currentTime >= m_attackTime) {
					angleHitBox += velocity;
					m_HitBox->setRotation(angleHitBox);
					m_weapon->setRotation(angleHitBox + 45.f);
					m_currentTime -= m_attackTime;
				}
			}
			else {
				state = 2;
			}

		}
		if (state == 2) {
			if (angleHitBox >= angleWPState2) {
				if (m_currentTime >= m_attackTime) {
					angleHitBox -= velocity;
					m_HitBox->setRotation(angleHitBox);
					m_weapon->setRotation(angleHitBox + 45.f);
					m_currentTime -= m_attackTime;
				}
			}
			else
			{
				m_isAttacking = false;
				m_hitMob->clear();
			}
		}
	}
	

}

vector<IMob*>* WPSword::GetHitMob()
{
	return m_hitMob;
}

void WPSword::AddHitMob(IMob* mob)
{
	m_hitMob->push_back(mob);
}



HitBox* WPSword::getHitBox()
{
	return m_HitBox;
}


