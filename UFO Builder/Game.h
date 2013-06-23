#pragma once

#include <SFML\Graphics.hpp>
#include <Box2D\Box2D.h>
#include "Starter.h"
#include "UfoEditor.h"
#include "Level.h"

class Game
{
private:
	Starter* m_starter;
	UfoEditor* m_ufoEditor;
	Level* m_level;

	sf::RenderWindow* m_renderWindow; // wrapper for sf::Window, allows easy 2D rendering

	void resize();

public:
	Game(Starter* starter, sf::RenderWindow* window);
	~Game();

	void tick(sf::Time elapsedTime);

	UfoEditor* getUfoEditor();
	Level* getLevel();
};
