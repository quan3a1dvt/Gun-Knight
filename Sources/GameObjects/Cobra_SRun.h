#pragma once
#include "IMState.h"
#include "IMob.h"

class Cobra_SRun :public IMState {
public:
	Cobra_SRun(IMob* mob);
	void Init();
	void Update(float deltaTime);
	void Render(sf::RenderWindow* window);
	Animation* getSprite();
private:
	IMob* m_mob;
	Animation* m_animation;

};