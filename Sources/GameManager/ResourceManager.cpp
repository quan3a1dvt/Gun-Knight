#include "ResourceManager.h"

ResourceManager::ResourceManager()
{
	m_Path = "assets/";
	m_TexturePath = m_Path + "Textures/";
	m_FontPath = m_Path + "Fonts/";
	m_SoundPath = m_Path + "Sounds/";
	m_allowSound = true;
}

ResourceManager::~ResourceManager()
{
	for (auto it : m_MapTexture) {
		if (it.second != nullptr) {
			delete it.second;
		}
	}
	m_MapTexture.clear();

	for (auto it : m_MapFont) {
		if (it.second != nullptr) {
			delete it.second;
		}
	}
	m_MapFont.clear();

}

void ResourceManager::addTexture(string name)
{
	sf::Texture* texture = new sf::Texture();
	texture->loadFromFile(m_TexturePath + name + ".png");

	auto it = m_MapTexture.find(name);
	if (it != m_MapTexture.end()) {
		return;
	}
	m_MapTexture.insert(pair<string, sf::Texture*>(name, texture));
}

void ResourceManager::removeTexture(string name)
{
	auto it = m_MapTexture.find(name);
	if (it == m_MapTexture.end()) {
		return;
	}
	if (it->second != nullptr) delete it->second;
	m_MapTexture.erase(it);
}

sf::Texture* ResourceManager::getTexture(string name)
{
	auto it = m_MapTexture.find(name);
	if (it != m_MapTexture.end()) {
		return it->second;
	}
	sf::Texture* texture = new sf::Texture();;
	texture->loadFromFile(m_TexturePath + name + ".png");
	m_MapTexture.insert(pair<string, sf::Texture*>(name, texture));
	//texture->setSmooth(true);
	return texture;
}

void ResourceManager::addFont(string name)
{
	sf::Font* font = new sf::Font();
	font->loadFromFile(m_TexturePath + name + ".TTF");

	auto it = m_MapFont.find(name);
	if (it != m_MapFont.end()) {
		return;
	}
	m_MapFont.insert(pair<string, sf::Font*>(name, font));
}

void ResourceManager::removeFont(string name)
{
	auto it = m_MapFont.find(name);
	if (it == m_MapFont.end()) {
		return;
	}
	if (it->second != nullptr) delete it->second;
	m_MapFont.erase(it);
}

sf::Font* ResourceManager::getFont(string name)
{
	auto it = m_MapFont.find(name);
	if (it != m_MapFont.end()) {
		return it->second;
	}
	sf::Font* font = new sf::Font();;
	font->loadFromFile(m_FontPath + name + ".TTF");
	m_MapFont.insert(pair<string, sf::Font*>(name, font));
	return font;
}

void ResourceManager::addSound(string name)
{
	sf::Sound* sound = new sf::Sound();
	sf::SoundBuffer* buffet = new sf::SoundBuffer();
	buffet->loadFromFile(m_SoundPath + name + ".wav");
	sound->setBuffer(*buffet);

	auto it = m_MapSound.find(name);
	if (it != m_MapSound.end()) {
		return;
	}
	m_MapSound.insert(pair<string, sf::Sound*>(name, sound));
}

void ResourceManager::removeSound(string name)
{
	auto it = m_MapSound.find(name);
	if (it == m_MapSound.end()) {
		return;
	}
	if (it->second != nullptr) delete it->second;
	m_MapSound.erase(it);
}

sf::Sound* ResourceManager::getSound(string name)
{
	auto it = m_MapSound.find(name);
	if (it != m_MapSound.end()) {
		return it->second;
	}
	sf::Sound* sound = new sf::Sound();
	sf::SoundBuffer* buffet = new sf::SoundBuffer();
	buffet->loadFromFile(m_SoundPath + name + ".wav");
	sound->setBuffer(*buffet);
	m_MapSound.insert(pair<string, sf::Sound*>(name, sound));
	return sound;
}

void ResourceManager::addMusic(string name)
{
	sf::Music* music = new sf::Music();
	music->openFromFile(m_SoundPath + name + ".wav");

	auto it = m_MapFont.find(name);
	if (it != m_MapFont.end()) {
		return;
	}
	m_MapMusic.insert(pair<string, sf::Music*>(name, music));
}

void ResourceManager::removeMusic(string name)
{
	auto it = m_MapMusic.find(name);
	if (it == m_MapMusic.end()) {
		return;
	}
	if (it->second != nullptr) delete it->second;
	m_MapMusic.erase(it);
}

sf::Music* ResourceManager::getMusic(string name)
{
	auto it = m_MapMusic.find(name);
	if (it != m_MapMusic.end()) {
		return it->second;
	}
	sf::Music* music = new sf::Music();
	music->openFromFile(m_SoundPath + name + ".wav");
	m_MapMusic.insert(pair<string, sf::Music*>(name, music));
	return music;
}

void ResourceManager::playMusic(string name)
{
	if (m_allowSound) ASSET->getMusic(name)->play();
}

void ResourceManager::playSound(string name)
{
	if (m_allowSound) ASSET->getSound(name)->play();
}

void ResourceManager::setAllowSound(bool allow)
{
	m_allowSound = allow;
}