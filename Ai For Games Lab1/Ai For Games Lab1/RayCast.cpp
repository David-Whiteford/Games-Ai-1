#include "RayCast.h"

RayCast::RayCast()
{
	m_raycastLine[0].color = sf::Color::Red;
	m_raycastLine[1].color = sf::Color::Blue;
}

RayCast::~RayCast()
{
}

void RayCast::setRayValues(sf::Vector2f t_startPosition, sf::Vector2f t_direction, float t_length)
{
	m_positon = t_startPosition;
	m_direction = t_direction;
	m_rayLength = t_length;
}

void RayCast::hit(sf::Vector2f t_targetPosition, float t_targetRadius)
{
	sf::Vector2f endPoint = m_positon + (m_direction * m_rayLength);

	/*if(endPoint.x > t_targetPosition.x - t_targetRadius|| endPoint.y > t_targetPosition.y - t_targetRadius 
		|| endPoint.y < t_targetPosition.y + t_targetRadius)
	{
		m_hit = true;
	}*/
	
	
}

sf::VertexArray RayCast::drawRay()
{
	sf::VertexArray rayCast(sf::LinesStrip, 2);

	if (m_hit){ rayCast[0].color = sf::Color::Red;}
	else{ rayCast[0].color = sf::Color::White; }
	
	rayCast[0].position = m_positon;
	rayCast[1].position = m_positon + (m_direction * (m_rayLength));
	return rayCast;
}
