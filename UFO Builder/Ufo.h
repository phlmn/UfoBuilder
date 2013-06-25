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
	sf::Sprite* m_spriteBody;

	sf::Vector2f m_cameraPos;
	bool m_mouseIsPressed;

	float m_sensitivity;

	bool isSelected(const sf::Sprite* object);
public:
	Ufo(sf::RenderWindow* window);
	~Ufo();

	void tick(sf::Time elapsedTime);

	void addPart();
	void removePart();

	void resize(float scale);

	void setCameraPos(sf::Vector2f pos);
	sf::Vector2f getCameraPos();

	void setPos(sf::Vector2f pos);
	sf::Vector2f getPos();
};
