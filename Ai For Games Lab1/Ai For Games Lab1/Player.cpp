#include "Player.h"

Player::Player()
{
}

Player::~Player()
{
}

int Player::getWidth()
{
	return m_width;
}

int Player::getHeigth()
{
	return m_height;
}

sf::Vector2f Player::getPosition()
{
	sf::Vector2f playerCentre = sf::Vector2f(m_player.getPosition().x - m_shipWidth, 
		m_player.getPosition().y-m_shipHeigth);
	return playerCentre;
}
float Player::getCircleRadius()
{
	return circle.getRadius();
}
void Player::BoundryControl(sf::VideoMode desktop)
{
	if (m_player.getPosition().x >= desktop.width + m_0ffset)
	{
		m_player.setPosition(-50.0f, m_player.getPosition().y);
	}
	else if (m_player.getPosition().x <= 0 - m_0ffset)
	{
		m_player.setPosition(desktop.width, m_player.getPosition().y);
	}

	else if (m_player.getPosition().y >= desktop.height + m_0ffset)
	{
		m_player.setPosition(m_player.getPosition().x, 0);
	}
	else if (m_player.getPosition().y <= 0)
	{
		m_player.setPosition(m_player.getPosition().x, desktop.height);
	}
}
void Player::setPosition(sf::Vector2f t_position)
{
}

void Player::playerMovement(double dt)
{
	m_newPosX = m_player.getPosition().x + cos(m_rotation * DEG_TO_RAD) * m_speed * (dt / 1000);
	m_newPosY = m_player.getPosition().y + sin(m_rotation * DEG_TO_RAD) * m_speed * (dt / 1000);
	m_player.setPosition(m_newPosX, m_newPosY);
	m_player.setRotation(m_rotation);
	
	

}
void Player::increaseSpeed()
{
	//increases the speed
	m_previousSpeed = m_speed;
	if (m_speed < 50.0f)
	{
		m_speed += .001f;
	}
}

void Player::decreaseSpeed()
{
	//decreases the speed
	m_previousSpeed = m_speed; 
	if (m_speed > -50.0f)
	{
		m_speed -= .001f;
	}
}

void Player::increaseRotation()
{
	//increase rotation
	m_previousRotation = m_rotation;
	m_rotation += .01f;
	
	if (m_rotation == 360.0)
	{
		m_rotation = 0;
	}
}

void Player::decreaseRotation()
{
	//decrease rotation
	m_previousRotation = m_rotation;
	m_rotation -= .01f;
	
	if (m_rotation == 0.0)
	{
		m_rotation = 359.0f;
	}
}

double Player::getSpeed()
{
	return m_speed;
}


void Player::init()
{
	setUpPlayer();
}



void Player::update(sf::VideoMode desktop, double dt)
{
	handleKeyInput();
	playerMovement(dt);
	BoundryControl(desktop);
	




	circle.setPosition(sf::Vector2f(m_player.getPosition().x - m_shipWidth, m_player.getPosition().y - m_shipHeigth));
}

void Player::setUpPlayer()
{
	
	if (!texture.loadFromFile("IMAGES//rightPlayer.png"))
	{
		// error...
	}
	
	m_player.setTexture(texture);
	m_player.setPosition(sf::Vector2f(10.f, 500.f)); 
	m_player.setScale(0.5f, 0.5f);
	m_player.setOrigin(m_width / 2 , m_height / 2);



	circle.setRadius(75);
	circle.setOutlineColor(sf::Color::Red);
	circle.setOutlineThickness(2);
	circle.setPosition(sf::Vector2f(m_player.getPosition().x - m_shipWidth, m_player.getPosition().y - m_shipHeigth));
}

void Player::render(sf::RenderWindow& t_window)
{
	t_window.draw(circle);
	t_window.draw(m_player);
}

void Player::handleKeyInput()
{
	//key inputs the keys on the keyboard
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		increaseRotation();
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		decreaseRotation();
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		increaseSpeed();
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		decreaseSpeed();
	}
}
