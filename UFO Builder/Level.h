#pragma once
#include "Game.h"

class Level
{
private:
	sf::Sprite m_spriteBackground;
public:
	Level();
	~Level();

	void tick(sf::Time elapsedTime);
};
