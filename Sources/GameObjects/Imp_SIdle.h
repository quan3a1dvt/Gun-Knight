#pragma once
#include "IMState.h"
#include "IMob.h"

class Imp_SIdle :public IMState {
public:
	Imp_SIdle(IMob* mob);
	void Init();
	void Update(float deltaTime);
	void Render(sf::RenderWindow* window);
	Animation* getSprite();
private:
	IMob* m_mob;
	Animation* m_animation;

};