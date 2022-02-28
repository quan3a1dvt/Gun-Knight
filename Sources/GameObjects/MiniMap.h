#pragma once
#include "../GameManager/ResourceManager.h"

class MiniMap {
public:
	MiniMap();
	~MiniMap();
	void Init(string locate);
	void Update(float deltaTime, sf::Vector2i CurrentPos);
	void Render(sf::RenderWindow* window);
protected:
	sf::Sprite* m_DrawMiniMap;
	sf::RectangleShape* m_DrawCurrentPos;

	bool m_InRoom;

	sf::IntRect m_IntRect;
	sf::Vector2i m_rectPos;
	sf::Vector2i m_rectSize;

	sf::Vector2i m_CurrentPos;
};