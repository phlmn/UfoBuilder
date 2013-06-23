#pragma once

#include <list>
#include <SFML\Graphics.hpp>
#include "UfoPart.h"

class Ufo
{
private:
	std::list<UfoPart*> m_parts;

	b2World* m_physWorld; // manage all physics entities and dynamic simulation
	// rigid bodys
	b2Body* m_bodyTest;
	b2Body* m_bodyGround;

	sf::RenderWindow* m_renderWindow; // wrapper for sf::Window, allows easy 2D rendering
	
	// drawable representation of a texture -> allows to easily display a texture on a render target
	sf::Sprite m_spriteBody;

	sf::Vector2i m_mousePosition;
	sf::Vector2i m_lastClick;
	sf::Vector2i m_difference;
	bool m_mouseIsPressed;

	int m_direcction;
	int m_acceleration;

	float m_sensitivity;

	bool isSelected(const sf::Sprite object);
public:
	Ufo(sf::RenderWindow* window);
	~Ufo();

	void tick(sf::Time elapsedTime);

	void addPart();
	void removePart();

	void resize(float scale);

	sf::Vector2i getMousePosition();
	sf::Vector2i getLastClick();
};
