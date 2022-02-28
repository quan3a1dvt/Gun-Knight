#include "MiniMap.h"

MiniMap::MiniMap()
{
	m_DrawMiniMap = new sf::Sprite;
	m_DrawCurrentPos = new sf::RectangleShape;
}

MiniMap::~MiniMap()
{
}

void MiniMap::Init(string locate)
{
	m_DrawMiniMap->setTexture(*ASSET->getTexture(locate));
	m_DrawMiniMap->setScale(0.1f, 0.1f);
	//m_DrawMiniMap->setColor(sf::Color(255, 255, 255, 128));
	m_DrawMiniMap->setPosition(screenWidth - m_DrawMiniMap->getTexture()->getSize().x * m_DrawMiniMap->getScale().x, 0.f);

	//m_DrawCurrentPos->setTexture(*ASSET->getTexture(locate));
	//m_DrawCurrentPos->setScale(0.1f, 0.1f);
	m_DrawCurrentPos->setFillColor(sf::Color(255, 255, 255, 128));
	//m_DrawCurrentPos->setPosition(screenWidth - m_DrawCurrentPos->getTexture()->getSize().x * m_DrawCurrentPos->getScale().x, 0.f);
}

void MiniMap::Update(float deltaTime, sf::Vector2i CurrentPos)
{
	//printf("%d %d\n", CurrentPos.x, CurrentPos.y);
	//if (CurrentPos.x != -1 && CurrentPos.y != -1) {
	//	m_InRoom = true;
	//	m_rectSize = sf::Vector2i(m_DrawMiniMap->getTexture()->getSize().x / 13 * 2, m_DrawMiniMap->getTexture()->getSize().y / 13 * 2);
	//	m_rectPos = sf::Vector2i((CurrentPos.x * 3 + 1) * m_rectSize.x / 2, (CurrentPos.y * 3 + 1) * m_rectSize.y / 2);
	//	m_DrawCurrentPos->setSize(sf::Vector2f(m_rectSize.x * m_DrawMiniMap->getScale().x, m_rectSize.y * m_DrawMiniMap->getScale().y));
	//	m_DrawCurrentPos->setPosition(m_rectPos.x * m_DrawMiniMap->getScale().x + m_DrawMiniMap->getPosition().x, m_rectPos.y * m_DrawMiniMap->getScale().y + m_DrawMiniMap->getPosition().y);
	//	//printf("%d %d %d %d\n", m_rectPos.x, m_rectPos.y, m_rectSize.x, m_rectSize.y);

	//}
	//else m_InRoom = false;
}

void MiniMap::Render(sf::RenderWindow* window)
{
	window->draw(*m_DrawMiniMap);
	if (m_InRoom) window->draw(*m_DrawCurrentPos);
}
