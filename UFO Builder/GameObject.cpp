#include "GameObject.h"


GameObject::GameObject()
{
	m_objectID = "";
}

GameObject::~GameObject()
{

}

void GameObject::setObjectID(sf::String id)
{
	m_objectID = id;
}

sf::String GameObject::getObjectID()
{
	return m_objectID;
}
