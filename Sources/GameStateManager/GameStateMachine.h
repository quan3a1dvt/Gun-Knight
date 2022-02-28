#pragma once
#include "../GameManager/Singleton.h"
#include <iostream>
#include <list>
using namespace std;

class GameStateBase;

enum StateTypes
{
	STATE_INVALID = 0,
	STATE_INTRO,
	STATE_MENU,
	STATE_LOBBY,
	STATE_PLAY,
	STATE_PAUSE,
	STATE_SETTING,
	STATE_END,
};
#define	GSMC GameStateMachine::GetInstance()
class GameStateMachine :public CSingleton<GameStateMachine> {
public:
	GameStateMachine();
	~GameStateMachine();

	void ChangeState(GameStateBase* state);
	void ChangeState(StateTypes st);
	void PushState(StateTypes st);
	void PopState();

	void PerformStateChange();

	GameStateBase* currentState() const;
	GameStateBase* nextState() const;
	bool NeedToChangeState();
	bool HasState();

private:
	list < GameStateBase*>	m_StateStack;
	GameStateBase* m_ActiveState;
	GameStateBase* m_NextState;
};