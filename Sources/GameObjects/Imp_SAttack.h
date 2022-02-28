#pragma once
#include "IMState.h"
#include "IMob.h"
#include "IPlayer.h"
class Imp_SAttack :public IMState {
public:
	Imp_SAttack(IMob* mob);
	void Init();
	void Update(float deltaTime);
	void Render(sf::RenderWindow* window);
	Animation* getSprite();
private:
	IMob* m_mob;
	Animation* m_animation;

};