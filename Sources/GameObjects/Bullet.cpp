#include "Bullet.h"
#include "Tile.h"
#include "IMob.h"
#include "IPlayer.h"
Bullet::Bullet()
{
	m_Bullet = new Animation;
	m_HitBox = new HitBox;
	m_HitCircle = new HitCircle;
	m_Active = false;
	m_Hit = false;
}

Bullet::~Bullet()
{
}

void Bullet::Init()
{
	m_HitBox->Init(0.f);
	m_HitBox->setPosition(sf::Vector2f(0.f, 0.f));
	m_HitCircle->Init(0.f);
	m_HitCircle->setPosition(sf::Vector2f(0.f, 0.f));
	m_Active = false;
}

void Bullet::Update(float deltaTime)
{
	if (m_Active) {
		switch (m_Type)
		{
		case BULLET_DEFAULT:
			break;
		case BULLET_ROUND1:
		{
			
			if (m_Hit == false) m_Bullet->Update(deltaTime);
			else {
				if (m_Bullet->Play(deltaTime)) {
					m_Active = false;
				}
			}		
			if (m_Hit == false) {
				float x;
				float y;
				//printf("%f %d\n", m_Degree, m_Quadrant);
				if (m_Degree == 90.f) x = 0.f;
				else x = ((m_Quadrant == 1 || m_Quadrant == 4) ? 1 : -1) * cos(m_Degree * 0.0174532925);
				if (m_Degree == 0.f) y = 0.f;
				else y = ((m_Quadrant == 3 || m_Quadrant == 4) ? 1 : -1) * sin(m_Degree * 0.0174532925);
				m_HitCircle->move(x * m_HitCircle->GetVelocity() * deltaTime, y * m_HitCircle->GetVelocity() * deltaTime);
				m_Bullet->setPosition(m_HitCircle->getPosition());
				Collision();
			}
			
			break;
		}
		case BULLET_ROUND2:
		{
			m_waitTime += deltaTime;
			if (m_Hit == false) m_Bullet->Update(deltaTime);
			else {
				if (m_Bullet->Play(deltaTime)) {
					m_Active = false;
				}
			}	
			if (m_Hit == false) {
				if (m_waitTime >= 0.4f) {
					//printf("%f %d\n", m_Degree, m_Quadrant);
					m_HitCircle->move((m_HitCircle->getPosition().x < GConnect->getPlayer()->getHitBox()->getPosition().x ? 1 : -1) * m_HitCircle->GetVelocity() * deltaTime,
						(m_HitCircle->getPosition().y < GConnect->getPlayer()->getHitBox()->getPosition().y ? 1 : -1) * m_HitCircle->GetVelocity() * deltaTime);
					m_Bullet->setPosition(m_HitCircle->getPosition());
					Collision();
				}
				else {
					float x;
					float y;
					//printf("%f %d\n", m_Degree, m_Quadrant);
					if (m_Degree == 90.f) x = 0.f;
					else x = ((m_Quadrant == 1 || m_Quadrant == 4) ? 1 : -1) * cos(m_Degree * 0.0174532925);
					if (m_Degree == 0.f) y = 0.f;
					else y = ((m_Quadrant == 3 || m_Quadrant == 4) ? 1 : -1) * sin(m_Degree * 0.0174532925);
					m_HitCircle->move(x * m_HitCircle->GetVelocity() * deltaTime, y * m_HitCircle->GetVelocity() * deltaTime);
					m_Bullet->setPosition(m_HitCircle->getPosition());
					Collision();
				}
				
			}

			break;
		}
		case BULLET_RECT1:
			break;
		default:
			break;
		}		
	}
}

void Bullet::Render(sf::RenderWindow* window)
{
	if (m_Active) {
		switch (m_Type)
		{
		case BULLET_DEFAULT:
			break;
		case BULLET_ROUND1:
		{
			window->draw(*m_Bullet);
			window->draw(*m_HitCircle);
			break;
		}
		case BULLET_ROUND2:
		{
			window->draw(*m_Bullet);
			window->draw(*m_HitCircle);
			break;
		}
		case BULLET_RECT1:
			break;
		default:
			break;
		}
	}	
}

void Bullet::Create(BulletType type, string tex, sf::Vector2f pos, sf::Vector2f size, bool fromPlayer, int damage, vector<float> data)
{
	m_Type = type;
	m_Pos = pos;
	m_fromPlayer = fromPlayer;
	string locate = "Bullet/" + tex;
	m_Damage = damage;
	m_Data = data;
	switch (m_Type)
	{
	case BULLET_DEFAULT:
		break;
	case BULLET_ROUND1:
	{
		m_isRect = false;	
		m_Bullet->Reset(*ASSET->getTexture(locate), sf::Vector2i(1, 1), 0.01f);
		m_Scale = sf::Vector2f(size.x / m_Bullet->getTextureRect().width, size.y / m_Bullet->getTextureRect().height);
		m_Bullet->setScale(m_Scale);
		m_HitCircle->setRadius(m_Bullet->getTexture()->getSize().x * m_Scale.x/ 2.f);
		m_HitCircle->setOrigin(m_HitCircle->getRadius(), m_HitCircle->getRadius());
		m_HitCircle->setPosition(pos);
		m_HitCircle->setFillColor(sf::Color(0, 0, 0, 0));
		m_HitCircle->setOutlineThickness(1.0f);
		m_HitCircle->setOutlineColor(sf::Color::Red);
		if (data[0] != -1) m_HitCircle->Init(data[0]);
		else m_HitCircle->Init(100.f);
		if (data[1] != -1) SetDirection(data[1]);	
		else SetDirection(0);
		m_Active = true;
		m_Hit = false;
		break;
	}
	case BULLET_ROUND2:
	{
		m_isRect = false;
		m_Bullet->Reset(*ASSET->getTexture(locate), sf::Vector2i(1, 1), 0.01f);
		m_Scale = sf::Vector2f(size.x / m_Bullet->getTextureRect().width, size.y / m_Bullet->getTextureRect().height);
		m_Bullet->setScale(m_Scale);
		m_HitCircle->setRadius(m_Bullet->getTexture()->getSize().x * m_Scale.x / 2.f);
		m_HitCircle->setOrigin(m_HitCircle->getRadius(), m_HitCircle->getRadius());
		m_HitCircle->setPosition(pos);
		m_HitCircle->setFillColor(sf::Color(0, 0, 0, 0));
		m_HitCircle->setOutlineThickness(1.0f);
		m_HitCircle->setOutlineColor(sf::Color::Red);
		if (data[0] != -1) m_HitCircle->Init(data[0]);
		else m_HitCircle->Init(100.f);
		if (data[1] != -1) SetDirection(data[1]);
		else SetDirection(0);
		m_Active = true;
		m_Hit = false;
		m_waitTime = 0.f;
		break;
	}
	case BULLET_RECT1:
		break;
	case BULLET_RECT2:
	{
		m_isRect = false;
		m_Bullet->Reset(*ASSET->getTexture(locate), sf::Vector2i(1, 1), 0.01f);
		m_Scale = sf::Vector2f(size.x / m_Bullet->getTextureRect().width, size.y / m_Bullet->getTextureRect().height);
		m_Bullet->setScale(m_Scale);
		
		m_HitBox->setOrigin(m_HitBox->getSize().x / 2, m_HitBox->getSize().y / 2);
		m_HitBox->setPosition(pos);
		m_HitBox->setFillColor(sf::Color(0, 0, 0, 0));
		m_HitBox->setOutlineThickness(1.0f);
		m_HitBox->setOutlineColor(sf::Color::Red);
		if (data[0] != -1) m_HitBox->Init(data[0]);
		else m_HitBox->Init(100.f);
		if (data[1] != -1) SetDirection(data[1]);
		else SetDirection(0);
		m_Active = true;
		m_Hit = false;
		m_waitTime = 0.f;
		break;
	}
	default:
		break;
	}


}



void Bullet::SetDirection(float degree)
{
	float Degree = degree;
	if (Degree < 0.f) {
		Degree += 360.f;
	}
	else if (Degree >= 360.f) {
		Degree -= 360.f;
	}
	//printf("%f\n", degree);
	if (Degree >= 0.f && Degree < 90.f) {
		m_Quadrant = 1;
		m_Degree = Degree;
	}
	else if (Degree >= 90.f && Degree < 180.f) {
		m_Quadrant = 2;
		m_Degree = 180.f - Degree;
	}
	else if (Degree >= 180.f && Degree < 270.f) {
		m_Quadrant = 3;
		m_Degree = Degree - 180.f;
	}
	else if (Degree >= 270.f && Degree < 360.f) {
		m_Quadrant = 4;
		m_Degree = 360.f - Degree;
	}
}

bool Bullet::getActive()
{
	return m_Active;
}

void Bullet::setActive(bool active)
{
	m_Active = active;
}

void Bullet::Collision()
{
	int startx, starty;
	int endx, endy;
	if (m_isRect) {
		startx = (m_HitBox->getPosition().x - max(m_HitBox->getSize().x * m_HitBox->getScale().x / 2, m_HitBox->getSize().y * m_HitBox->getScale().y / 2)) / TileSize;
		starty = (m_HitBox->getPosition().y - max(m_HitBox->getSize().x * m_HitBox->getScale().x / 2, m_HitBox->getSize().y * m_HitBox->getScale().y / 2)) / TileSize;
		endx = (m_HitBox->getPosition().x + max(m_HitBox->getSize().x * m_HitBox->getScale().x / 2, m_HitBox->getSize().y * m_HitBox->getScale().y / 2)) / TileSize;
		endy = (m_HitBox->getPosition().y + max(m_HitBox->getSize().x * m_HitBox->getScale().x / 2, m_HitBox->getSize().y * m_HitBox->getScale().y / 2)) / TileSize;
	}
	else {
		startx = (m_HitCircle->getPosition().x - m_HitCircle->getRadius()) / TileSize;
		starty = (m_HitCircle->getPosition().y - m_HitCircle->getRadius()) / TileSize;
		endx = (m_HitCircle->getPosition().x + m_HitCircle->getRadius()) / TileSize;
		endy = (m_HitCircle->getPosition().y + m_HitCircle->getRadius()) / TileSize;
	}
	FOR(i, starty, endy) {
		FOR(j, startx, endx) {
			if ((*GConnect->getTiles())[i][j]->getType() != TileType::TILE_FLOOR) {
				if ((m_isRect == false && Collision::BoundingBoxTest(m_HitCircle, (*GConnect->getTiles())[i][j])) || (m_isRect == true && Collision::BoundingBoxTest(m_HitBox, (*GConnect->getTiles())[i][j]))) {
					m_Bullet->Reset(*ASSET->getTexture("Bullet/explosion_1"), sf::Vector2i(8, 1), 0.05f);
					m_Hit = true;
					break;
				}
			}
			
		}
	}
	if (m_Active) {
		if (m_fromPlayer) {
			for (IMob* i : *GConnect->getMobs()) {
				if (i->getActive()) {
					if (Collision::BoundingBoxTest(m_HitCircle, i->getHitBox())) {
						i->LoseHP(m_Damage);
						m_Bullet->Reset(*ASSET->getTexture("Bullet/explosion_1"), sf::Vector2i(8, 1), 0.05f);
						m_Hit = true;
						
						break;
					}

				}
			}
		}
		else {
			if (Collision::BoundingBoxTest(m_HitCircle, GConnect->getPlayer()->getHitBox())) {
				m_Bullet->Reset(*ASSET->getTexture("Bullet/explosion_1"), sf::Vector2i(8, 1), 0.05f);
				GConnect->getPlayer()->LoseHp(m_Damage);
				m_Hit = true;
			}
		}
	}
	
}

