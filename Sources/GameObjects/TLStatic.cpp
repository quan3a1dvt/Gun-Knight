#include "TLStatic.h"

void TLStatic::Init(string name, sf::Vector2i hitboxSize)
{
	m_spire->setTexture(*ASSET->getTexture("Tiled/" + name));
	m_hitbox = new HitBox(hitboxSize);
}

void TLStatic::Update(float deltaTime)
{
}

void TLStatic::Render(sf::RenderWindow* window)
{
	window->draw(*m_spire);
}

HitBox* TLStatic::GetHitBox()
{
	return m_hitbox;
}
