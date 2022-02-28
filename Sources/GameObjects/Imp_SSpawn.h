#pragma once
#include "IMState.h"
#include "IMob.h"

class Imp_SSpawn :public IMState {
public:
	Imp_SSpawn(IMob* mob);
	void Init();
	void Update(float deltaTime);
	void Render(sf::RenderWindow* window);
	Animation* getSprite();
private:
	IMob* m_mob;
	Animation* m_animation;

};