#pragma once

#include <SFML\Graphics.hpp>
#include "StringHelper.h"
#include <Box2D\Box2D.h>

class Game
{
private:
	bool init();
	void tick();
	void cleanup();

	int m_ticks;

	b2World* m_physWorld;
	b2Body* m_bodyTest;
	b2Body* m_bodyGround;

	sf::Clock m_clock;
	sf::RenderWindow* m_window;
	
	sf::Sprite m_spriteTest;
	sf::Sprite m_spriteBody;

	sf::Font m_fontSegoe;

	sf::ConvexShape m_polygon;

	float PI;
	float DEG_TO_RAD;
	float RAD_TO_DEG;

public:
	Game();
	~Game();

	void run();
};

