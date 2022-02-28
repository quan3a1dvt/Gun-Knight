#include "Shoot.h"

Shoot::Shoot()
{
	m_Type = SHOOT_DEFAULT;
}

Shoot::~Shoot()
{
}

void Shoot::Init()
{
}

void Shoot::Update(float deltaTime)
{
	switch (m_Type)
	{
	case SHOOT_1:
		break;
	case SHOOT_2:
		break;
	case SHOOT_3:
		break;
	case SHOOT_4:
		break;
	case SHOOT_DEFAULT:
		break;
	default:
		break;
	}
}

void Shoot::Render(sf::RenderWindow* window)
{
	switch (m_Type)
	{
	case SHOOT_1:
		break;
	case SHOOT_2:
		break;
	case SHOOT_3:
		break;
	case SHOOT_4:
		break;
	case SHOOT_DEFAULT:
		break;
	default:
		break;
	}
}

void Shoot::Create(ShootType type, BulletType btype, string tex, sf::Vector2f pos, sf::Vector2f size, bool fromPlayer, int damage, vector<float> data)
{
	//for (Bullet* i : m_Bullets) i->setActive(false);
	m_Type = type;
	m_Pos = pos;
	//m_Bullets.clear();
	switch (m_Type)
	{
	case SHOOT_1:
	{
		// 0: velocity, 1: bullet_num 2:recoil,
		m_Active = true;
		float velocity = data[0];
		int bulletnum = (int)data[1];
		int currentbullet = 1;
		vector<float> temp(3, -1);
		temp[0] = velocity;
		for(Bullet* i:*(GConnect->getBullets())) {
			if (i->getActive() == false) {
				temp[1] = currentbullet * (360.f / bulletnum) - (360.f / bulletnum) / 2;
				temp[1] = temp[1] + (random::random(0, 1) == 0 ? 1 : -1) * random::random(0, (int)data[2]);
				i->Create(btype, tex, pos, size, fromPlayer, damage, temp);
				currentbullet++;
				if (currentbullet > bulletnum) break;
			}
		}
		m_Active = false;
		break;
	}
	case SHOOT_2:
	{
		// 0: velocity, 1: degree, 2: recoil
		m_Active = true;
		vector<float> temp(3, -1);
		temp[0] = data[0];
		temp[1] = data[1] + random::random(-(int)data[2], (int)data[2]);
		for (Bullet* i : *(GConnect->getBullets())) {
			if (i->getActive() == false) {
				i->Create(btype, tex, pos, size, fromPlayer, damage, temp);
				break;
			}
		}
		m_Active = false;
		break;
	}
	case SHOOT_3:
	{
		// 0: velocity, 1: bullet_num, 2: degree, 3: degree per b,  4:recoil,
		m_Active = true;
		float velocity = data[0];
		int bulletnum = (int)data[1];
		int currentbullet = -bulletnum / 2;
		vector<float> temp(2, -1);
		temp[0] = velocity;
		for (Bullet* i : *(GConnect->getBullets())) {
			if (i->getActive() == false) {
				if (currentbullet == 0 && bulletnum % 2 == 0) {
					currentbullet++;
					continue;
				}
				temp[1] = data[2] + currentbullet * data[3];
				temp[1] = temp[1] + (random::random(0, 1) == 0 ? 1 : -1) * random::random(0, (int)data[4]);
				i->Create(btype, tex, pos, size, fromPlayer, damage, temp);
				currentbullet++;
				if (currentbullet > bulletnum/2) break;
			}
		}
		m_Active = false;
		break;
	}

	case SHOOT_DEFAULT:
		break;
	default:
		break;
	}
}

bool Shoot::getActive()
{
	return m_Active;
}

void Shoot::setActive(bool active)
{
	m_Active = active;
}
