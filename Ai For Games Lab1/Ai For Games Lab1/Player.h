#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include <iostream>

class Player
{
public:
	Player();
	~Player();
	
	sf::Texture texture;
	sf::Sprite m_player;
	float m_velocity = 0.01f;
	float m_rotationVel = 0.5f;
	int m_width = 180;
	int m_height = 172;
	int m_0ffset = 80;
	sf::Vector2f movementVec;
	int m_shipHeigth = 86;
	int m_shipWidth = 90;
	float m_newPosX;
	float m_newPosY;
	sf::CircleShape circle;
	double m_previousRotation{ 0.0 };
	double  m_previousSpeed{ 0.0 };
	double m_speed{ 0.0 };
	double m_rotation{ 0.0 };
	int getWidth();
	int getHeigth();
	double const DEG_TO_RAD = 3.1415926 / 180.0f;
	sf::Vector2f getPosition();
	void setPosition(sf::Vector2f t_position);
	void playerMovement(double dt);
	float getCircleRadius();
	void BoundryControl(sf::VideoMode desktop);
	void init();
	void update(sf::VideoMode desktop, double dt);
	void setUpPlayer();
	void render(sf::RenderWindow& t_window);
	void handleKeyInput();
	void increaseSpeed();
	void decreaseSpeed();
	void increaseRotation();
	void decreaseRotation();
	double getSpeed();
	
private:

};
#endif

