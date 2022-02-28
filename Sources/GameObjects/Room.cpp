#include "Room.h"
#include "ShopItem.h"
Room::Room()
{
	m_Tiles = GConnect->getTiles();
	m_ShopItems.resize(4);
}

Room::~Room()
{
}

void Room::Init()
{
	xstart = 0;
	xend = 0;
	ystart = 0;
	yend = 0;
	m_Scale = sf::Vector2f(TileSize / 16.f, TileSize / 16.f);
	m_Size = sf::Vector2i(0, 0);
	m_Active = false;
	m_Type = BOX_DEFAULT;
}

void Room::Update(float deltaTime)
{
	if (m_Type == ROOM_CHEST) {
		FOR(i, 0, m_ShopItems.size() - 1) {
			m_ShopItems[i].Update(deltaTime);
		}
	}
}

void Room::Render(sf::RenderWindow* window)
{
	if (m_Type != BOX_DEFAULT) {
		FOR(i, ystart, yend) {
			FOR(j, xstart, xend) {
				window->draw(*(*m_Tiles)[i][j]);
			}
		}
	}
	if (m_Type == ROOM_CHEST) {
		FOR(i, 0, m_ShopItems.size() - 1) {
			m_ShopItems[i].Render(window);
		}
	}
}
void Room::Reset()
{
	m_Size = sf::Vector2i(0, 0);
	FOR(i, 0, m_ShopItems.size() - 1) {
		m_ShopItems[i].Create(sf::Vector2f(0.f, 0.f), ShopItemType::DEFAULT);
	}
	m_Type = BOX_DEFAULT;
}
// default tile size 16p x 16p
void Room::Create(int tileset, TileBoxType type, sf::Vector2i pos)
{
	sf::Vector2i m_DefaultTileSize(16.f, 16.f);
	m_TileSet = tileset;
	m_Type = type;
	m_Pos = pos;
	if (m_Type == ROOM_NORMAL) {
		m_Size = sf::Vector2i(RandomRoomSize[random::random(0, 2)], RandomRoomSize[random::random(0, 2)]);
	}
	else {
		m_Size = RoomSize[m_Type];
	}

	

	xstart = m_Pos.x * RoomMaxSize + (RoomMaxSize - m_Size.x) / 2;
	xend = m_Pos.x * RoomMaxSize + (RoomMaxSize + m_Size.x) / 2 - 1;
	ystart = m_Pos.y * RoomMaxSize + (RoomMaxSize - m_Size.y) / 2;
	yend = m_Pos.y * RoomMaxSize + (RoomMaxSize + m_Size.y) / 2 - 1;


	string locate = "../Map/TileSet" + to_string(m_TileSet);
	int x, y;


	FOR(i, xstart, xend) {
		x = i;
		y = ystart;
		(*m_Tiles)[y][x]->setTexture(*ASSET->getTexture(locate));
		m_CurrentTiltePos = sf::Vector2i(MapTile[m_TileSet][1].x * m_DefaultTileSize.x, MapTile[m_TileSet][1].y * m_DefaultTileSize.x);
		(*m_Tiles)[y][x]->setTextureRect(sf::IntRect(m_CurrentTiltePos, m_DefaultTileSize));
		(*m_Tiles)[y][x]->setType(TileType::TILE_WALL);
	}

	//---------------------------------------//

	FOR(i, ystart, yend) {
		x = xend;
		y = i;
		(*m_Tiles)[y][x]->setTexture(*ASSET->getTexture(locate));
		m_CurrentTiltePos = sf::Vector2i(MapTile[m_TileSet][3].x * m_DefaultTileSize.x, MapTile[m_TileSet][3].y * m_DefaultTileSize.x);
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

	FOR(i, ystart, yend) {
		x = xstart;
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
	m_CurrentTiltePos = sf::Vector2i(MapTile[m_TileSet][0].x * m_DefaultTileSize.x, MapTile[m_TileSet][0].y * m_DefaultTileSize.x);
	(*m_Tiles)[y][x]->setTextureRect(sf::IntRect(m_CurrentTiltePos, m_DefaultTileSize));
	(*m_Tiles)[y][x]->setType(TileType::TILE_WALL);


	//---------------------------------------//

	x = xend;
	y = ystart;
	(*m_Tiles)[y][x]->setTexture(*ASSET->getTexture(locate));
	m_CurrentTiltePos = sf::Vector2i(MapTile[m_TileSet][2].x * m_DefaultTileSize.x, MapTile[m_TileSet][2].y * m_DefaultTileSize.x);
	(*m_Tiles)[y][x]->setTextureRect(sf::IntRect(m_CurrentTiltePos, m_DefaultTileSize));
	(*m_Tiles)[y][x]->setType(TileType::TILE_WALL);

	//---------------------------------------//



	x = xend;
	y = yend;
	(*m_Tiles)[y][x]->setTexture(*ASSET->getTexture(locate));
	m_CurrentTiltePos = sf::Vector2i(MapTile[m_TileSet][4].x * m_DefaultTileSize.x, MapTile[m_TileSet][4].y * m_DefaultTileSize.x);
	(*m_Tiles)[y][x]->setTextureRect(sf::IntRect(m_CurrentTiltePos, m_DefaultTileSize));
	(*m_Tiles)[y][x]->setType(TileType::TILE_WALL);

	//---------------------------------------//



	x = xstart;
	y = yend;
	(*m_Tiles)[y][x]->setTexture(*ASSET->getTexture(locate));
	m_CurrentTiltePos = sf::Vector2i(MapTile[m_TileSet][6].x * m_DefaultTileSize.x, MapTile[m_TileSet][6].y * m_DefaultTileSize.x);
	(*m_Tiles)[y][x]->setTextureRect(sf::IntRect(m_CurrentTiltePos, m_DefaultTileSize));
	(*m_Tiles)[y][x]->setType(TileType::TILE_WALL);

	//---------------------------------------//


	//---------------------------------------//

	FOR(i, ystart + 1, yend - 1) {
		FOR(j, xstart + 1, xend - 1) {
			x = j;
			y = i;
			(*m_Tiles)[y][x]->setTexture(*ASSET->getTexture(locate));
			m_CurrentTiltePos = sf::Vector2i(MapTile[m_TileSet][8].x * m_DefaultTileSize.x, MapTile[m_TileSet][8].y * m_DefaultTileSize.x);
			(*m_Tiles)[y][x]->setTextureRect(sf::IntRect(m_CurrentTiltePos, m_DefaultTileSize));
			(*m_Tiles)[y][x]->setType(TileType::TILE_FLOOR);
		}
	}

	//---------------------------------------//

	FOR(i, ystart, yend) {
		FOR(j, xstart, xend) {
			x = j;
			y = i;
			(*m_Tiles)[y][x]->setScale(m_Scale);
		}
	}

	if (m_Type == ROOM_NORMAL)
	{
		m_Active = true;
		m_WavesNum = random::random(1, 2);
		FOR(i, 0, m_WavesNum) {
			FOR(j, 0, 3) {
				m_WavesData[i][j] = 0;
			}
			m_WavesData[i][0] = random::random(0, 0);
			m_WavesData[i][1] = random::random(2, 3);
			m_WavesData[i][2] = random::random(1, 2);
		}
		m_WavesData[0][0] = 0;
		m_WavesData[0][1] = 0;
		m_WavesData[0][2] = 0;
	}
	else if(m_Type == ROOM_BOSS)
	{
		m_Active = true;
		m_WavesNum = random::random(3, 4);
		FOR(i, 0, m_WavesNum) {
			FOR(j, 0, 3) {
				m_WavesData[i][j] = 0;
			}
			m_WavesData[i][0] = random::random(0, 0);
			m_WavesData[i][1] = random::random(3, 5);
			m_WavesData[i][2] = random::random(3, 5);
		}
		m_WavesData[0][0] = 0;
		m_WavesData[0][1] = 0;
		m_WavesData[0][2] = 0;
	}
	else m_Active = false;

	if (m_Type == ROOM_CHEST) {
		m_ShopItems[0].Create((*m_Tiles)[m_Pos.y * RoomMaxSize + RoomMaxSize / 2][m_Pos.x * RoomMaxSize + RoomMaxSize / 2 - 3]->getPosition(), ShopItemType::BANDAGE);
		m_ShopItems[1].Create((*m_Tiles)[m_Pos.y * RoomMaxSize + RoomMaxSize / 2][m_Pos.x * RoomMaxSize + RoomMaxSize / 2 - 1]->getPosition(), ShopItemType::PISTOL_B);
		m_ShopItems[2].Create((*m_Tiles)[m_Pos.y * RoomMaxSize + RoomMaxSize / 2][m_Pos.x * RoomMaxSize + RoomMaxSize / 2 + 1]->getPosition(), ShopItemType::SHOTGUN_B);
		m_ShopItems[3].Create((*m_Tiles)[m_Pos.y * RoomMaxSize + RoomMaxSize / 2][m_Pos.x * RoomMaxSize + RoomMaxSize / 2 + 3]->getPosition(), ShopItemType::SMG_B);
	}
	
}

sf::Vector2i Room::getSize()
{
	return m_Size;
}

sf::Vector2i Room::getPos()
{
	return m_Pos;
}

bool Room::getActive()
{
	return m_Active;
}

void Room::setActive(bool active)
{
	m_Active = active;
}

void Room::RoomActive(bool active)
{
	if (active) {
		*GConnect->getWavesNum() = m_WavesNum;
		FOR(i, 0, 3) {
			FOR(j, 0, 3) {
				(*GConnect->getWavesData())[i][j] = m_WavesData[i][j];
			}
		}
	}
	else m_Active = false;
}

sf::Vector2i Room::getStart()
{
	return sf::Vector2i(xstart, ystart);
}

sf::Vector2i Room::getEnd()
{
	return sf::Vector2i(xend, yend);
}

TileBoxType Room::getType()
{
	return m_Type;
}

void Room::setType(TileBoxType type)
{
	m_Type = type;
}
