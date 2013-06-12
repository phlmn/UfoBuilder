#pragma once

#include <SFML\Graphics.hpp>
#include <Box2D\Box2D.h>
#include "Starter.h"
#include "Level.h"

class Game
{
private:
	Starter* m_starter;
	Level* m_level;

	b2World* m_physWorld;
	b2Body* m_bodyTest;
	b2Body* m_bodyGround;

	sf::RenderWindow* m_renderWindow;

	sf::Sprite m_spriteTest;
	sf::Sprite m_spriteBody;

	void resize();

public:
	Game(Starter* starter, sf::RenderWindow* window);
	~Game();

	void tick(sf::Time elapsedTime);
};
