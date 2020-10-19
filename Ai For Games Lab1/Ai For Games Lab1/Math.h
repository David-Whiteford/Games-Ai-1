#ifndef MATH_H
#define MATH_H
#include <SFML/Graphics.hpp>
#include <cmath>
class Math
{
public:
	Math();
	sf::Vector2f normalise(sf::Vector2f t_vec);
	float magnitude(sf::Vector2f t_vec);
	float magnitudeSquared(float t_vecX, float t_vecY);
	float length(sf::Vector2f& vec);
	float dot(sf::Vector2f& vec, sf::Vector2f& vec2);
	

};

#endif