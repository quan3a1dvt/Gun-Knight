#pragma once

#include "IPState.h"
#include "HitBox.h"

class WPSword;
class WPGun;
class IPlayer {
public:
	virtual void ChangeNextState(IPState::STATE nextState) = 0;
	virtual void Init() = 0;
	virtual void Update(float deltaTime) = 0;
	virtual void Render(sf::RenderWindow* window) = 0;
	virtual HitBox* getHitBox() = 0;
	virtual void LoseHp(int hp) = 0;
	virtual void LoseArmor(int armor) = 0;
	virtual sf::Vector2i getHp() = 0;
	virtual sf::Vector2i getArmor() = 0;
	virtual sf::Vector2f getScale() = 0;
	virtual bool getCW() = 0;
	virtual void setCW(bool cw) = 0;
	virtual WPSword* GetMeleeWP() = 0;
	virtual void Move(float movex, float movey) = 0;
	virtual void setActive(bool active) = 0;
	virtual bool getActive() = 0;
	virtual WPGun* getCurrentWP() = 0;
	virtual int getCoin() = 0;
	virtual void addCoin(int coin) = 0;
	virtual sf::Vector2i getExp() = 0;
	virtual void addExp(int exp) = 0;
	virtual void setExp(int exp) = 0;
	virtual int getLevel() = 0;
	virtual bool getHurt() = 0;
protected:
	
};