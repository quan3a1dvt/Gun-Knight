#pragma once
#include <SFML/Graphics.hpp>

class HitBox :public sf::RectangleShape {
public:
    HitBox(sf::Vector2i size);
    HitBox();
    ~HitBox();
    void Init(float velocity);

    float GetVelocity();
private:
    float m_velocity;
};