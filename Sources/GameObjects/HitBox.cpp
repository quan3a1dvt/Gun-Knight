#include "HitBox.h"



HitBox::HitBox(sf::Vector2i size) : RectangleShape((sf::Vector2f)size)
{
    this->setOrigin((sf::Vector2f)size / 2.f);
    this->setFillColor(sf::Color(0,0,0,0));
    this->setOutlineThickness(1.0f);
    this->setOutlineColor(sf::Color::Red);
    m_velocity = 0.f;
}

HitBox::HitBox()
{
    this->setSize(sf::Vector2f(10.f, 10.f));
}

HitBox::~HitBox()
{
}

void HitBox::Init(float velocity)
{
   
    m_velocity = velocity;
}

float HitBox::GetVelocity()
{
    return m_velocity;
}
