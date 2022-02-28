#include <SFML/Graphics.hpp>

class Animation :public sf::Sprite {
public:
	Animation();
	Animation(sf::Texture &texture, sf::Vector2i frameNum, float frameTime);
	void CalRectSize();
	void CalRectPos();
	void ApplyRect();
	sf::Vector2i GetRectSize();
	void Update(float deltaTime);
	void Reset(sf::Texture& texture, sf::Vector2i frameNum, float frameTime);
	bool Play(float deltaTime);
private:
	sf::Vector2i m_frameNum;
	sf::Vector2i m_currentFrame;
	sf::Vector2i m_rectPos;
	sf::Vector2i m_rectSize;
	
	sf::IntRect m_rect;

	float m_frameTime;
	float m_currentTime;


};

