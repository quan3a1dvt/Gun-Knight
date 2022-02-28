#include "Game.h"
#include "GameStateManager/GameStateBase.h"

Game::~Game()
{
    if (m_window != nullptr) delete m_window;
}

void Game::Init()
{
    m_window = new sf::RenderWindow(sf::VideoMode(screenWidth, screenHeight), "Gun Knight" , sf::Style::Close);
    m_window->setFramerateLimit(144);
    m_window->setVerticalSyncEnabled(false);
    GameStateMachine::GetInstance()->ChangeState(StateTypes::STATE_INTRO);
    WConnect->setWindow(m_window);
    srand(time(NULL));
}

void Game::Run()
{
    Init();
    sf::Clock clock;
    float deltaTime = 0.f;
    while (m_window->isOpen()) {
        deltaTime = clock.restart().asSeconds();
        sf::Event event;
        while (m_window->pollEvent(event)) {
            if (event.type == sf::Event::EventType::Closed)
                m_window->close();
        }
        Update(deltaTime);
        Render();
    }
}

void Game::Update(float deltaTime)
{
    //printf("%f\n", 1.f / deltaTime);
    if (GameStateMachine::GetInstance()->NeedToChangeState()) {
        GameStateMachine::GetInstance()->PerformStateChange();
    }
    GameStateMachine::GetInstance()->currentState()->Update(deltaTime);
    
}

void Game::Render()
{
    m_window->clear();
    GameStateMachine::GetInstance()->currentState()->Render(m_window);
    m_window->display();
}
