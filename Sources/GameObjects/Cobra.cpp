#include "Cobra.h"
#include "Cobra_SSpawn.h"
#include "Cobra_SIdle.h"
#include "Cobra_SRun.h"
#include "Cobra_SAttack.h"
#include "Cobra_SDeath.h"

Cobra::Cobra()
{
	m_damage = 1;

	m_scale = sf::Vector2f(4.f, 4.f);
	m_spawnState = new Cobra_SSpawn(this);
	m_idleState = new Cobra_SIdle(this);
	m_runState = new Cobra_SRun(this);
	m_attackState = new Cobra_SAttack(this);
	m_deathState = new Cobra_SDeath(this);
	
	
	m_HitBox = new HitBox(sf::Vector2i(15 * m_scale.x, 12 * m_scale.x));

	m_Active = false;

}

Cobra::~Cobra()
{
	if (m_spawnState != nullptr) {
		delete m_idleState;
	}
	if (m_idleState != nullptr) {
		delete m_idleState;
	}
	if (m_runState != nullptr) {
		delete m_runState;
	}
	if (m_attackState != nullptr) {
		delete m_attackState;
	}
	if (m_deathState != nullptr) {
		delete m_deathState;
	}
	m_currentState = nullptr;

	if (m_HitBox != nullptr) {
		delete m_HitBox;
	}
}

void Cobra::ChangeNextState(IMState::STATE nextState)
{
	m_nextState = nextState;
}

void Cobra::Init()
{
	m_nextState = IMState::SNULL;
	m_currentState = m_spawnState;
	m_spawnState->Init();
	m_idleState->Init();
	m_runState->Init();
	m_attackState->Init();
	m_deathState->Init();

	m_HitBox->Init(200.f);
	/*
	m_hitNumber.setFont(*ASSET->getFont("EvilEmpire-4BBVK"));
	m_hitNumber.setPosition(m_HitBox->getPosition().x, m_HitBox->getPosition().y - 2 * m_HitBox->getSize().y);
	m_hitNumber.setFillColor(sf::Color(255, 0, 0));
	m_hitNumber.setCharacterSize(0.0f);
	m_hitNumber.setOrigin(m_hitNumber.getLocalBounds().left + m_hitNumber.getLocalBounds().width / 2.0f, m_hitNumber.getLocalBounds().top + m_hitNumber.getLocalBounds().height / 2.0f);
	m_Active = true;
	*/
	
	m_Hp = sf::Vector2i(100, 100);

	m_choosedMoveWay = 0;
	m_followTime = 0.f;
	m_followTimeLimit = 1.f;
	m_waitTime = random::random(2, 10) / 10.f;
	m_canAttack = true;
	m_canMove = true;

	m_stop = false;
}

void Cobra::Update(float deltaTime)
{

	if (m_Active) {
		m_currentState->Update(deltaTime);
		PerformStateChange();
		if (m_currentState != m_spawnState) {
			PerformAIMovement(deltaTime);
			m_hitNumber.setPosition(m_HitBox->getPosition().x, m_HitBox->getPosition().y - 2 * m_HitBox->getSize().y);
			if (CheckAttackedByMelee()) {
				//m_canMove = false;
				LoseHP(GConnect->getPlayer()->GetMeleeWP()->GetDamage());
				m_hitNumber.setString(to_string((int)GConnect->getPlayer()->GetMeleeWP()->GetDamage()));
				m_hitNumber.setCharacterSize(15.0f);
			}
			if (m_Hp.x <= 0) {
				m_canMove = false;
				ChangeNextState(IMState::STATE_DEATH);
			}
		}
	}
	
}

void Cobra::Render(sf::RenderWindow* window)
{
	if (m_Active) {
		m_currentState->Render(window);
		window->draw(*m_HitBox);
		//window->draw(m_hitNumber);
	}
	
}

bool Cobra::CheckAttackedByMelee()
{
	if (GConnect->getPlayer()->GetMeleeWP()->isAttacking()) {
		if (Collision::BoundingBoxTest(GConnect->getPlayer()->GetMeleeWP()->getHitBox(), m_HitBox)) {
			for (int i = 0; i < (int)GConnect->getPlayer()->GetMeleeWP()->GetHitMob()->size(); i++) {
				if (this == GConnect->getPlayer()->GetMeleeWP()->GetHitMob()->at(i)) {
					return false;
				}
			}		
			GConnect->getPlayer()->GetMeleeWP()->AddHitMob(this);
			return true;
		}
	}
	return false;
}

void Cobra::PerformAIMovement(float deltaTime)
{
	
	vector<IMob*>* mobs = GConnect->getMobs();
	sf::Vector2f PlayerPos = GConnect->getPlayer()->getHitBox()->getPosition();
	//m_distPlayer = sqrt((PlayerPos.x - m_HitBox->getPosition().x) * (PlayerPos.x - m_HitBox->getPosition().x) + (PlayerPos.y - m_HitBox->getPosition().y) * (PlayerPos.y - m_HitBox->getPosition().y));
	
	if (m_choosedMoveWay == 0 && m_canMove) {
		//follow or to prepos (1 || 2)
		m_followTime += deltaTime;
		if (m_followTime >= m_waitTime) {
			randValue = random::random(1, 7);
			m_stop = false;
			if (randValue <= 3) {
				randValue = 10.f;
				m_choosedMoveWay = 1;
				m_followTime = 0;
			}
			else if (randValue == 4) {
				randValue = random::random(20, 300);
				//printf("%d\n", randValue);
				m_choosedMoveWay = 2;
				m_destination = PlayerPos;
				m_followTime = 0;
			}
			else {
				randValue = random::random(20, 100);
				
				m_destination.x = m_HitBox->getPosition().x + (random::random(1, 2) == 1 ? 1 : -1) * random::random(20, 200);
				m_destination.y = m_HitBox->getPosition().y + (random::random(1, 2) == 1 ? 1 : -1) * random::random(20, 200);
				m_choosedMoveWay = 2;
				m_followTime = 0;
			}
			m_canAttack = true;
		}
		
		
	}
	else if (m_choosedMoveWay == 1 && m_canMove) {
		if (m_followTime < m_followTimeLimit) {
			m_destination = PlayerPos;
			if (fabs(m_destination.x - m_HitBox->getPosition().x) >= randValue || fabs(m_destination.y - m_HitBox->getPosition().y) >= randValue && m_stop == false) {
				movex = (m_destination.x - m_HitBox->getPosition().x >= 0 ? 1 : -1) * min(m_HitBox->GetVelocity() * deltaTime, fabs(m_destination.x - m_HitBox->getPosition().x));
				movey = (m_destination.y - m_HitBox->getPosition().y >= 0 ? 1 : -1) * min(m_HitBox->GetVelocity() * deltaTime, fabs(m_destination.y - m_HitBox->getPosition().y));
				bool collis = false;
				for (int i = 0; i < mobs->size(); i++) {
					if (mobs->at(i)->getActive() && mobs->at(i) != this) {
						if (Collision::WillBoundingBoxTest(m_HitBox, mobs->at(i)->getHitBox(), movex, movey)) {
							collis = true;
							break;
						}
					}
				}

				if (collis == false) {
					Move(movex, movey);
				}
				else m_stop = true;
				ChangeNextState(IMState::STATE_RUN);
			}
			else {
				m_choosedMoveWay = 0;
				m_waitTime = random::random(2, 5) * 1.f / 10.f;
				if (m_currentState != m_idleState)
				ChangeNextState(IMState::STATE_ATTACK);
			}
			m_cw = (PlayerPos.x - m_HitBox->getPosition().x > 1.f ? true : false);
			m_followTime += deltaTime;
			
		}
		else {
			m_choosedMoveWay = 0;
			//ChangeNextState(IMState::STATE_IDLE);
		}
	}
	else if (m_choosedMoveWay == 2 && m_canMove) {
		if (m_followTime < m_followTimeLimit) {
			if ((fabs(m_destination.x - m_HitBox->getPosition().x) >= randValue || fabs(m_destination.y - m_HitBox->getPosition().y) >= randValue) && m_stop == false) {
				movex = (m_destination.x - m_HitBox->getPosition().x >= 0 ? 1 : -1) * min(m_HitBox->GetVelocity() * deltaTime, fabs(m_destination.x - m_HitBox->getPosition().x));
				movey = (m_destination.y - m_HitBox->getPosition().y >= 0 ? 1 : -1) * min(m_HitBox->GetVelocity() * deltaTime, fabs(m_destination.y - m_HitBox->getPosition().y));

				bool collis = false;
				for (int i = 0; i < mobs->size(); i++) {
					if (mobs->at(i)->getActive() && mobs->at(i) != this) {
						if (Collision::WillBoundingBoxTest(m_HitBox, mobs->at(i)->getHitBox(), movex, movey)) {
							collis = true;
							break;
						}
					}
				}

				if (collis == false) {
					Move(movex, movey);
				}
				else m_stop = true;
				m_cw = (PlayerPos.x - m_HitBox->getPosition().x > 1.f ? true : false);
				ChangeNextState(IMState::STATE_RUN);
			}
			else {
				m_choosedMoveWay = 0;
				m_waitTime = random::random(2, 5) * 1.f / 10.f;
				if (m_currentState != m_idleState)
					ChangeNextState(IMState::STATE_IDLE);
			}
			m_followTime += deltaTime;
		}
		else {
			m_choosedMoveWay = 0;
			if (m_currentState != m_idleState) ChangeNextState(IMState::STATE_IDLE);
		}
	}
	
}

void Cobra::Spawn()
{
	Init();
	while (1) {

		bool canSpawn = true;
		m_SpawnPos.x = random::random((int)(RoomMaxSize * TileSize * GConnect->getRoomPos()->x + (RoomMaxSize - (*GConnect->getTileBoxes())[GConnect->getRoomPos()->y][GConnect->getRoomPos()->x]->getSize().x) * TileSize / 2 + 2 * TileSize),
			(int)(RoomMaxSize * TileSize * GConnect->getRoomPos()->x + (RoomMaxSize + (*GConnect->getTileBoxes())[GConnect->getRoomPos()->y][GConnect->getRoomPos()->x]->getSize().x) * TileSize / 2 - 2 * TileSize));
		m_SpawnPos.y = random::random((int)(RoomMaxSize * TileSize * GConnect->getRoomPos()->y + (RoomMaxSize - (*GConnect->getTileBoxes())[GConnect->getRoomPos()->y][GConnect->getRoomPos()->x]->getSize().y) * TileSize / 2 + 2 * TileSize),
			(int)(RoomMaxSize * TileSize * GConnect->getRoomPos()->y + (RoomMaxSize + (*GConnect->getTileBoxes())[GConnect->getRoomPos()->y][GConnect->getRoomPos()->x]->getSize().y) * TileSize / 2 - 2 * TileSize));
		FOR(i, 0, GConnect->getMobs()->size() - 1) {
			if (GConnect->getMobs()->at(i)->getActive()) {
				if (Collision::BoundingBoxTest(m_HitBox, GConnect->getMobs()->at(i)->getHitBox())) {
					canSpawn = false;
					break;
				}
			}
		}
		if (canSpawn) {
			//printf("%d %d %f %f\n", m_SpawnPos.x, m_SpawnPos.y, GConnect->getPlayer()->getHitBox()->getPosition().x, GConnect->getPlayer()->getHitBox()->getPosition().y);
			m_HitBox->setPosition(m_SpawnPos.x, m_SpawnPos.y);
			m_Active = true;
			break;
		}
	}
}

void Cobra::Move(float movex, float movey)
{
	sf::Vector2f point1 = sf::Vector2f(m_HitBox->getPosition().x - m_HitBox->getOrigin().x + movex, m_HitBox->getPosition().y - m_HitBox->getOrigin().y + movey);
	sf::Vector2f point2 = sf::Vector2f(point1.x + movex, point1.y + m_HitBox->getSize().y * m_HitBox->getScale().y + movey);
	sf::Vector2f point3 = sf::Vector2f(point1.x + m_HitBox->getSize().x * m_HitBox->getScale().x + movex, point1.y + m_HitBox->getSize().y * m_HitBox->getScale().y + movey);
	sf::Vector2f point4 = sf::Vector2f(point1.x + m_HitBox->getSize().x * m_HitBox->getScale().x + movex, point1.y + movey);
	if ((*GConnect->getTiles())[point2.y / TileSize][point2.x / TileSize]->getType() == TileType::TILE_FLOOR && (*GConnect->getTiles())[point3.y / TileSize][point3.x / TileSize]->getType() == TileType::TILE_FLOOR)
	{
		m_HitBox->move(movex, movey);
	}
	else m_stop = true;
}

void Cobra::LoseHP(int hp)
{
	m_Hp.x -= hp;
}

Animation* Cobra::getSprite()
{
	return m_currentState->getSprite();
}

sf::Shader* Cobra::getShader()
{
	return nullptr;
}



void Cobra::PerformStateChange()
{
	if (m_nextState != IMState::SNULL) {
		switch (m_nextState)
		{
		case IMState::STATE_SPAWN:
			m_currentState = m_idleState;
			break;
		case IMState::STATE_IDLE:
			m_currentState = m_idleState;
			break;
		case IMState::STATE_RUN:
			m_currentState = m_runState;
			break;		
		case IMState::STATE_ATTACK:
			m_currentState = m_attackState;
			break;
		case IMState::STATE_DEATH:
			m_currentState = m_deathState;
			break;
		default:
			break;
		}
		m_nextState = IMState::SNULL;
	}
}
