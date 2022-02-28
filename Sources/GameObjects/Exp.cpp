#include "Exp.h"

Exp::Exp()
{
	m_Active = false;
	m_Exp = new Animation(*ASSET->getTexture("Exp"), sf::Vector2i(4, 1), 0.1f);
	m_HitBox = new HitBox((sf::Vector2i)m_Exp->GetRectSize());
	m_Value = 3;
}

Exp::~Exp()
{
}

void Exp::Init()
{


}

void Exp::Update(float deltaTime)
{
	if (m_Active) m_Exp->Update(deltaTime);
}

void Exp::Render(sf::RenderWindow* window)
{
	if (m_Active) {
		window->draw(*m_Exp);
		//window->draw(*m_HitBox);
	}

}
void Exp::Reset(sf::Vector2f pos, int value)
{
	m_HitBox->setPosition(pos);
	m_Exp->setPosition(m_HitBox->getPosition());
	m_Active = true;
	m_Value = value;
}
HitBox* Exp::getHitBox()
{
	return m_HitBox;
}
int Exp::getValue()
{
	return m_Value;
}

bool Exp::getActive()
{
	return m_Active;
}

void Exp::setActive(bool active)
{
	m_Active = active;
}

