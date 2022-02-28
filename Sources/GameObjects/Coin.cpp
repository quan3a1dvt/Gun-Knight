#include "Coin.h"

Coin::Coin()
{
	m_Active = false;
	m_Coin = new Animation(*ASSET->getTexture("Coin"), sf::Vector2i(5, 1), 0.1f);
	m_HitBox = new HitBox((sf::Vector2i)m_Coin->GetRectSize());
	m_Value = 1;
}

Coin::~Coin()
{
}

void Coin::Init()
{
	
	
}

void Coin::Update(float deltaTime)
{
	if (m_Active) m_Coin->Update(deltaTime);
}

void Coin::Render(sf::RenderWindow* window)
{
	if (m_Active) {
		window->draw(*m_Coin);
		//window->draw(*m_HitBox);
	}

}
void Coin::Reset(sf::Vector2f pos, int value)
{
	m_HitBox->setPosition(pos);
	m_Coin->setPosition(m_HitBox->getPosition());
	m_Value = value;
	m_Active = true;
}
HitBox* Coin::getHitBox()
{
	return m_HitBox;
}
int Coin::getValue()
{
	return m_Value;
}

bool Coin::getActive()
{
	return m_Active;
}

void Coin::setActive(bool active)
{
	m_Active = active;
}

