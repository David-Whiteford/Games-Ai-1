#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include "Player.h"
#include "AI.h"
class Game
{
public:
	Game();
	~Game();
	
	void run();


private:
	void init();
	void processEvents();
	void update(double dt);
	void render();
	void handleInputs();
	enum class AiActive
	{
		WANDER_MAP_AI,
		SEEK_PLAYER_AI,
		FLEE_AI,
		PURSUE_AI,
		ARRIVE_AI
	} m_aiState;
	sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
	Player m_player;
	AI m_seekAi;
	AI m_fleeAi;
	AI m_wanderAi;
	AI m_pursueAi;
	AI m_arriveAi;
	sf::Font m_font;
	sf::Text m_text;
	sf::Vector2f m_textOffset = sf::Vector2f(500.0f, 0.0f);

	sf::RenderWindow m_window; // main SFML window

};
#endif