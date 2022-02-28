#include "GSSetting.h"

GSSetting::GSSetting()
{
}

GSSetting::~GSSetting()
{
}

void GSSetting::Exit()
{
}

void GSSetting::Pause()
{
}

void GSSetting::Resume()
{
}

void GSSetting::Init()
{
	GameButton* button;

	// Return Button
	button = new GameButton();
	button->Init("close");
	button->setOnClick([]() {GSMC->PopState(); });
	button->setSize(sf::Vector2f(100, 100));
	button->setPosition(screenWidth - screenWidth / 16, screenHeight / 13);
	button->setOrigin(button->getSize() / 2.f);
	m_listButton.push_back(button);

	//Background
	//sf::Texture* texture = ASSET->getTexture("Background layers/Background");
	//m_background.setTexture(*texture);
	//m_background.setPosition(screenWidth / 2, screenHeight / 2);
	//m_background.setOrigin((sf::Vector2f)texture->getSize() / 2.f);

	//Title
	m_title.setString("SETTING");
	m_title.setFont(*ASSET->getFont("EvilEmpire-4BBVK"));
	m_title.setPosition(screenWidth / 2, screenHeight / 10);
	m_title.setFillColor(sf::Color(156, 227, 186));
	m_title.setCharacterSize(200.0f);
	m_title.setOrigin(m_title.getLocalBounds().left + m_title.getLocalBounds().width / 2.0f, m_title.getLocalBounds().top + m_title.getLocalBounds().height / 2.0f);

}

void GSSetting::Update(float deltaTime)
{
	for (auto button : m_listButton) {
		button->Update(deltaTime);
	}
}

void GSSetting::Render(sf::RenderWindow* window)
{
	window->draw(m_background);
	window->draw(m_title);
	for (auto button : m_listButton) {
		button->Render(window);
	}
}
