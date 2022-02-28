#pragma once
#include "IMState.h"
#include "IMob.h"

class Imp_SRun :public IMState {
public:
	Imp_SRun(IMob* mob);
	void Init();
	void Update(float deltaTime);
	void Render(sf::RenderWindow* window);
	Animation* getSprite();
private:
	IMob* m_mob;
	Animation* m_animation;

};