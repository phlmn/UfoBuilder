#pragma once

#include <SFML\Graphics.hpp>
#include <SFGUI\SFGUI.hpp>
#include <Box2D\Box2D.h>
#include "Starter.h"

class Starter;

class Game
{
private:
	Starter* m_starter;

	b2World* m_physWorld;
	b2Body* m_bodyTest;
	b2Body* m_bodyGround;

	sf::RenderWindow* m_renderWindow;

	sf::Sprite m_spriteTest;
	sf::Sprite m_spriteBody;

	sfg::SFGUI m_gui;
	sfg::Desktop* m_desktop;

public:
	Game(Starter* starter, sf::RenderWindow* window, sfg::Desktop* desktop);
	~Game();

	void tick(sf::Time elapsedTime);
	void show();
	void hide();
};
