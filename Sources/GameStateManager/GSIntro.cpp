#include "GSIntro.h"

GSIntro::GSIntro()
{
	m_currentTime = 0.f;
}

GSIntro::~GSIntro()
{
}

void GSIntro::Exit()
{
}

void GSIntro::Pause()
{
}

void GSIntro::Resume()
{
}

void GSIntro::Init()
{
	//sf::Texture* texture = ASSET->getTexture("Logo");
	//m_logo.setTexture(*texture);
	//m_logo.setOrigin((sf::Vector2f)texture->getSize() / 2.f);
	//m_logo.setPosition(screenWidth / 2, screenHeight / 2);
}

void GSIntro::Update(float deltaTime)
{
	m_currentTime += deltaTime;
	if (m_currentTime > 1.f) {
		GameStateMachine::GetInstance()->ChangeState(StateTypes::STATE_MENU);
	}
}

void GSIntro::Render(sf::RenderWindow* window)
{
	window->draw(m_logo);
}
