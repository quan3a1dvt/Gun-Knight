#pragma once
#include <SFML/Graphics.hpp>
#define screenWidth 1280
#define screenHeight 800
#define titleGame "Knight"
#define FOR(i,a,b) for(int i=a;i<=b;i++)
#define FORD(i,a,b) for(int i=a;i>=b;i--)
#define fi first
#define se second
#define mp make_pair
#define eachmtypenumber 5
#define RoomMaxSize 27


const sf::Texture DefaultTexture;

const float sqSide = 640.f;

const int BulletsNumber = 200;

const float TileSize = 48.f;

const sf::Vector2f GlobalScale(1.f, 1.f);

const int HallWidth = 7;

const int RandomRoomSize[3] = { 17, 21, 25 };

const sf::Vector2i RoomSize[] = {
	sf::Vector2i(27,27),
	sf::Vector2i(17,17),
	sf::Vector2i(13,13),
	sf::Vector2i(27,27),
	sf::Vector2i(17,17),
};

const sf::Vector2i MapTile[4][10]{
	{
		sf::Vector2i(2,0),
		sf::Vector2i(3,0),
		sf::Vector2i(4,0),
		sf::Vector2i(4,2),
		sf::Vector2i(4,1),
		sf::Vector2i(3,0),
		sf::Vector2i(2,2),
		sf::Vector2i(4,2),
		sf::Vector2i(1,0),
	},
	{
		sf::Vector2i(0,0),
		sf::Vector2i(3,0),
		sf::Vector2i(10,0),
		sf::Vector2i(10,1),
		sf::Vector2i(10,4),
		sf::Vector2i(6,4),
		sf::Vector2i(0,4),
		sf::Vector2i(0,1),
		sf::Vector2i(5,6),
	},
};

const int tiledmap[3][3][4][4] = {
	//0:start
	//10:end
	//1:fight
	//2:chest
	{
		{
			{-1,2,-1,-1},
			{-1,1,1,10},
			{-1,1,-1,-1},
			{-1,0,-1,-1},
		},
	}
};
// room scale
const sf::Vector2f roomscale[3][3][4][4] = {
	{
		{
			{{},{sf::Vector2f(1,1)},{},{}},
			{{},{sf::Vector2f(1,1)},{sf::Vector2f(1,1)},{sf::Vector2f(1,1)}},
			{{},{sf::Vector2f(1,1)},{},{}},
			{{},{sf::Vector2f(1,1)},{},{}},
		},
	}
};
// wave_number and mobtype_number
const int mobswaves[3][3][4][4][2] = {
	{
		{
			{{},{},{},{}},
			{{},{3,1},{2,1},{}},
			{{},{1,1},{},{}},
			{{},{},{},{}},
		},
	}
};

const int mobswavesdata[3][3][4][4][3][1] = {
	{
		{
			{{},{},{},{}},
			{{},{{3},{3},{3}},{{1},{3}},{}},
			{{},{{3}},{},{}},
			{{},{},{},{}},
		},
	}
};
