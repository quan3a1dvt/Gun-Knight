#include "Tile.h"

Tile::Tile()
{
	m_Type = TILE_DEFAULT;
	
}

Tile::~Tile()
{
}

void Tile::Init()
{
}

void Tile::Update(float deltaTime)
{
}

void Tile::Render(sf::RenderWindow* window)
{
	if (m_Type != TILE_DEFAULT) {
		window->draw(*this);
	}
}

TileType Tile::getType()
{
	return m_Type;
}

void Tile::setType(TileType type)
{
	m_Type = type;
}
