#pragma once
#include <map>
#include <list>
#include <queue>
#include <stack>
#include <string>
#include "../GameObjects/GameButton.h"
#include "../GameObjects/Animation.h"
#include "Collision.h"
#include "Random.h"
#include "../GameStateManager/GameStateMachine.h"
#include "GameConnector.h"
#include "../GameConfig.h"
#include "SFML/Audio.hpp"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <math.h>

#define ASSET ResourceManager::GetInstance()
using namespace std;
class ResourceManager :public CSingleton<ResourceManager> {
public:
	ResourceManager();
	~ResourceManager();
	
	void addTexture(string name);
	void removeTexture(string name);
	sf::Texture* getTexture(string name);

	void addFont(string name);
	void removeFont(string name);
	sf::Font* getFont(string name);

	void addSound(string name);
	void removeSound(string name);
	sf::Sound* getSound(string name);

	void addMusic(string name);
	void removeMusic(string name);
	sf::Music* getMusic(string name);

	void playMusic(string name);
	void playSound(string name);
	void setAllowSound(bool allow);




private:
	map<string, sf::Texture*> m_MapTexture;
	map<string, sf::Font*> m_MapFont;
	map<string, sf::Sound*> m_MapSound;
	map<string, sf::Music*> m_MapMusic;

	string m_Path;
	string m_TexturePath;
	string m_FontPath;
	string m_SoundPath;

	bool m_allowSound;
};