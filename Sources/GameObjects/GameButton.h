#pragma once
#include "../GameManager/WindowConnector.h"
#include "../GameManager/ResourceManager.h"
class GameButton : public sf::RectangleShape {
public:
	GameButton();
	~GameButton();

	void Init(std::string name);
	void Update(float deltaTime);
	void Render(sf::RenderWindow* window);

	void HandleTouchEvent();
	bool isHandle();

	void setOnClick(void (*Func)());
private:
	void (*m_bottonClickFunc)();
	bool m_isHandling;
	float m_CurrentTime;
	float m_TimeRelease;
	std::string m_path;
};