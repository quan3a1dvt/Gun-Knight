#include "Player.h"
#include "PSRun.h"
#include "PSIdle.h"
#include "Room.h"
#include "Tile.h"
#include "Coin.h"
#include "Exp.h"
Player::Player()
{
	m_Scale = sf::Vector2f(4.f * GlobalScale.x, 4.f * GlobalScale.y);
	m_nextState = IPState::SNULL;
	m_runState = new PSRun(this);
	m_deathState;
	m_attackState;
	m_idleState = new PSIdle(this);
	m_currentState = m_idleState;
	m_wpSword = new WPSword(this);
	m_wpGuns.resize(3);
	FOR(i, 0, m_wpGuns.size() - 1) m_wpGuns[i] = new WPGun();
	

	m_HitBox = new HitBox(sf::Vector2i(9 * m_Scale.x, 13 * m_Scale.y));

	m_Tiles = GConnect->getTiles();
	m_TileBoxes = GConnect->getTileBoxes();

	m_RoomPos = GConnect->getRoomPos();

	m_Active = false;
	

}

Player::~Player()
{
	if (m_runState != nullptr) {
		delete m_runState;
	}
	if (m_idleState != nullptr) {
		delete m_idleState;
	}
	if (m_attackState != nullptr) {
		delete m_attackState;
	}
	if (m_deathState != nullptr) {
		delete m_deathState;
	}
	m_currentState = nullptr;

	/*if (m_wpSword != nullptr) {
		delete m_wpSword;
	}*/

	if (m_HitBox != nullptr) {
		delete m_HitBox;
	}
}

void Player::ChangeNextState(IPState::STATE nextState)
{
	m_nextState = nextState;
}

void Player::Init()
{
	m_runState->Init();
	m_idleState->Init();
	//m_deathState->Init();
	//m_attackState->Init();
	m_HitBox->setPosition(100.f, 100.f);
	m_HitBox->Init(600.f);

	//m_wpSword->Init();
	FOR(i, 0, m_wpGuns.size() - 1) m_wpGuns[i]->Init();
	m_currentGunSlot = 0;
	m_currentGunSlotCount = 3;
	m_maxGunSlotCount = 3;
	m_waitTime = 0.5f;
	m_wpGuns[m_currentGunSlot]->Create(GunType::GUN_PISTOL);
	m_wpGuns[1]->Create(GunType::GUN_SHOTGUN);
	m_wpGuns[2]->Create(GunType::GUN_SMG);

	m_cw = true;
	m_Hp = sf::Vector2i(20, 20);
	m_Armor = sf::Vector2i(20, 20);
	m_Coin = 1000;
	m_Exp = sf::Vector2i(0,100);
	m_Exp = GConnect->getPExp();
	m_Level = 1;

	m_Hurt = false;
	m_waitHurt = 2.0f;
	m_currentHurtTime = 0.f;

	m_ShowHurt = false;
	m_waitShowHurt = 0.2f;
	m_currentShowHurtTime = 0.f;
}

void Player::Update(float deltaTime)
{
	if (m_Active) {
		m_currentTime += deltaTime;
		PerformStateChange();
		m_currentState->Update(deltaTime);
		m_wpGuns[m_currentGunSlot]->Update(deltaTime);
		//printf("%f %f\n", m_HitBox->getPosition().x, m_HitBox->getPosition().y);


		//if ((*m_Rooms)[y][x]->getType() != RoomType::ROOM_DEFAULT)
		//m_wpSword->Update(deltaTime);
		/*if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			m_wpSword->Attack(deltaTime);
		}*/
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q) && m_currentTime >= m_waitTime) {
			m_currentTime = 0.f;
			if (m_currentGunSlot >= m_currentGunSlotCount - 1) {
				m_currentGunSlot = 0;
			}
			else m_currentGunSlot++;
		}

		m_currentHurtTime += deltaTime;
		if (m_currentHurtTime >= m_waitHurt + 0.8f) {
			m_currentHurtTime -= 0.8f;
			m_Armor.x = min(m_Armor.x + 1, m_Armor.y);
		}

		//m_currentHurtTime += deltaTime;
		//if (m_currentHurtTime >= m_waitHurt) {
		//	m_Hurt = false;
		//}
		//m_currentShowHurtTime += deltaTime;
		//if (m_currentShowHurtTime >= m_waitShowHurt) {
		//	m_currentShowHurtTime = 0.f;
		//	m_ShowHurt = not m_ShowHurt;
		//}
		
		FOR(i, 0, GConnect->getCoins()->size() - 1) {
			if (GConnect->getCoins()->at(i)->getActive() && Collision::BoundingBoxTest(GConnect->getCoins()->at(i)->getHitBox(), GConnect->getPlayer()->getHitBox())) {
				GConnect->getCoins()->at(i)->setActive(false);
				addCoin(GConnect->getCoins()->at(i)->getValue());
			}
		}

		FOR(i, 0, GConnect->getExps()->size() - 1) {
			if (GConnect->getExps()->at(i)->getActive() && Collision::BoundingBoxTest(GConnect->getExps()->at(i)->getHitBox(), GConnect->getPlayer()->getHitBox())) {
				GConnect->getExps()->at(i)->setActive(false);
				addExp(GConnect->getExps()->at(i)->getValue());
			}
		}
	}
	

}

void Player::Render(sf::RenderWindow* window)
{
	if (m_Active) {
		//if (!(m_Hurt && m_ShowHurt)) {
			m_currentState->Render(window);
			m_wpGuns[m_currentGunSlot]->Render(window);
		//}
		//m_wpSword->Render(window);
		
		//window->draw(*m_HitBox);
	}
	
}

bool Player::getCW()
{
	return m_cw;
}

void Player::setCW(bool cw)
{
	m_cw = cw;
}

WPSword* Player::GetMeleeWP()
{
	return m_wpSword;
}

void Player::Move(float movex, float movey)
{
	sf::Vector2f point1 = sf::Vector2f(m_HitBox->getPosition().x - m_HitBox->getOrigin().x + movex, m_HitBox->getPosition().y - m_HitBox->getOrigin().y + movey);
	sf::Vector2f point2 = sf::Vector2f(point1.x + movex, point1.y + m_HitBox->getSize().y * m_HitBox->getScale().y + movey);
	sf::Vector2f point3 = sf::Vector2f(point1.x + m_HitBox->getSize().x * m_HitBox->getScale().x + movex, point1.y + m_HitBox->getSize().y * m_HitBox->getScale().y + movey);
	sf::Vector2f point4 = sf::Vector2f(point1.x + m_HitBox->getSize().x * m_HitBox->getScale().x + movex, point1.y + movey);
	if ((*m_Tiles)[point2.y / TileSize][point2.x / TileSize]->getType() == TileType::TILE_FLOOR && (*m_Tiles)[point3.y / TileSize][point3.x / TileSize]->getType() == TileType::TILE_FLOOR)
	{
		m_HitBox->move(movex, movey);
		if ((int)(point2.x / (RoomMaxSize * TileSize)) ==  (int)(point3.x / (RoomMaxSize * TileSize)) && (int)(point2.y / (RoomMaxSize * TileSize)) == (int)(point3.y / (RoomMaxSize * TileSize))) {
			int x = point2.x / (RoomMaxSize * TileSize);
			int y = point2.y / (RoomMaxSize * TileSize);
			
			if ((*m_TileBoxes)[y][x]->getType() != TileBoxType::BOX_DEFAULT) {
				if (
					   ((int)point2.x % (int)(RoomMaxSize * TileSize) >= ((RoomMaxSize - (*m_TileBoxes)[y][x]->getSize().x) * TileSize / 2 + TileSize) && (int)point2.x % (int)(RoomMaxSize * TileSize) <= ((RoomMaxSize + (*m_TileBoxes)[y][x]->getSize().x) * TileSize / 2 - TileSize))
					&& ((int)point2.y % (int)(RoomMaxSize * TileSize) >= ((RoomMaxSize - (*m_TileBoxes)[y][x]->getSize().y) * TileSize / 2 + TileSize) && (int)point2.y % (int)(RoomMaxSize * TileSize) <= ((RoomMaxSize + (*m_TileBoxes)[y][x]->getSize().y) * TileSize / 2 - TileSize))
					&& ((int)point3.x % (int)(RoomMaxSize * TileSize) >= ((RoomMaxSize - (*m_TileBoxes)[y][x]->getSize().x) * TileSize / 2 + TileSize) && (int)point3.x % (int)(RoomMaxSize * TileSize) <= ((RoomMaxSize + (*m_TileBoxes)[y][x]->getSize().x) * TileSize / 2 - TileSize))
					&& ((int)point3.y % (int)(RoomMaxSize * TileSize) >= ((RoomMaxSize - (*m_TileBoxes)[y][x]->getSize().y) * TileSize / 2 + TileSize) && (int)point3.y % (int)(RoomMaxSize * TileSize) <= ((RoomMaxSize + (*m_TileBoxes)[y][x]->getSize().y) * TileSize / 2 - TileSize))
					) {
					m_RoomPos->x = x;
					m_RoomPos->y = y;
				}
				else {
					m_RoomPos->x = -1;
					m_RoomPos->y = -1;
				}
			}
			
		}
		else {
			m_RoomPos->x = -1;
			m_RoomPos->y = -1;
		}
		
	}
	//printf("%d %d\n", m_RoomPos->x, m_RoomPos->y);
	//m_HitBox->move(movex, movey);
}

void Player::setActive(bool active)
{
	m_Active = active;
}

bool Player::getActive()
{
	return m_Active;
}

WPGun* Player::getCurrentWP()
{
	return m_wpGuns[m_currentGunSlot];
}

int Player::getCoin()
{
	return m_Coin;
}

void Player::addCoin(int coin)
{
	m_Coin += coin;
	m_Coin = max(m_Coin, 0);
}

sf::Vector2i Player::getExp()
{
	return m_Exp;
}

void Player::addExp(int exp)
{
	m_Exp.x += exp;
	if (m_Exp.x >= m_Exp.y) {
		m_Level++;
		m_Exp.x -= m_Exp.y;
		switch (m_Level)
		{
		case 1:
			m_Exp.y = 100;
			m_Hp = sf::Vector2i(20, 20);
			m_Armor = sf::Vector2i(20, 20);
		case 2:
			m_Exp.y = 300;
			m_Hp = sf::Vector2i(20, 20);
			m_Armor = sf::Vector2i(30, 30);
		case 3:
			m_Exp.y = 2000;
			m_Hp = sf::Vector2i(30, 30);
			m_Armor = sf::Vector2i(35, 35);
		case 4:
			m_Exp.y = 10000;
			m_Hp = sf::Vector2i(30, 30);
			m_Armor = sf::Vector2i(50, 50);
		case 5:
			m_Exp.y = 30000;
			m_Hp = sf::Vector2i(50, 50);
			m_Armor = sf::Vector2i(60, 60);
		default:
			break;
		}
	}
	GConnect->setPExp(m_Exp);
}

void Player::setExp(int exp)
{
	m_Exp.x = exp;
}

int Player::getLevel()
{
	return m_Level;
}

bool Player::getHurt()
{
	return m_Hurt;
}

HitBox* Player::getHitBox()
{
	return m_HitBox;
}

void Player::LoseHp(int hp)
{
	if (hp < 0) {
		m_Hp.x = min(m_Hp.x - hp, m_Hp.y);
		return;
	}
	int temp = max(0, m_Armor.x - hp);
	if (temp == 0) {
		m_Armor.x = 0;
		hp -= m_Armor.x;
	}
	else {
		m_Armor.x -= hp;
		hp = 0;
	}
	m_Hp.x -= hp;
	m_Hp.x = max(m_Hp.x, 0);
	m_Hurt = true;
	m_currentHurtTime = 0.f;
}

void Player::LoseArmor(int armor)
{
	m_Armor.x -= armor;
}

sf::Vector2i Player::getHp()
{
	return m_Hp;
}

sf::Vector2i Player::getArmor()
{
	return m_Armor;
}

sf::Vector2f Player::getScale()
{
	return m_Scale;
}

void Player::PerformStateChange()
{
	if (m_nextState != IPState::SNULL) {
		switch (m_nextState)
		{
		case IPState::STATE_RUN:
			m_currentState = m_runState;
			break;
		case IPState::STATE_IDLE:
			m_currentState = m_idleState;
			break;
		case IPState::STATE_DEATH:
			m_currentState = m_deathState;
			break;
		case IPState::STATE_ATTACK:
			m_currentState = m_attackState;
			break;
		default:
			break;
		}
		m_nextState = IPState::SNULL;
	}
}
