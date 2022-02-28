#include "WPGun.h"
#include "IPlayer.h"
WPGun::WPGun()
{
	m_weapon = new sf::Sprite;
	m_ShootPos = new sf::CircleShape(3);
	m_damage = 20;
	m_waitTime = 0.4f;
	m_isAttacking = false;
	m_Active = false;
	m_Reloading = false;
}

WPGun::~WPGun()
{
}



void WPGun::Init()
{
	m_ShootPos->setOutlineThickness(1.0f);
	m_ShootPos->setOutlineColor(sf::Color::Red);
	m_ShootPos->setPointCount(40);
	m_Reload = new Animation(*ASSET->getTexture("GUI/Reloading"), sf::Vector2i(12, 1), 0.1f);
	m_Reload->setScale(0.3f, 0.3f);
}



void WPGun::Update(float deltaTime)
{
	m_currentTime += deltaTime;

	m_Reload->setPosition(GConnect->getPlayer()->getHitBox()->getPosition().x, GConnect->getPlayer()->getHitBox()->getPosition().y - GConnect->getPlayer()->getHitBox()->getSize().y * 3 / 4);
	m_Reload->Update(deltaTime);
	if (m_Active) {

	}
	phitboxPos = GConnect->getPlayer()->getHitBox()->getPosition();
	phitboxScale = GConnect->getPlayer()->getHitBox()->getScale();
	phitboxSize = GConnect->getPlayer()->getHitBox()->getSize();
	mousePos = sf::Vector2f(sf::Mouse::getPosition(*WConnect->getWindow()).x + phitboxPos.x - screenWidth / 2, sf::Mouse::getPosition(*WConnect->getWindow()).y + phitboxPos.y - screenHeight / 2);
	wpScale = m_weapon->getScale();
	wpPos = m_weapon->getPosition();
	wpSize = m_weapon->getTexture()->getSize();
	isPlayerCW = GConnect->getPlayer()->getCW();
	m_weapon->setPosition(phitboxPos.x + (isPlayerCW ? 1 : -1) * phitboxSize.x / 4, phitboxPos.y + phitboxSize.y / 4);
	m_ShootPos->setPosition(m_weapon->getPosition());
	m_weapon->setScale((isPlayerCW ? 1 : -1) * fabs(wpScale.x), fabs(wpScale.y));
	m_ShootPos->setScale((isPlayerCW ? 1 : -1) * 1.f, 1.f);
	if (isPlayerCW) {
		if ((mousePos.x >= (phitboxPos.x - phitboxSize.x / 4)) && (mousePos.x <= (phitboxPos.x + phitboxSize.x / 4))) {
			angle = atan((wpPos.y - mousePos.y) / (-mousePos.x + wpPos.x)) * 57.2957795 + 180.f;
		}
		else {
			angle = - atan((wpPos.y - mousePos.y) / (mousePos.x - wpPos.x)) * 57.2957795;
		}
		m_weapon->setRotation(angle);
		m_ShootPos->setRotation(angle);
	}
	else {

		if ((mousePos.x > (phitboxPos.x - phitboxSize.x / 4)) && (mousePos.x < (phitboxPos.x + phitboxSize.x / 4))) {
			angle = 90.f - atan((wpPos.y - mousePos.y) / (mousePos.x - wpPos.x)) * 57.2957795;
		}
		else {
			angle = atan((wpPos.y - mousePos.y) / (-mousePos.x + wpPos.x)) * 57.2957795;

		}
		m_weapon->setRotation(angle);
		m_ShootPos->setRotation(angle);
	}
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && m_Reloading == false) {
		if (m_currentTime >= m_waitTime) {
			m_currentTime = 0;
			switch (m_Type)
			{
			case GUN_PISTOL:
			{
				if (isPlayerCW) {
					m_Radius = sqrt(m_ShootPos->getOrigin().x * m_ShootPos->getOrigin().x + m_ShootPos->getOrigin().y * m_ShootPos->getOrigin().y);
					angle = -angle;
				}
				else
				{
					m_Radius = -sqrt(m_ShootPos->getOrigin().x * m_ShootPos->getOrigin().x + m_ShootPos->getOrigin().y * m_ShootPos->getOrigin().y);
					angle = 180.f - angle;
				}
				vector<float> temp(3, -1);
				temp[0] = 1000.f;
				temp[1] = angle;
				temp[2] = 5.f;
				sf::Vector2f shootpos;
				shootpos.x = m_ShootPos->getPosition().x + m_Radius * cos(m_ShootPos->getRotation() * 3.14f / 180.f);
				shootpos.y = m_ShootPos->getPosition().y + m_Radius * sin(m_ShootPos->getRotation() * 3.14f / 180.f);
				//printf("%f %f   %f %f\n", shootpos.x, shootpos.y, m_ShootPos->getPosition().x, m_ShootPos->getPosition().y);
				if (m_Clip.x > 0) {
					BManager->Create(ShootType::SHOOT_2, BulletType::BULLET_ROUND1, "ROUND1", shootpos, sf::Vector2f(13.f, 13.f), true, 10, temp);
					m_Clip.x--;
					m_Ammo.x--;
				}
				else {
					m_Reloading = true;
					m_currentTime = 0.f;
				}
				//GConnect->getView()->setCenter(GConnect->getPlayer()->getHitBox()->getPosition().x - 20.f, GConnect->getPlayer()->getHitBox()->getPosition().y);

				break;
			}
			case GUN_SHOTGUN:
			{
				if (isPlayerCW) {
					m_Radius = sqrt(m_ShootPos->getOrigin().x * m_ShootPos->getOrigin().x + m_ShootPos->getOrigin().y * m_ShootPos->getOrigin().y);
					angle = -angle;
				}
				else
				{
					m_Radius = -sqrt(m_ShootPos->getOrigin().x * m_ShootPos->getOrigin().x + m_ShootPos->getOrigin().y * m_ShootPos->getOrigin().y);
					angle = 180.f - angle;
				}
				vector<float> temp(5, -1);
				temp[0] = 1000.f;
				temp[1] = 7.f;
				temp[2] = angle;
				temp[3] = 3.f;
				temp[4] = 3.f;
				sf::Vector2f shootpos;
				shootpos.x = m_ShootPos->getPosition().x + m_Radius * cos(m_ShootPos->getRotation() * 3.14f / 180.f);
				shootpos.y = m_ShootPos->getPosition().y + m_Radius * sin(m_ShootPos->getRotation() * 3.14f / 180.f);
				if (m_Clip.x > 0) {
					BManager->Create(ShootType::SHOOT_3, BulletType::BULLET_ROUND1, "ROUND1", shootpos, sf::Vector2f(13.f, 13.f), true, 6, temp);
					m_Clip.x--;
					m_Ammo.x--;
				}
				else {
					m_Reloading = true;
					m_currentTime = 0.f;
				}
				//GConnect->getView()->setCenter(GConnect->getPlayer()->getHitBox()->getPosition().x - 20.f, GConnect->getPlayer()->getHitBox()->getPosition().y);

				break;
			}
			case GUN_SMG:
			{
				if (isPlayerCW) {
					m_Radius = sqrt(m_ShootPos->getOrigin().x * m_ShootPos->getOrigin().x + m_ShootPos->getOrigin().y * m_ShootPos->getOrigin().y);
					angle = -angle;
				}
				else
				{
					m_Radius = -sqrt(m_ShootPos->getOrigin().x * m_ShootPos->getOrigin().x + m_ShootPos->getOrigin().y * m_ShootPos->getOrigin().y);
					angle = 180.f - angle;
				}
				vector<float> temp(3, -1);
				temp[0] = 1000.f;
				temp[1] = angle;
				temp[2] = 8.f;
				sf::Vector2f shootpos;
				shootpos.x = m_ShootPos->getPosition().x + m_Radius * cos(m_ShootPos->getRotation() * 3.14f / 180.f);
				shootpos.y = m_ShootPos->getPosition().y + m_Radius * sin(m_ShootPos->getRotation() * 3.14f / 180.f);
				//printf("%f %f   %f %f\n", shootpos.x, shootpos.y, m_ShootPos->getPosition().x, m_ShootPos->getPosition().y);
				if (m_Clip.x > 0) {
					BManager->Create(ShootType::SHOOT_2, BulletType::BULLET_ROUND1, "ROUND1", shootpos, sf::Vector2f(13.f, 13.f), true, 8, temp);
					m_Clip.x--;
					m_Ammo.x--;
				}
				else {
					m_Reloading = true;
					m_currentTime = 0.f;
				}
				//GConnect->getView()->setCenter(GConnect->getPlayer()->getHitBox()->getPosition().x - 20.f, GConnect->getPlayer()->getHitBox()->getPosition().y);

				break;
			}
			case GUN_M202:
			{
				if (isPlayerCW) {
					m_Radius = sqrt(m_ShootPos->getOrigin().x * m_ShootPos->getOrigin().x + m_ShootPos->getOrigin().y * m_ShootPos->getOrigin().y);
					angle = -angle;
				}
				else
				{
					m_Radius = -sqrt(m_ShootPos->getOrigin().x * m_ShootPos->getOrigin().x + m_ShootPos->getOrigin().y * m_ShootPos->getOrigin().y);
					angle = 180.f - angle;
				}
				vector<float> temp(5, -1);
				temp[0] = 1000.f;
				temp[1] = 6.f;
				temp[2] = angle;
				temp[3] = 3.f;
				temp[4] = 3.f;
				sf::Vector2f shootpos;
				shootpos.x = m_ShootPos->getPosition().x + m_Radius * cos(m_ShootPos->getRotation() * 3.14f / 180.f);
				shootpos.y = m_ShootPos->getPosition().y + m_Radius * sin(m_ShootPos->getRotation() * 3.14f / 180.f);
				if (m_Clip.x > 0) {
				//	BManager->Create(ShootType::SHOOT_3, BulletType::BULLET_ROCKET1, "ROUND1", shootpos, sf::Vector2f(13.f, 13.f), true, 2, temp);
					m_Clip.x--;
					m_Ammo.x--;
				}
				else {
					m_Reloading = true;
					m_currentTime = 0.f;
				}
				//GConnect->getView()->setCenter(GConnect->getPlayer()->getHitBox()->getPosition().x - 20.f, GConnect->getPlayer()->getHitBox()->getPosition().y);

				break;
			}
			default:
				break;
			}
		}
		
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::R) && m_Reloading == false) {
		m_Reloading = true;
		m_currentTime = 0.f;
	}
	if (m_currentTime >= m_ReloadTime && m_Reloading == true) {
		m_Clip.x += min(m_Ammo.x, m_Clip.y - m_Clip.x);
		m_Ammo.x -= min(m_Ammo.x, m_Clip.y - m_Clip.x);
		m_Reloading = false;
	}
}



void WPGun::Render(sf::RenderWindow* window)
{
	window->draw(*m_weapon);
	//window->draw(*m_ShootPos);
	if (m_Reloading) window->draw(*m_Reload);
}

void WPGun::Create(GunType type)
{
	m_Type = type;
	switch (m_Type)
	{
	case GUN_PISTOL:
	{
		m_AssetName = "Pistol";
		m_weapon->setTexture(*ASSET->getTexture("Gun/Pistol"));	
		m_weapon->setOrigin(m_weapon->getTexture()->getSize().x / 4, m_weapon->getTexture()->getSize().y / 2);
		m_weapon->setScale(1.2f, 1.2f);
		m_ShootPos->setOrigin(-1.f * m_weapon->getTexture()->getSize().x * m_weapon->getScale().x, 1.f * m_weapon->getTexture()->getSize().y * m_weapon->getScale().y / 6);		
		m_Active = true;
		m_waitTime = 0.6f;
		m_Ammo = sf::Vector2i(1000,1000);
		m_Clip = sf::Vector2i(8, 8);
		m_AmmoType = AMMO_PISTOL;
		m_ReloadTime = 1.f;
		break;
	}
	case GUN_SHOTGUN:
	{
		m_AssetName = "Shotgun";
		m_weapon->setTexture(*ASSET->getTexture("Gun/Shotgun"));
		m_weapon->setOrigin(m_weapon->getTexture()->getSize().x / 4, m_weapon->getTexture()->getSize().y / 2);
		m_weapon->setScale(2.0f, 2.0f);
		m_ShootPos->setOrigin(-1.f * m_weapon->getTexture()->getSize().x * m_weapon->getScale().x, 1.f * m_weapon->getTexture()->getSize().y * m_weapon->getScale().y / 6);
		m_Active = true;
		m_waitTime = 0.6f;
		m_Ammo = sf::Vector2i(50, 50);
		m_Clip = sf::Vector2i(3, 3);
		m_AmmoType = AMMO_SHOTGUN;
		m_ReloadTime = 1.f;
		break;
	}
	case GUN_SMG:
	{
		m_AssetName = "Smg";
		m_weapon->setTexture(*ASSET->getTexture("Gun/Smg"));
		m_weapon->setOrigin(m_weapon->getTexture()->getSize().x / 4, m_weapon->getTexture()->getSize().y / 2);
		m_weapon->setScale(1.6f, 1.6f);
		m_ShootPos->setOrigin(-1.f * m_weapon->getTexture()->getSize().x * m_weapon->getScale().x, 1.f * m_weapon->getTexture()->getSize().y * m_weapon->getScale().y / 6);
		m_Active = true;
		m_waitTime = 0.1f;
		m_Ammo = sf::Vector2i(200, 200);
		m_Clip = sf::Vector2i(35, 35);
		m_AmmoType = AMMO_SMG;
		m_ReloadTime = 1.f;
		break;
	}
	case GUN_M202:
	{
		m_weapon->setTexture(*ASSET->getTexture("Gun/M202"));
		m_weapon->setOrigin(m_weapon->getTexture()->getSize().x / 4, m_weapon->getTexture()->getSize().y / 2);
		m_weapon->setScale(2.0f, 2.0f);
		m_ShootPos->setOrigin(-1.f * m_weapon->getTexture()->getSize().x * m_weapon->getScale().x, 1.f * m_weapon->getTexture()->getSize().y * m_weapon->getScale().y / 6);
		m_Active = true;
		m_waitTime = 0.6f;
		m_Ammo = sf::Vector2i(100, 100);
		m_Clip = sf::Vector2i(1, 1);
		m_AmmoType = AMMO_SHOTGUN;
		m_ReloadTime = 1.f;
		break;
	}
	default:
		break;
	}
}
float WPGun::GetDamage()
{
	return 1;
}

sf::Vector2i WPGun::getAmmo()
{
	return m_Ammo;
}

void WPGun::setAmmo(sf::Vector2i ammo)
{
	m_Ammo = ammo;
}

sf::Vector2i WPGun::getClip()
{
	return m_Clip;
}

GunType WPGun::getType()
{
	return m_Type;
}

AmmoType WPGun::getAmmoType()
{
	return m_AmmoType;
}

string WPGun::getAssetName()
{
	return m_AssetName;
}
