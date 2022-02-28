#include "PSIdle.h"
#include "TiledMap.h"
PSIdle::PSIdle(IPlayer* Player)
{
	m_Player = Player;
}

void PSIdle::Init()
{
	m_animation = new Animation(*ASSET->getTexture("Character/knight_idle_spritesheet"), sf::Vector2i(6, 1), 0.1f);
	m_animation->setScale(m_Player->getScale());
}
float rota = 10.0f;
void PSIdle::Update(float deltaTime)
{
	m_animation->Update(deltaTime);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		float movex = 0.f;
		float movey = 0.f;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
			m_Player->ChangeNextState(STATE_RUN);
			movex = -m_Player->getHitBox()->GetVelocity() * deltaTime;
			movey = 0.f;
			m_Player->Move(movex, movey);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
			m_Player->ChangeNextState(STATE_RUN);
			movex = m_Player->getHitBox()->GetVelocity() * deltaTime;
			movey = 0.f;
			m_Player->Move(movex, movey);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
			m_Player->ChangeNextState(STATE_RUN);
			movex = 0.f;
			movey = -m_Player->getHitBox()->GetVelocity() * deltaTime;
			m_Player->Move(movex, movey);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
			m_Player->ChangeNextState(STATE_RUN);
			movex = 0.f;
			movey = m_Player->getHitBox()->GetVelocity() * deltaTime;
			m_Player->Move(movex, movey);
		}
		
	}
	else {
		m_Player->ChangeNextState(STATE_IDLE);
	}
	m_animation->setPosition(m_Player->getHitBox()->getPosition());
	float hitboxCenterX = m_Player->getHitBox()->getPosition().x;
	float mousePosX = sf::Mouse::getPosition(*WConnect->getWindow()).x + m_Player->getHitBox()->getPosition().x - screenWidth / 2;
	//printf("%f %f\n", mousePosX, hitboxCenterX);
	if (m_Player->getCW()) {
		if (mousePosX <= hitboxCenterX - m_Player->getHitBox()->getSize().x / 4) {
			m_Player->setCW(false);
		}
	}
	else {
		if (mousePosX >= hitboxCenterX + m_Player->getHitBox()->getSize().x / 4) {
			m_Player->setCW(true);
		}
	}
	if (m_Player->getCW()) {
		m_animation->setScale(fabs(m_animation->getScale().x), m_animation->getScale().y);
	}
	else {
		m_animation->setScale(-fabs(m_animation->getScale().x), m_animation->getScale().y);
	}
	
	//printf("%d\n", m_Player->getCW());
	//printf("%f %f %d\n", mousePosX, hitboxCenterX + m_Player->getHitBox()->getSize().x / 4, (mousePosX <= hitboxCenterX + m_Player->getHitBox()->getSize().x / 4));

}

void PSIdle::Render(sf::RenderWindow* window)
{
	window->draw(*m_animation);
}
