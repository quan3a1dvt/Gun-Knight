#pragma once
#include <SFML/Graphics.hpp>

class HitCircle :public sf::CircleShape {
public:
    HitCircle(int radius);
    HitCircle();
    ~HitCircle();
    void Init(float velocity);

    float GetVelocity();
private:
    float m_velocity;
};