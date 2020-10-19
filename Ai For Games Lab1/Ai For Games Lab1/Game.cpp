
#include "Game.h"
#include <iostream>
static double const MS_PER_UPDATE = 10.0;
Game::Game():
	m_window{ sf::VideoMode{ desktop.width, desktop.height, desktop.bitsPerPixel }, "SFML Game" }
{
	init();
	
}


Game::~Game()
{
}


void Game::run()
{
	sf::Clock clock;
	sf::Int32 lag = 0;

	while (m_window.isOpen())
	{
		sf::Time dt = clock.restart();

		lag += dt.asMilliseconds();

		processEvents();

		while (lag > MS_PER_UPDATE)
		{
			update(MS_PER_UPDATE);
			lag -= MS_PER_UPDATE;
		}
		update(MS_PER_UPDATE);

		render();
	}
}


void Game::init()
{
	if (!m_font.loadFromFile("FONTS/ariblk.ttf"))
	{
		std::cout << "error with font file file";
	}
	
	m_text.setString("Press the keys 1 - 5 to change Ai");
	m_text.setFont(m_font);
	m_text.setCharacterSize(25);
	m_text.setFillColor(sf::Color::White);
	int ScreenWidth = desktop.width;
	m_text.setPosition(sf::Vector2f(ScreenWidth,10.0f) - m_textOffset);

	m_player.init();

	m_pursueAi.init();
	m_pursueAi.setCircleRadius(m_player.getCircleRadius());
	m_pursueAi.setPosition();
	
	m_arriveAi.init();
	m_arriveAi.setCircleRadius(m_player.getCircleRadius());
	m_arriveAi.setPosition();

	m_seekAi.init();
	m_seekAi.setCircleRadius(m_player.getCircleRadius());
	m_seekAi.setPosition();
	m_fleeAi.init();
	m_fleeAi.setPosition();
	m_fleeAi.init();
	
	m_wanderAi.init();
	m_wanderAi.setPosition();
	m_wanderAi.init();
		

}

void Game::processEvents()
{
}

void Game::update(double dt)
{
	handleInputs();
	m_player.update(desktop, dt);
	sf::Vector2f playerCentre = sf::Vector2f(m_player.getPosition().x + m_player.getWidth() / 2
		, m_player.getPosition().y + m_player.getHeigth() / 2);
	switch (m_aiState)
	{
	case AiActive::SEEK_PLAYER_AI:
		m_seekAi.update(desktop, dt, playerCentre);
		break;
	case AiActive::WANDER_MAP_AI:
		m_wanderAi.update(desktop, dt, m_player.getPosition());
		break;
	case AiActive::FLEE_AI:
		m_fleeAi.update(desktop, dt, playerCentre);
		break;
	case AiActive::ARRIVE_AI:
		m_arriveAi.update(desktop, dt, playerCentre);
		break;
	case AiActive::PURSUE_AI:
		m_pursueAi.update(desktop, dt, playerCentre);
		break;
	default:
		break;
	}
}

void Game::render()
{
	m_window.clear(sf::Color::Black);
	m_player.render(m_window);
	m_window.draw(m_text);
	switch (m_aiState)
	{
	case AiActive::SEEK_PLAYER_AI:
		m_seekAi.render(m_window);
		break;
	case AiActive::WANDER_MAP_AI:
		m_wanderAi.render(m_window);
		break;
	case AiActive::FLEE_AI:
		m_fleeAi.render(m_window);
		break;
	case AiActive::ARRIVE_AI:
		m_arriveAi.render(m_window);
		break;
	case AiActive::PURSUE_AI:
		m_pursueAi.render(m_window);
		break;
	default:
		break;
	}
	m_window.display();
}

void Game::handleInputs()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
	{
		m_fleeAi.setFlee();
		m_aiState = AiActive::FLEE_AI;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
	{
		m_seekAi.setSeekPlayer();
		m_aiState = AiActive::SEEK_PLAYER_AI;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
	{
		m_wanderAi.setWander();
		m_aiState = AiActive::WANDER_MAP_AI;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4))
	{
		m_arriveAi.setArrive();
		m_aiState = AiActive::ARRIVE_AI;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num5))
	{
		m_pursueAi.setPursue();
		m_aiState = AiActive::PURSUE_AI;
	}

}

