#include "Math.h"

Math::Math()
{
}

sf::Vector2f Math::normalise(sf::Vector2f t_vec)
{
	float mag = magnitude(t_vec);
	if (abs(mag) < 1e-9)
	{
		t_vec.x = 0;
		t_vec.y = 0;
	}
	else
	{
		t_vec.x /= mag;
		t_vec.y /= mag;
	}
	return t_vec;
}

float Math::magnitude(sf::Vector2f t_vec)
{
	float x = t_vec.x;
	float y = t_vec.y;
	float val = magnitudeSquared(x, y);
	val =  sqrt(val);
	return val;
	
}

float Math::magnitudeSquared(float t_vecX,float t_vecY)
{
	return (t_vecX * t_vecX + t_vecY* t_vecY);
}

float Math::length(sf::Vector2f& vec)
{
	return sqrt(dot(vec , vec));
}

float Math::dot(sf::Vector2f& vec, sf::Vector2f& vec2)
{
	return vec.x * vec2.x + vec.y * vec2.y;
}
