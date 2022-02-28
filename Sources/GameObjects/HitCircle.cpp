#include "HitCircle.h"

HitCircle::HitCircle(int radius) : CircleShape(radius)
{
    this->setOrigin(this->getRadius(), this->getRadius());
    this->setFillColor(sf::Color(0, 0, 0, 0));
    this->setOutlineThickness(1.0f);
    this->setOutlineColor(sf::Color::Red);
    m_velocity = 0.f;
}

HitCircle::HitCircle()
{
    this->setRadius(8);
}

HitCircle::~HitCircle()
{
}

void HitCircle::Init(float velocity)
{
    m_velocity = velocity;
}

float HitCircle::GetVelocity()
{
    return m_velocity;
}
