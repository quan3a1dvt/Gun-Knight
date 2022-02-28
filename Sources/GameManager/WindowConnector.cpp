#include "WindowConnector.h"

WindowConnector::WindowConnector()
{
    m_Window = nullptr;
}

void WindowConnector::setWindow(sf::RenderWindow* window)
{
    m_Window = window;
}

sf::RenderWindow* WindowConnector::getWindow()
{
    return m_Window;
}