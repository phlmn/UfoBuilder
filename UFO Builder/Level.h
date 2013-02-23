#pragma once

#include <list>
#include <string>
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
#include "Game.h"
#include "tinyxml2.h"

class Level
{
private:
	sf::Sprite m_spriteBackground;
	std::list<GameObject*> m_objects;

public:
	Level();
	~Level();

	void tick(sf::Time elapsedTime);

	void start();
	void pause();
	void stop();

	void addObject(GameObject* object);
	void removeObject(GameObject* object);
	std::list<GameObject*>* getObjects();

	bool save(std::string filename);
	bool load(std::string filename);
};
