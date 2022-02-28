#include "GSPlay.h"

GSPlay::GSPlay()
{
	

	/*GameConnector();

	CoinsManager();
	ExpsManager();
	TiledMap();*/
	m_Player = new Player;
	GConnect->setPlayer(m_Player);
	/*WavesManager();
	MobsManager();
	BulletsManager();
	
	UI();*/

	m_pView = new sf::View;
	
}

GSPlay::~GSPlay()
{
}

void GSPlay::Exit()
{
}

void GSPlay::Pause()
{
	
}

void GSPlay::Resume()
{
	WConnect->getWindow()->setMouseCursorVisible(false);
}

void GSPlay::Init()
{
	CManager->Init();
	EManager->Init();
	m_Player->Init();
	TM->Init();
	//TM->ChangeMap();
	
	MManager->Init();
	BManager->Init();
	WManager->Init();
	
	GUI->Init();

	m_Cursor.setTexture(*ASSET->getTexture("Cursor"));
	m_Cursor.setOrigin(m_Cursor.getTexture()->getSize().x / 2, m_Cursor.getTexture()->getSize().y / 2);
	m_Cursor.setScale(20.f / m_Cursor.getTexture()->getSize().x, 20.f / m_Cursor.getTexture()->getSize().y);
	m_Cursor.setColor(sf::Color(255, 0, 0));
	WConnect->getWindow()->setMouseCursorVisible(false);

	GConnect->setView(m_pView);
	m_pView->setSize(screenWidth, screenHeight);

	sf::Vector2f PauseScale(1.f, 1.f);
	sf::Vector2f PauseFrameSize(400.f, 400.f);
	m_PauseFrame.setTexture(*ASSET->getTexture("Button/PauseFrame"));
	m_PauseFrame.setOrigin(m_PauseFrame.getTexture()->getSize().y / 2, m_PauseFrame.getTexture()->getSize().y / 2);
	m_PauseFrame.setScale(PauseScale.x * PauseFrameSize.x / m_PauseFrame.getTexture()->getSize().x, PauseScale.y * PauseFrameSize.y / m_PauseFrame.getTexture()->getSize().y);
	m_PauseFrame.setPosition(screenWidth / 2, screenHeight / 2);

	sf::Sprite* sprite;
	string Title[5] = { "P","A","U","S","E" };
	FOR(i, 0, 4) {
		sprite = new sf::Sprite;
		sprite->setTexture(*ASSET->getTexture("Button/" + Title[i]));
		sprite->setOrigin(sprite->getTexture()->getSize().x / 2.f, sprite->getTexture()->getSize().y / 2.f);
		sprite->setScale(150.f * PauseScale.x / sprite->getTexture()->getSize().x, 150.f * PauseScale.y / sprite->getTexture()->getSize().y);
		sprite->setPosition(m_PauseFrame.getPosition().x - (2 - i) * 70.f * PauseScale.x, m_PauseFrame.getPosition().y - PauseFrameSize.y * PauseScale.y / 5);
		m_PauseTitle.push_back(sprite);
	}

	GameButton* button;

	//Enter Lobby Button
	button = new GameButton();
	button->Init("lobby");
	button->setOnClick([]() {GSMC->PopState();});
	button->setSize(sf::Vector2f(80 * PauseScale.x, 80 * PauseScale.y));
	button->setOrigin(button->getSize() / 2.f);
	button->setPosition(m_PauseFrame.getPosition().x - PauseFrameSize.x * PauseScale.x / 6, m_PauseFrame.getPosition().y + PauseFrameSize.y * PauseScale.y / 4);
	m_listButton.push_back(button);

	//Setting Button
	button = new GameButton();
	button->Init("setting");
	button->setOnClick([]() {GSMC->PushState(StateTypes::STATE_SETTING); });
	button->setSize(sf::Vector2f(80 * PauseScale.x, 80 * PauseScale.y));
	button->setOrigin(button->getSize() / 2.f);
	button->setPosition(m_PauseFrame.getPosition().x + PauseFrameSize.x * PauseScale.x / 6, m_PauseFrame.getPosition().y + PauseFrameSize.y * PauseScale.y / 4);
	m_listButton.push_back(button);



	m_waitPause = 0.2f;
	m_currentPauseTime = 0.f;
	m_canPause = true;

	m_Active = true;

	m_Res.setFont(*ASSET->getFont("EvilEmpire-4BBVK"));
	
	m_Res.setFillColor(sf::Color::White);
	
	m_Res.setOutlineThickness(1.f);
	//m_Res.setOrigin(m_PriceText.getLocalBounds().left + m_PriceText.getLocalBounds().width / 2.0f, m_PriceText.getLocalBounds().top + m_PriceText.getLocalBounds().height / 2.0f);
	
}

void GSPlay::Update(float deltaTime)
{
	if (m_Active) {
		
		m_currentPauseTime += deltaTime;
		if (m_currentPauseTime >= m_waitPause) {
			m_canPause = true;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::P) && m_canPause) {
			m_currentPauseTime = 0.f;
			m_canPause = false;
			m_Active = false;
			WConnect->getWindow()->setMouseCursorVisible(true);
		}
		//printf("%f\n", sf::Mouse::getPosition(*WConnect->getWindow()).x + m_Player->getHitBox()->getPosition().x - screenWidth / 2.f);
		TM->Update(deltaTime);
		m_Player->Update(deltaTime);

		MManager->Update(deltaTime);
		WManager->Update(deltaTime);
		BManager->Update(deltaTime);
		CManager->Update(deltaTime);
		EManager->Update(deltaTime);
		m_Res.setString(to_string(TM->m_getRes().x) + " - " + to_string(TM->m_getRes().y));
		m_Res.setCharacterSize(50.f);
		m_Res.setPosition(screenWidth / 2, 0.f);
		
		m_Cursor.setPosition(sf::Mouse::getPosition(*WConnect->getWindow()).x + m_Player->getHitBox()->getPosition().x - screenWidth / 2, sf::Mouse::getPosition(*WConnect->getWindow()).y + m_Player->getHitBox()->getPosition().y - screenHeight / 2);
		m_pView->setCenter(m_Player->getHitBox()->getPosition());
		GUI->Update(deltaTime);
		WConnect->getWindow()->setMouseCursorVisible(false);
		
		//if (m_Player->getHp().x <= 0) GameStateMachine::GetInstance()->PopState();

	}
	else {
		m_currentPauseTime += deltaTime;
		WConnect->getWindow()->setMouseCursorVisible(true);
		if (m_currentPauseTime >= m_waitPause) {
			m_canPause = true;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::P) && m_canPause) {
			m_currentPauseTime = 0.f;
			m_canPause = false;
			m_Active = true;
			WConnect->getWindow()->setMouseCursorVisible(false);
		}
		for (auto button : m_listButton) {
			button->Update(deltaTime);
		}
		
	}
}

void GSPlay::Render(sf::RenderWindow* window)
{
	window->setView(*m_pView);
	
	TM->Render(window);
	//m_Player->Render(window);
	MManager->Render(window);
	WManager->Render(window);
	BManager->Render(window);
	CManager->Render(window);
	EManager->Render(window);

	window->draw(m_Cursor);
	window->setView(window->getDefaultView());
	window->draw(m_Res);
	GUI->Render(window);
	window->setView(*m_pView);

	if (m_Active == false) {
		window->setView(window->getDefaultView());
		window->draw(m_PauseFrame);

		for (auto button : m_listButton) {
			button->Render(window);
		}
		printf("%d\n", m_PauseTitle.size());
		for (auto sprite : m_PauseTitle) {
			window->draw(*sprite);
		}
	}
}
