#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <queue>
class RayCast
{
public:
	RayCast();
	~RayCast();
	void setRayValues(sf::Vector2f t_startPosition, sf::Vector2f t_direction, float t_length);
	void hit(sf::Vector2f t_targetPosition, float t_targetRadius);
	sf::VertexArray drawRay();


private:
	sf::Vector2f m_direction;
	sf::Vector2f m_positon;
	float m_rayLength = 0.0f;
	bool m_hit = false;
	sf::Vertex m_raycastLine[2];
};