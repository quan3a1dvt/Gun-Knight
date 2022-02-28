#include "GameStateBase.h"
#include "GSIntro.h"
#include "GSMenu.h"
#include "GSLobby.h"
#include "GSPlay.h"
#include "GSGameplay.h"
#include "GSSetting.h"
#include "GSPause.h"
#include "GSEnd.h"

GameStateBase::GameStateBase()
{
}

GameStateBase::~GameStateBase()
{
}

GameStateBase* GameStateBase::CreateState(StateTypes st)
{
	GameStateBase* gs = nullptr;
	switch (st)
	{
	case STATE_INVALID:
		break;
	case STATE_INTRO:
		gs = new GSIntro();
		break;
	case STATE_MENU:
		gs = new GSMenu();
		break;
	case STATE_LOBBY:
		gs = new GSLobby();
		break;
	case STATE_PLAY:
		gs = new GSPlay();
		break;
	case STATE_PAUSE:
		gs = new GSPause();
		break;
	case STATE_SETTING:
		gs = new GSSetting();
		break;
	case STATE_END:
		gs = new GSEnd();
		break;
	default:
		break;
	}
	return gs;
}