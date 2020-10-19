#ifndef AI_H
#define AI_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Player.h"
#include "RayCast.h"
#include "Math.h"
class AI
{
public:
	AI();
	~AI();
	Math m_math;

	sf::Vector2f getPosition();
	void setPosition();
	void getSteering(sf::Vector2f t_target);
	void setCircleRadius(float t_radius);
	void setPosition(sf::Vector2f t_position);
	void kinematicWander(float dt);
	void directionToFace(sf::Vector2f t_target);
	void align();
	void kinematicSeek(sf::Vector2f m_playerPos,double dt);
	void kinematicArrive(sf::Vector2f m_playerPos, float dt);
	void kinematicFlee(sf::Vector2f m_playerPos, double dt);
	void init();
	void BoundryControl(sf::VideoMode desktop);
	void setWander();
	void setSeekPlayer();
	void setFlee();
	void setArrive();
	void setPursue();
	void update(sf::VideoMode desktop, double dt , sf::Vector2f t_playerPos);
	void setUpAi();
	void pursue(sf::Vector2f t_target, double dt);
	void evade(sf::Vector2f t_target, double dt);
	float getNewOrientation(float t_currentOrientation, sf::Vector2f t_velocity);
	void render(sf::RenderWindow& t_window);
	void setTarget(sf::Vector2f t_target);
	float mapToRange(float t_rotation);
private:
	sf::Font m_font;
	sf::Text m_text;
	sf::Vector2f m_textOffset = sf::Vector2f(25.0f, 0.0f);
	RayCast m_rayCast;
	sf::Vector2f m_wanderOffset = sf::Vector2f(10.0f,10.0f);
	float m_wanderRadius = 50.0f;
	float m_wanderRate = 1.25f;
	float m_wanderOrientation = 0.0f;
	float m_wanderMaxAccel = 0.1f;
	float m_wanderTargetOrientation = 0.0f;
	
	sf::Vector2f m_direction;
	sf::Texture texture;
	sf::Sprite m_ai;
	
	int m_radius = 0;
	float m_timeToTarget = 0.25f;
	float MaxSpeed = 6.0f;
	
	float m_maxAcelleration = 0.2f;
	int m_0ffset = 80;
	float m_maxRotation = 90.0f;
	float m_maxTimePrediction = 10.0f;
	float m_timePrediction = 0.0f;
	float m_maxAngular = 10.0f;
	float m_maxAngularAcc = 0.1f;
	float m_arrivalRadius = 0.0f;
	float m_slowRadius = 0.0f;
	Player m_player;
	float m_targetSpeed = 0.0f;
	enum class EnemyBehaviour
	{
		WANDER_MAP,
		SEEK_PLAYER,
		FLEE,
		PURSUE,
		ARRIVE

	} m_enemyBehaviour;
	
	struct Kinematic
	{
		sf::Vector2f position;
		float orientation;
		sf::Vector2f velocity;
		float rotation;
		sf::Vector2f direction;
		float distance;
		float speed;

	} m_aiVals;
	//Stores the values of the target
	struct Target
	{
		sf::Vector2f position;
		float orientation;
		sf::Vector2f velocity;
		float rotation;
		sf::Vector2f direction;
		float distance;
		float speed;
		float radius;

	} m_targetVals,m_newTargetVals , m_arriveTargetVals;

	struct SteeringOutput
	{
		sf::Vector2f linear;
		float angular;
		
	} steering;
	SteeringOutput steeringWander;

};
#endif