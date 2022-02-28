#pragma once
#include "../GameManager/ResourceManager.h"
#include "HitBox.h"
#include "HitCircle.h"

class IMob;
enum BulletType {
	BULLET_DEFAULT = 0,
	BULLET_ROUND1,
	BULLET_ROUND2,
	BULLET_RECT1,
	BULLET_RECT2,
};
class Bullet {
public:
	
	Bullet();
	~Bullet();
	void Init();
	void Update(float deltaTime);
	void Render(sf::RenderWindow* window);
	void Create(BulletType type, string tex, sf::Vector2f pos, sf::Vector2f size, bool fromPlayer, int damage, vector<float> data);
	void SetDirection(float degree);
	bool getActive();
	void setActive(bool active);
	void Collision();
protected:
	BulletType m_Type;
	sf::Vector2f m_Scale;
	sf::Vector2f m_Pos;
	vector<IMob*> m_HitMob;
	HitBox* m_HitBox;
	HitCircle* m_HitCircle;
	Animation* m_Bullet;
	int m_Damage;
	vector<float> m_Data;
	float m_waitTime;
	bool m_fromPlayer;
	bool m_isRect;
	bool m_Active;
	int m_Quadrant;
	float m_Degree;
	sf::Vector2i m_BoxPos;
	bool m_Hit;

	
	
};