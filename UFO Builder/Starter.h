#pragma once

#include "main.h"

#ifndef STARTER_H
#define STARTER_H

class Starter
{
private:
	bool init();
	void tick();
	void cleanup();

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
	Starter();
	~Starter();

	void run();
};

#endif
