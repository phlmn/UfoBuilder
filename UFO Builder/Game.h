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

	b2World* m_physWorld; // manage all physics entities and dynamic simulation
	// rigid bodys
	b2Body* m_bodyTest;
	b2Body* m_bodyGround;

	sf::RenderWindow* m_renderWindow; // wrapper for sf::Window, allows easy 2D rendering

	// drawable representation of a texture -> allows to easily display a texture on a render target
	sf::Sprite m_spriteTest;
	sf::Sprite m_spriteBody;

	sf::Vector2i m_mousePosition;
	sf::Vector2i m_lastClick;

	void resize();

	bool isSelected(const sf::Sprite object);

public:
	Game(Starter* starter, sf::RenderWindow* window);
	~Game();

	void tick(sf::Time elapsedTime);
	sf::Vector2i getMousePosition();
	sf::Vector2i getLastClick();
};
