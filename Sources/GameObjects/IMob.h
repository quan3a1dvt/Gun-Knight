#pragma once

#include "IMState.h"
#include "HitBox.h"


class IMob {
public:
	virtual void ChangeNextState(IMState::STATE nextState) = 0;
	virtual void Init() = 0;
	virtual void Update(float deltaTime) = 0;
	virtual void Render(sf::RenderWindow* window) = 0;
	virtual void PerformAIMovement(float deltaTime) = 0;
	virtual void Spawn() = 0;
	HitBox* getHitBox();
	sf::Vector2f getScale();
	bool getCW();
	void setCW(bool cw);
	virtual void LoseHP(int hplose) = 0;
	void SetCanMove(bool canmove);
	virtual bool CheckAttackedByMelee() = 0;
	void setActive(bool active);
	bool getActive();
	int getDamage();
	virtual Animation* getSprite() = 0;
	virtual sf::Shader* getShader() = 0;
	void setOnFire(int damage);
protected:
	int m_damage;

	sf::Vector2i m_SpawnPos;
		
	HitBox* m_HitBox;
	
	sf::Vector2f m_scale;
	
	bool m_cw;
	sf::Vector2i m_Hp;
	bool m_canMove;
	bool m_Active;
	
};