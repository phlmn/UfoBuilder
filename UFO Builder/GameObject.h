#pragma once

#include <SFML\Graphics.hpp>
#include <Box2D\Box2D.h>

class GameObject
{
protected:
	sf::String m_objectID;
	sf::String m_name;
	sf::String m_imageFile;

	b2BodyDef m_bodyDef;
	
public:
	GameObject();
	~GameObject();

	void setObjectID(sf::String id);
	sf::String getObjectID();
};
