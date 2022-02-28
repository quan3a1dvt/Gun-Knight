#pragma once

#include "IMob.h"
#include "HitBox.h"
#include "WPSword.h"
class Imp : public IMob {
public:
	Imp();
	~Imp();
	void ChangeNextState(IMState::STATE nextState);

	void Init();
	void Update(float deltaTime);
	void Render(sf::RenderWindow* window);
	bool CheckAttackedByMelee();
	void PerformAIMovement(float deltaTime);
	void Spawn();
	void Move(float movex, float movey);
	void LoseHP(int hp);
	bool getShowShader();
	Animation* getSprite();
	sf::Shader* getShader();
protected:
	void PerformStateChange();

	IMState::STATE m_nextState;
	IMState* m_currentState;
	IMState* m_spawnState;
	IMState* m_idleState;
	IMState* m_runState;
	IMState* m_attackState;
	IMState* m_deathState;
	
	sf::Vector2f m_destination;
	
	bool m_stop;

	bool m_isRest;
	float m_distPlayer;
	int m_choosedMoveWay;
	float m_followTime;
	float m_followTimeLimit;
	float m_waitTime;
	float m_canAttack;
	
	sf::Text m_HitNumber;
	int m_HitNumberVal;
	bool m_ShowHitNumber;
	float m_waitHitNumber;
	float m_currentHitNumberTime;

	int randValue;
	float movex;
	float movey;

	bool m_ShowShader;
	float m_waitShader;
	float m_currentShaderTime;
	sf::Shader* m_Shader;

	HitBox* m_AttackHitBox;
};