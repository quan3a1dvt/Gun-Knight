#pragma once
#include "SFML/Graphics.hpp"
#include "../GameManager/Singleton.h"

#define WConnect WindowConnector::GetInstance()

class WindowConnector :public CSingleton<WindowConnector> {
public:
	WindowConnector();
	void setWindow(sf::RenderWindow* window);
	sf::RenderWindow* getWindow();
private:
	sf::RenderWindow* m_Window;
};