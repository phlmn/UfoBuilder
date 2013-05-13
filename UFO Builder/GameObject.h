#pragma once

#include <SFML\Graphics.hpp>

class GameObject
{
protected:
	sf::String m_objectID;
	
public:
	GameObject();
	~GameObject();

	void setObjectID(sf::String id);
	sf::String getObjectID();
};
