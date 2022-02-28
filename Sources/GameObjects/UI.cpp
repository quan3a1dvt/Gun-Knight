#include "UI.h"
#include "IPlayer.h"
UI::UI()
{
	m_Clips.resize(50);
	m_HpCount.resize(80);
	m_ArmorCount.resize(80);
}

UI::~UI()
{
	//
}

void UI::Init()
{
	m_HudScale = sf::Vector2f(1.5f, 1.5f);
	m_HudPos = sf::Vector2f(30.f, 30.f);
	m_Hud.setTexture(*ASSET->getTexture("GUI/hud/full_hud_bg"));
	m_Hud.setPosition(m_HudPos);
	m_Hud.setScale(m_HudScale);

	m_HpBar.setTexture(*ASSET->getTexture("GUI/hud/hp_bar"));
	m_HpBar.setPosition(m_HudPos.x + 88.f * m_HudScale.x, m_HudPos.y + 7.1f * m_HudScale.y);
	m_HpBar.setScale(m_HudScale);
	FOR(i, 0, m_HpCount.size() - 1) {
		m_HpCount[i].setSize(sf::Vector2f(2.f, m_HpBar.getTexture()->getSize().y * m_HudScale.y));
		m_HpCount[i].setFillColor(sf::Color::Black);
	}

	m_ArmorBar.setTexture(*ASSET->getTexture("GUI/hud/armor_bar"));
	m_ArmorBar.setPosition(m_HudPos.x + 88.f * m_HudScale.x, m_HudPos.y + 32.f * m_HudScale.y);
	m_ArmorBar.setScale(m_HudScale);
	FOR(i, 0, m_HpCount.size() - 1) {
		m_ArmorCount[i].setSize(sf::Vector2f(2.f, m_ArmorBar.getTexture()->getSize().y * m_HudScale.y));
		m_ArmorCount[i].setFillColor(sf::Color::Black);
	}

	m_ExpBar.setTexture(*ASSET->getTexture("GUI/hud/exp_bar"));
	m_ExpBar.setPosition(m_HudPos.x + 69.f * m_HudScale.x, m_HudPos.y + 46.f * m_HudScale.y);
	m_ExpBar.setScale(m_HudScale);
	m_ExpText.setFont(*ASSET->getFont("EvilEmpire-4BBVK"));
	m_ExpText.setFillColor(sf::Color::Green);
	m_ExpText.setOutlineThickness(1.f);
	m_ExpText.setCharacterSize(0.0f);
	m_ExpText.setPosition(m_HudPos.x + 68.f * m_HudScale.x, m_HudPos.y + 50.f * m_HudScale.y);

	m_PHud.setRadius(33.f * m_HudScale.x);
	m_PHud.setTexture(ASSET->getTexture("GUI/hud/PHud"));
	m_PHud.setPosition(m_HudPos.x , m_HudPos.y);

	m_CoinHud = Animation(*ASSET->getTexture("Coin"), sf::Vector2i(5, 1), 0.1f);
	m_CoinHud.setPosition(m_HudPos.x + 270.f * m_HudScale.x, m_HudPos.y + 14.1f * m_HudScale.y);
	m_CoinHud.setScale(m_HudScale);

	m_CoinText.setFont(*ASSET->getFont("EvilEmpire-4BBVK"));
	m_CoinText.setFillColor(sf::Color::Yellow);
	m_CoinText.setOutlineThickness(1.f);
	m_CoinText.setCharacterSize(0.0f);
	m_CoinText.setPosition(m_HudPos.x + 280.f * m_HudScale.x, m_HudPos.y  + 5.f * m_HudScale.y);

	m_ClipScale = sf::Vector2f(2.f, 2.f);
	m_ClipPos = sf::Vector2f(screenWidth - 20.f, screenHeight - 20.f);
	m_AmmoType = AmmoType::AMMO_DEFAULT;

	m_ClipBar.setTexture(*ASSET->getTexture("GUI/clip_bar"));
	m_ClipBar.setOrigin(m_ClipBar.getTexture()->getSize().x, m_ClipBar.getTexture()->getSize().y);
	m_ClipBar.setPosition(m_ClipPos);

	m_Ammo.setString("0");
	m_Ammo.setFont(*ASSET->getFont("EvilEmpire-4BBVK"));
	m_Ammo.setPosition(screenWidth - 240.f, screenHeight - 180.f);
	m_Ammo.setFillColor(sf::Color(255, 255, 255));
	m_Ammo.setCharacterSize(25.0f);
	//m_Ammo.setOrigin(m_Ammo.getLocalBounds().left + m_Ammo.getLocalBounds().width, 0.f);

	m_GunFrame.setSize(sf::Vector2f(170.f, 100.f));
	m_GunFrame.setPosition(screenWidth - 240.f, screenHeight - 130.f);
	//m_GunFrame.setFillColor(sf::Color(0, 0, 0, 0));
	m_GunFrame.setOutlineThickness(3.f);
	m_GunFrame.setOutlineColor(sf::Color(77, 76, 78));
}

void UI::Update(float deltaTime)
{
	sf::Vector2i pHp = GConnect->getPlayer()->getHp();
	m_pHp = pHp;
	sf::Vector2i pArmor = GConnect->getPlayer()->getArmor();
	m_pArmor = pArmor;
	sf::Vector2i pExp = GConnect->getPlayer()->getExp();
	sf::Vector2i pAmmo = GConnect->getPlayer()->getCurrentWP()->getAmmo();
	
	m_CoinHud.Update(deltaTime);
	m_CoinText.setString(to_string(GConnect->getPlayer()->getCoin()));
	m_CoinText.setCharacterSize(15.f * m_HudScale.x);
	
	m_HpBar.setTextureRect(sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(m_HpBar.getTexture()->getSize().x * pHp.x / pHp.y, m_HpBar.getTexture()->getSize().y)));
	FOR(i, 0, pHp.y - 2) {
		m_HpCount[i].setPosition(m_HpBar.getPosition().x + (i + 1) * m_HpBar.getTexture()->getSize().x * m_HudScale.x / pHp.y, m_HpBar.getPosition().y);

	}

	m_ArmorBar.setTextureRect(sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(m_ArmorBar.getTexture()->getSize().x * pArmor.x / pArmor.y, m_ArmorBar.getTexture()->getSize().y)));
	FOR(i, 0, pHp.y - 2) {
		m_ArmorCount[i].setPosition(m_ArmorBar.getPosition().x + (i + 1) * m_ArmorBar.getTexture()->getSize().x * m_HudScale.x / pHp.y, m_ArmorBar.getPosition().y);
	}

	m_ExpBar.setTextureRect(sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(m_ExpBar.getTexture()->getSize().x * pExp.x / pExp.y, m_ExpBar.getTexture()->getSize().y)));
	m_ExpText.setString("Lv. " + to_string(GConnect->getPlayer()->getLevel()));
	m_ExpText.setCharacterSize(15.f * m_HudScale.x);

	m_Clip = GConnect->getPlayer()->getCurrentWP()->getClip();
	if (GConnect->getPlayer()->getCurrentWP()->getAmmoType() != m_AmmoType) {
		m_AmmoType = GConnect->getPlayer()->getCurrentWP()->getAmmoType();
		if (m_AmmoType == AmmoType::AMMO_PISTOL || m_AmmoType == AmmoType::AMMO_SHOTGUN) {
			cliptext = (m_AmmoType == AmmoType::AMMO_PISTOL) ? "pistol" : "shotgun";
			m_ClipSize = sf::Vector2f(m_ClipScale.x * 69.f * 0.15f, m_ClipScale.y * 42.f * 0.15f);
			FOR(i, 0, m_Clip.y - 1) {
				m_Clips[i].setPosition(m_ClipPos.x - 5.f * m_ClipScale.x - m_ClipSize.x, m_ClipPos.y - 10.f * m_ClipScale.y - (i+1) * (m_ClipSize.y + 4.f * m_ClipScale.y));
			}
		}
		else if (m_AmmoType == AmmoType::AMMO_SMG) {
			cliptext = "rifle";
			m_ClipSize = sf::Vector2f(m_ClipScale.x * 56.f * 0.15f, m_ClipScale.y * 17.f * 0.10f);
			FOR(i, 0, m_Clip.y - 1) {
				m_Clips[i].setPosition(m_ClipPos.x - 4.5f * m_ClipScale.x - m_ClipSize.x, m_ClipPos.y - 27.f * m_ClipScale.y - (i + 1) * (m_ClipSize.y + 3.f * m_ClipScale.y));
			}
		}
	}
	m_ClipBarSize = sf::Vector2f(m_ClipSize.x * 2, m_Clip.y * m_ClipSize.y + (m_Clip.y + 1) * m_ClipScale.y * 4.f + 20.f * m_ClipScale.y);
	m_ClipBar.setScale(m_ClipBarSize.x / m_ClipBar.getTexture()->getSize().x, m_ClipBarSize.y / m_ClipBar.getTexture()->getSize().y);
	FOR(i, 0, m_Clip.y - 1) {
		if (i < m_Clip.x) m_Clips[i].setTexture(*ASSET->getTexture("GUI/bullet/" + cliptext + "_normal_full"));
		else m_Clips[i].setTexture(*ASSET->getTexture("GUI/bullet/" + cliptext + "_empty"));
		//printf("%f\n", m_ClipSize.x );
		m_Clips[i].setScale(m_ClipSize.x / m_Clips[i].getTexture()->getSize().x, m_ClipSize.y / m_Clips[i].getTexture()->getSize().y);
	}
	m_Ammo.setString(to_string(pAmmo.x) + "/" + to_string(pAmmo.y));
	m_GunFrame.setTexture(ASSET->getTexture("Gun/" + GConnect->getPlayer()->getCurrentWP()->getAssetName()));

}

void UI::Render(sf::RenderWindow* window)
{
	
	window->draw(m_HpBar);
	FOR(i, 0, m_pHp.y - 2) {
		window->draw(m_HpCount[i]);
	}
	window->draw(m_ArmorBar);
	FOR(i, 0, m_pArmor.y - 2) {
		window->draw(m_ArmorCount[i]);
	}
	window->draw(m_ExpBar);
	window->draw(m_ExpText);
	window->draw(m_PHud);
	window->draw(m_Hud);
	window->draw(m_CoinHud);
	window->draw(m_CoinText);
	window->draw(m_Ammo);
	window->draw(m_GunFrame);
	window->draw(m_ClipBar);
	FOR(i, 0, m_Clip.y - 1) {
		window->draw(m_Clips[i]);
	}
}
