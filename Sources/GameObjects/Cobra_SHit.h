#pragma once
#include "IMState.h"
#include "IMob.h"

class Cobra_SHit :public IMState {
public:
	Cobra_SHit(IMob* mob);
	void Init();
	void Update(float deltaTime);
	void Render(sf::RenderWindow* window);
private:
	IMob* m_mob;
	Animation* m_animation;

};