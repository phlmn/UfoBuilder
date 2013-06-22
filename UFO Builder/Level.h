#pragma once

#include <list>
#include <string>
#include <SFML\Graphics.hpp>
#include "StringHelper.h"
#include <Box2D\Box2D.h>
#include "tinyxml2.h"

class LevelObject;

class Level
{
private:
	sf::Sprite m_spriteBackground;
	std::list<LevelObject*> m_objects;

	std::string m_levelID;
	std::string m_bg;

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

	std::string getLevelID();
	bool save(std::string levelID);
	bool load(std::string levelID);
};
