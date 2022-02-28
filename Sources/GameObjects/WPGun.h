#pragma once
#include "Weapon.h"
#include "../GameManager/BulletsManager.h"

class IMob;
enum GunType {
	GUN_DEFAULT = 0,
	GUN_PISTOL,
	GUN_SHOTGUN,
	GUN_SMG,
	GUN_M202,
};
enum AmmoType {
	AMMO_DEFAULT = 0,
	AMMO_PISTOL,
	AMMO_SHOTGUN,
	AMMO_SMG,
	AMMO_RIFLE
};
class WPGun :public Weapon {
public:
	WPGun();
	~WPGun();
	void Init();
	void Update(float deltaTime);
	void Render(sf::RenderWindow* window);
	void Create(GunType type);
	float GetDamage();
	GunType getType();
	AmmoType getAmmoType();
	sf::Vector2i getAmmo();
	void setAmmo(sf::Vector2i ammo);
	sf::Vector2i getClip();
	string getAssetName();
	
protected:
	sf::Sprite* m_weapon;
	sf::CircleShape* m_ShootPos;
	float m_Radius;
	float m_damage;
	bool m_Active;
	GunType m_Type;
	AmmoType m_AmmoType;
	sf::Vector2i m_Ammo;
	sf::Vector2i m_Clip;
	bool m_Reloading;
	float m_ReloadTime;
	string m_AssetName;
	Animation* m_Reload;
};