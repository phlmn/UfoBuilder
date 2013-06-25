#pragma once

#include <list>
#include <string>
#include <SFML\Graphics.hpp>
#include "StringHelper.h"
#include <Box2D\Box2D.h>
#include "tinyxml2.h"

class LevelObject;
class Ufo;

class Level
{
private:
	std::list<LevelObject*> m_objects;

	sf::RenderWindow* m_renderWindow;

	std::string m_levelID;

	sf::Vector2f m_cameraPos;
	sf::Vector2i m_cameraMoveSpeed;

	Ufo* m_ufo;

public:
	Level(sf::RenderWindow* window);
	~Level();

	void tick(sf::Time elapsedTime);

	void addObject(LevelObject* object);
	void addObject(LevelObject* object, int index);
	void addObject(LevelObject* object, int layer, int index);
	void removeObject(LevelObject* object);
	std::list<LevelObject*>* getObjects();

	bool save(std::string levelID);
	bool load(std::string levelID);

	void setUfo(Ufo* ufo);
	Ufo* getUfo();
};
