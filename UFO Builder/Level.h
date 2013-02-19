#pragma once

#include "main.h"

class GameObject;

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

	bool save(sf::String filename);
	bool load(sf::String filename);
};
