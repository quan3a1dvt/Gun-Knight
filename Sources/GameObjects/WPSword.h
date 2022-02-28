#pragma once
#include "Weapon.h"
#include "HitBox.h"
#include "IPlayer.h"

class IMob;

class WPSword :public Weapon {
public:
	WPSword(IPlayer* Player);
	~WPSword();
	void Init();
	void Update(float deltaTime);
	void Render(sf::RenderWindow* window);
	float GetDamage();
	void Attack(float deltaTime);
	bool isAttacking();
	void PerformAttackAnimation(float deltaTime);
	vector<IMob*>* GetHitMob();
	void AddHitMob(IMob* mob);
	HitBox* getHitBox();
	
protected:
	IPlayer* m_Player;
	HitBox* m_HitBox;
	sf::Sprite* m_weapon;

	float m_damage;

	bool m_isAttacking;
	float m_currentTime;
	float m_attackTime;
	float m_waitTime;

	vector<IMob*>* m_hitMob;
};