#pragma once
#include "Bullet.h"
enum ShootType {
	SHOOT_DEFAULT = 0,
	SHOOT_1,
	SHOOT_2,
	SHOOT_3,
	SHOOT_4,
};
class Shoot { 
public:
	
	Shoot();
	~Shoot();
	void Init();
	void Update(float deltaTime);
	void Render(sf::RenderWindow* window);
	void Create(ShootType type, BulletType btype, string tex, sf::Vector2f pos, sf::Vector2f size, bool fromPlayer, int damage, vector<float> data);
	bool getActive();
	void setActive(bool active);
protected:
	sf::Vector2f m_Pos;
	vector<Bullet*> m_Bullets;
	ShootType m_Type;
	bool m_Active;
};