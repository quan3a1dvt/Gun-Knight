#include "GameStateMachine.h"
#include "GameStateBase.h"

GameStateMachine::GameStateMachine()
{
    m_ActiveState = nullptr;
    m_NextState = nullptr;
}

GameStateMachine::~GameStateMachine()
{
    while (!m_StateStack.empty()) {
        delete m_StateStack.back();
        m_StateStack.pop_back();
    }
}

void GameStateMachine::ChangeState(GameStateBase* state)
{
    m_NextState = state;
}

void GameStateMachine::ChangeState(StateTypes st)
{
    GameStateBase* gs = GameStateBase::CreateState(st);
    ChangeState(gs);
}

void GameStateMachine::PushState(StateTypes st)
{
    GameStateBase* gs = GameStateBase::CreateState(st);
    if (!m_StateStack.empty()) {
        m_StateStack.back()->Pause();
    }
    m_NextState = gs;
}

void GameStateMachine::PopState()
{
    // cleanup the current state
    if (!m_StateStack.empty()) {
        m_StateStack.back()->Exit();
        m_StateStack.pop_back();
    }

    // resume previous state
    if (!m_StateStack.empty()) {
        m_StateStack.back()->Resume();
    }
    m_ActiveState = m_StateStack.back();
}

void GameStateMachine::PerformStateChange()
{
    if (m_NextState != nullptr) {
        if (!m_StateStack.empty()) {
            m_StateStack.back()->Exit();
        }
        m_StateStack.push_back(m_NextState);
        m_StateStack.back()->Init();
        m_ActiveState = m_NextState;
    }
    m_NextState = nullptr;
}

GameStateBase* GameStateMachine::currentState() const
{
    return m_ActiveState;
}

GameStateBase* GameStateMachine::nextState() const
{
    return m_NextState;
}

bool GameStateMachine::NeedToChangeState()
{
    return m_NextState != nullptr;
}

bool GameStateMachine::HasState()
{
    return m_StateStack.size() > 0;
}
