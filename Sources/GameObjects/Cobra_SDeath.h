#pragma once
#include "IMState.h"
#include "IMob.h"
#include "TiledMap.h"
class Cobra_SDeath :public IMState {
public:
	Cobra_SDeath(IMob* mob);
	void Init();
	void Update(float deltaTime);
	void Render(sf::RenderWindow* window);
	Animation* getSprite();
private:
	IMob* m_mob;
	Animation* m_animation;

};