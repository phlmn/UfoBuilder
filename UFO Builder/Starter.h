#pragma once

#include <list>
#include <string>
#include <sstream>
#include <SFML\Graphics.hpp>
#include "StringHelper.h"
#include <Box2D\Box2D.h>
#include "GameObject.h"
#include "LevelEditor.h"
#include "Ufo.h"
#include "UfoEditor.h"
#include "UfoPart.h"
#include "UfoCarriage.h"
#include "UfoCockpit.h"
#include "UfoEngine.h"
#include "UfoFuelTank.h"
#include "Level.h"
#include "Game.h"
#include <SFGUI\SFGUI.hpp>

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

	sfg::SFGUI m_sfgui;
sfg::Desktop desktop;


	float PI;
	float DEG_TO_RAD;
	float RAD_TO_DEG;

public:
	Starter();
	~Starter();

	void run();
};
