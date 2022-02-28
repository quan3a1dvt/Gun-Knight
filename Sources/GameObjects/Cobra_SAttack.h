#pragma once
#include "IMState.h"
#include "IMob.h"
#include "IPlayer.h"
class Cobra_SAttack :public IMState {
public:
	Cobra_SAttack(IMob* mob);
	void Init();
	void Update(float deltaTime);
	void Render(sf::RenderWindow* window);
	Animation* getSprite();
private:
	IMob* m_mob;
	Animation* m_animation;

};