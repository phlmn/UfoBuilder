#pragma once

#include <list>
#include <string>
#include <SFML\Graphics.hpp>
#include "StringHelper.h"
#include <Box2D\Box2D.h>

class LevelObject;

class Level
{
private:
	sf::Sprite m_spriteBackground;
	std::list<LevelObject*> m_objects;

public:
	Level();
	~Level();

	void tick(sf::Time elapsedTime);

	void start();
	void pause();
	void stop();

	void addObject(LevelObject* object);
	void removeObject(LevelObject* object);
	std::list<LevelObject*>* getObjects();

	bool save(std::string filename);
	bool load(std::string filename);
};
