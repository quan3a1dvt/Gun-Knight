#include "ShopItem.h"
#include "IPlayer.h"
#include "WPGun.h"
ShopItem::ShopItem()
{
	m_Scale = sf::Vector2f(2.f, 2.f);
	m_Type = DEFAULT;
	m_HitBox = HitBox(sf::Vector2i(10.f, 10.f));
	m_waitTime = 1.f;
	m_currentTime = 0.f;
}

ShopItem::~ShopItem()
{
}

void ShopItem::Init()
{
}

void ShopItem::Update(float deltaTime)
{
	m_currentTime += deltaTime;
	if (m_Type != DEFAULT) {
		if (Collision::BoundingBoxTest(GConnect->getPlayer()->getHitBox(), &m_HitBox)) {
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::B) && m_currentTime >= m_waitTime) {
				m_currentTime = 0.f;
				switch (m_Type)
				{
				case DEFAULT:
					return;
					break;
				case PISTOL_B:
					if (GConnect->getPlayer()->getCurrentWP()->getAmmoType() == AmmoType::AMMO_PISTOL && GConnect->getPlayer()->getCoin() >= m_Price) {
						GConnect->getPlayer()->getCurrentWP()->setAmmo(sf::Vector2i(1000, 1000));
						GConnect->getPlayer()->addCoin(-1 * m_Price);
					}
					break;
				case SHOTGUN_B:
					if (GConnect->getPlayer()->getCurrentWP()->getAmmoType() == AmmoType::AMMO_SHOTGUN && GConnect->getPlayer()->getCoin() >= m_Price) {
						GConnect->getPlayer()->getCurrentWP()->setAmmo(sf::Vector2i(GConnect->getPlayer()->getCurrentWP()->getAmmo().y, GConnect->getPlayer()->getCurrentWP()->getAmmo().y));
						GConnect->getPlayer()->addCoin(-1 * m_Price);
					}
					break;
				case SMG_B:
					if (GConnect->getPlayer()->getCurrentWP()->getAmmoType() == AmmoType::AMMO_SMG && GConnect->getPlayer()->getCoin() >= m_Price) {
						GConnect->getPlayer()->getCurrentWP()->setAmmo(sf::Vector2i(GConnect->getPlayer()->getCurrentWP()->getAmmo().y, GConnect->getPlayer()->getCurrentWP()->getAmmo().y));
						GConnect->getPlayer()->addCoin(-1 * m_Price);
					}
					break;
				case BANDAGE:
					if (GConnect->getPlayer()->getCoin() >= m_Price) {
						GConnect->getPlayer()->LoseHp(-1 * 10);
						GConnect->getPlayer()->addCoin(-1 * m_Price);
					}
					break;
				default:
					break;
				}
			}
		}
	}
}

void ShopItem::Render(sf::RenderWindow* window)
{
	if (m_Type != DEFAULT) {
		window->draw(m_Item);
		if (Collision::BoundingBoxTest(GConnect->getPlayer()->getHitBox(), &m_HitBox)) {
			window->draw(m_PriceText);
		}
	}
}

void ShopItem::Create(sf::Vector2f pos, ShopItemType type)
{
	m_Type = type;
	switch (type)
	{
	case DEFAULT:
		return;
		break;
	case PISTOL_B:
		m_Item.setTexture(*ASSET->getTexture("Item/pistol_bullet"));
		m_Price = 20;
		break;
	case SHOTGUN_B:
		m_Item.setTexture(*ASSET->getTexture("Item/shotgun_bullet"));
		m_Price = 30;
		break;
	case SMG_B:
		m_Item.setTexture(*ASSET->getTexture("Item/smg_bullet"));
		m_Price = 40;
		break;
	case BANDAGE:
		m_Item.setTexture(*ASSET->getTexture("Item/bandage"));
		m_Price = 50;
		break;
	default:
		break;
	}

	m_Item.setOrigin(m_Item.getTexture()->getSize().x / 2.f, m_Item.getTexture()->getSize().y / 2.f);
	m_Item.setScale(m_Scale);
	m_Item.setPosition(pos);
	m_HitBox.setPosition(pos);
	m_PriceText.setFont(*ASSET->getFont("EvilEmpire-4BBVK"));
	m_PriceText.setString(to_string(m_Price));
	m_PriceText.setFillColor(sf::Color::Yellow);
	m_PriceText.setCharacterSize(20.0f * m_Scale.x);
	m_PriceText.setOutlineThickness(1.f);
	m_PriceText.setOrigin(m_PriceText.getLocalBounds().left + m_PriceText.getLocalBounds().width / 2.0f, m_PriceText.getLocalBounds().top + m_PriceText.getLocalBounds().height / 2.0f);
	m_PriceText.setPosition(pos.x, pos.y - m_Item.getTexture()->getSize().y * m_Scale.y / 2 - 10 * m_Scale.y);
}
