#include "Hall.h"

Hall::Hall()
{
	m_Tiles = GConnect->getTiles();
}

Hall::~Hall()
{
}

void Hall::Init()
{
	xstart = 0;
	xend = 0;
	ystart = 0;
	yend = 0;
	m_Scale = sf::Vector2f(TileSize / 16.f, TileSize / 16.f);
	m_Length = 0;
	m_Type = BOX_DEFAULT;
}

void Hall::Update(float deltaTime)
{
}

void Hall::Reset()
{
}

sf::Vector2i Hall::getSize()
{
	return sf::Vector2i();
}

sf::Vector2i Hall::getPos()
{
	return sf::Vector2i();
}

bool Hall::getActive()
{
	return false;
}

void Hall::setActive(bool active)
{
}

void Hall::Render(sf::RenderWindow* window)
{
	if (m_Type != BOX_DEFAULT) {
		FOR(i, ystart, yend) {
			FOR(j, xstart, xend) {
				window->draw(*(*m_Tiles)[i][j]);
			}
		}
	}
}

void Hall::Create(int tileset, TileBoxType type, sf::Vector2i pos)
{
	sf::Vector2i m_DefaultTileSize(16.f, 16.f);
	m_TileSet = tileset;
	m_Type = type;
	m_Pos = pos;
	if (m_Type == HALL_HORIZONTAL) {
		xstart = m_Pos.x * RoomMaxSize - 1;
		xend = (m_Pos.x + 1) * RoomMaxSize;
		ystart = m_Pos.y * RoomMaxSize + (RoomMaxSize - HallWidth) / 2;
		yend = m_Pos.y * RoomMaxSize + (RoomMaxSize + HallWidth) / 2 - 1;
		while (xstart > 0 && (*m_Tiles)[ystart][xstart]->getType() != TileType::TILE_WALL) {
			xstart--;
		}
		while (xend < 9 * RoomMaxSize - 1  && (*m_Tiles)[ystart][xend]->getType() != TileType::TILE_WALL) {
			xend++;
		}
	}
	else {	
		xstart = m_Pos.x * RoomMaxSize + (RoomMaxSize - HallWidth) / 2;
		xend = m_Pos.x * RoomMaxSize + (RoomMaxSize + HallWidth) / 2 - 1;
		ystart = m_Pos.y * RoomMaxSize - 1;
		yend = (m_Pos.y + 1) * RoomMaxSize;
		while (ystart > 0 && (*m_Tiles)[ystart][xstart]->getType() != TileType::TILE_WALL) {
			ystart--;
		}
		while (yend < 9 * RoomMaxSize - 1 && (*m_Tiles)[yend][xstart]->getType() != TileType::TILE_WALL) {
			yend++;
		}
	}
	string locate = "../Map/TileSet" + to_string(m_TileSet);
	int x, y;
	if (m_Type == HALL_HORIZONTAL) {

		FOR(i, xstart, xend) {
			x = i;
			y = ystart;
			(*m_Tiles)[y][x]->setTexture(*ASSET->getTexture(locate));
			m_CurrentTiltePos = sf::Vector2i(MapTile[m_TileSet][1].x * m_DefaultTileSize.x, MapTile[m_TileSet][1].y * m_DefaultTileSize.x);
			(*m_Tiles)[y][x]->setTextureRect(sf::IntRect(m_CurrentTiltePos, m_DefaultTileSize));
			(*m_Tiles)[y][x]->setType(TileType::TILE_WALL);
		}

		//---------------------------------------//

		FOR(i, xstart, xend) {
			x = i;
			y = yend;
			(*m_Tiles)[y][x]->setTexture(*ASSET->getTexture(locate));
			m_CurrentTiltePos = sf::Vector2i(MapTile[m_TileSet][5].x * m_DefaultTileSize.x, MapTile[m_TileSet][5].y * m_DefaultTileSize.x);
			(*m_Tiles)[y][x]->setTextureRect(sf::IntRect(m_CurrentTiltePos, m_DefaultTileSize));
			(*m_Tiles)[y][x]->setType(TileType::TILE_WALL);
		}

		//---------------------------------------//

		x = xstart;
		y = ystart;
		(*m_Tiles)[y][x]->setTexture(*ASSET->getTexture(locate));
		m_CurrentTiltePos = sf::Vector2i(MapTile[m_TileSet][6].x * m_DefaultTileSize.x, MapTile[m_TileSet][6].y * m_DefaultTileSize.x);
		(*m_Tiles)[y][x]->setTextureRect(sf::IntRect(m_CurrentTiltePos, m_DefaultTileSize));
		(*m_Tiles)[y][x]->setType(TileType::TILE_WALL);

		//---------------------------------------//

		x = xend;
		y = ystart;
		(*m_Tiles)[y][x]->setTexture(*ASSET->getTexture(locate));
		m_CurrentTiltePos = sf::Vector2i(MapTile[m_TileSet][4].x * m_DefaultTileSize.x, MapTile[m_TileSet][4].y * m_DefaultTileSize.x);
		(*m_Tiles)[y][x]->setTextureRect(sf::IntRect(m_CurrentTiltePos, m_DefaultTileSize));
		(*m_Tiles)[y][x]->setType(TileType::TILE_WALL);

		//---------------------------------------//

		x = xstart;    // 1
		y = yend;
		(*m_Tiles)[y][x]->setTexture(*ASSET->getTexture(locate));
		m_CurrentTiltePos = sf::Vector2i(MapTile[m_TileSet][0].x * m_DefaultTileSize.x, MapTile[m_TileSet][0].y * m_DefaultTileSize.x);
		(*m_Tiles)[y][x]->setTextureRect(sf::IntRect(m_CurrentTiltePos, m_DefaultTileSize));
		(*m_Tiles)[y][x]->setType(TileType::TILE_WALL);

		//---------------------------------------//

		x = xend;      // 6
		y = yend;
		(*m_Tiles)[y][x]->setTexture(*ASSET->getTexture(locate));
		m_CurrentTiltePos = sf::Vector2i(MapTile[m_TileSet][2].x * m_DefaultTileSize.x, MapTile[m_TileSet][2].y * m_DefaultTileSize.x);
		(*m_Tiles)[y][x]->setTextureRect(sf::IntRect(m_CurrentTiltePos, m_DefaultTileSize));
		(*m_Tiles)[y][x]->setType(TileType::TILE_WALL);

		//---------------------------------------//

		//---------------------------------------//

		FOR(i, ystart + 1, yend - 1) {
			FOR(j, xstart, xend) {
				x = j;
				y = i;
				(*m_Tiles)[y][x]->setTexture(*ASSET->getTexture(locate));
				m_CurrentTiltePos = sf::Vector2i(MapTile[m_TileSet][8].x * m_DefaultTileSize.x, MapTile[m_TileSet][8].y * m_DefaultTileSize.x);
				(*m_Tiles)[y][x]->setTextureRect(sf::IntRect(m_CurrentTiltePos, m_DefaultTileSize));
				(*m_Tiles)[y][x]->setType(TileType::TILE_FLOOR);
				m_preTexture = *ASSET->getTexture(locate);
				m_preIntRect = (*m_Tiles)[y][x]->getTextureRect();
			}
		}
	}
	else {
		FOR(i, ystart, yend) {
			x = xstart;
			y = i;
			(*m_Tiles)[y][x]->setTexture(*ASSET->getTexture(locate));
			m_CurrentTiltePos = sf::Vector2i(MapTile[m_TileSet][3].x * m_DefaultTileSize.x, MapTile[m_TileSet][3].y * m_DefaultTileSize.x);
			(*m_Tiles)[y][x]->setTextureRect(sf::IntRect(m_CurrentTiltePos, m_DefaultTileSize));
			(*m_Tiles)[y][x]->setType(TileType::TILE_WALL);
		}

		//---------------------------------------//

		FOR(i, ystart, yend) {
			x = xend;
			y = i;
			(*m_Tiles)[y][x]->setTexture(*ASSET->getTexture(locate));
			m_CurrentTiltePos = sf::Vector2i(MapTile[m_TileSet][7].x * m_DefaultTileSize.x, MapTile[m_TileSet][7].y * m_DefaultTileSize.x);
			(*m_Tiles)[y][x]->setTextureRect(sf::IntRect(m_CurrentTiltePos, m_DefaultTileSize));
			(*m_Tiles)[y][x]->setType(TileType::TILE_WALL);
		}

		//---------------------------------------//

		x = xstart;
		y = ystart;
		(*m_Tiles)[y][x]->setTexture(*ASSET->getTexture(locate));
		m_CurrentTiltePos = sf::Vector2i(MapTile[m_TileSet][2].x * m_DefaultTileSize.x, MapTile[m_TileSet][2].y * m_DefaultTileSize.x);
		(*m_Tiles)[y][x]->setTextureRect(sf::IntRect(m_CurrentTiltePos, m_DefaultTileSize));
		(*m_Tiles)[y][x]->setType(TileType::TILE_WALL);

		//---------------------------------------//

		x = xend;
		y = ystart;
		(*m_Tiles)[y][x]->setTexture(*ASSET->getTexture(locate));
		m_CurrentTiltePos = sf::Vector2i(MapTile[m_TileSet][0].x * m_DefaultTileSize.x, MapTile[m_TileSet][0].y * m_DefaultTileSize.x);
		(*m_Tiles)[y][x]->setTextureRect(sf::IntRect(m_CurrentTiltePos, m_DefaultTileSize));
		(*m_Tiles)[y][x]->setType(TileType::TILE_WALL);

		//---------------------------------------//

		x = xstart;
		y = yend;
		(*m_Tiles)[y][x]->setTexture(*ASSET->getTexture(locate));
		m_CurrentTiltePos = sf::Vector2i(MapTile[m_TileSet][4].x * m_DefaultTileSize.x, MapTile[m_TileSet][4].y * m_DefaultTileSize.x);
		(*m_Tiles)[y][x]->setTextureRect(sf::IntRect(m_CurrentTiltePos, m_DefaultTileSize));
		(*m_Tiles)[y][x]->setType(TileType::TILE_WALL);

		//---------------------------------------//

		x = xend;
		y = yend;
		(*m_Tiles)[y][x]->setTexture(*ASSET->getTexture(locate));
		m_CurrentTiltePos = sf::Vector2i(MapTile[m_TileSet][6].x * m_DefaultTileSize.x, MapTile[m_TileSet][6].y * m_DefaultTileSize.x);
		(*m_Tiles)[y][x]->setTextureRect(sf::IntRect(m_CurrentTiltePos, m_DefaultTileSize));
		(*m_Tiles)[y][x]->setType(TileType::TILE_WALL);

		//---------------------------------------//

		FOR(i, ystart, yend) {
			FOR(j, xstart + 1, xend - 1) {
				x = j;
				y = i;
				(*m_Tiles)[y][x]->setTexture(*ASSET->getTexture(locate));
				m_CurrentTiltePos = sf::Vector2i(MapTile[m_TileSet][8].x * m_DefaultTileSize.x, MapTile[m_TileSet][8].y * m_DefaultTileSize.x);
				(*m_Tiles)[y][x]->setTextureRect(sf::IntRect(m_CurrentTiltePos, m_DefaultTileSize));
				(*m_Tiles)[y][x]->setType(TileType::TILE_FLOOR);
				m_preTexture = *ASSET->getTexture(locate);
				m_preIntRect = (*m_Tiles)[y][x]->getTextureRect();
			}
		}	
	}

	FOR(i, ystart, yend) {
		FOR(j, xstart, xend) {
			x = j;
			y = i;
			(*m_Tiles)[y][x]->setScale(m_Scale);
		}
	}
}

TileBoxType Hall::getType()
{
	return m_Type;
}

void Hall::setType(TileBoxType type)
{
	m_Type = type;
}

void Hall::RoomActive(bool active)
{
	if (m_Type == HALL_HORIZONTAL) {
		FOR(i, ystart + 1, yend - 1) {
			(*m_Tiles)[i][xstart]->setType(active ? TileType::TILE_DOOR : TileType::TILE_FLOOR);
			(*m_Tiles)[i][xstart]->setTexture(active ? *ASSET->getTexture("../Map/Door") : m_preTexture);
			if (active == false) (*m_Tiles)[i][xstart]->setTextureRect(m_preIntRect);
			(*m_Tiles)[i][xend]->setType(active ? TileType::TILE_DOOR : TileType::TILE_FLOOR);
			(*m_Tiles)[i][xend]->setTexture(active ? *ASSET->getTexture("../Map/Door") : m_preTexture);
			if (active == false) (*m_Tiles)[i][xend]->setTextureRect(m_preIntRect);
			
		}
	}
	else if (m_Type == HALL_VERTICAL) {
		FOR(i, xstart + 1, xend - 1) {
			(*m_Tiles)[ystart][i]->setType(active ? TileType::TILE_DOOR : TileType::TILE_FLOOR);
			(*m_Tiles)[ystart][i]->setTexture(active ? *ASSET->getTexture("../Map/Door") : m_preTexture);
			if (active == false) (*m_Tiles)[ystart][i]->setTextureRect(m_preIntRect);
			(*m_Tiles)[yend][i]->setType(active ? TileType::TILE_DOOR : TileType::TILE_FLOOR);
			(*m_Tiles)[yend][i]->setTexture(active ? *ASSET->getTexture("../Map/Door") : m_preTexture);
			if (active == false) (*m_Tiles)[yend][i]->setTextureRect(m_preIntRect);
		}
	}


	
}

sf::Vector2i Hall::getStart()
{
	return sf::Vector2i(xstart, ystart);
}

sf::Vector2i Hall::getEnd()
{
	return sf::Vector2i(xend, yend);
}
