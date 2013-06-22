#include "Level.h"
#include "LevelObject.h"

using namespace std;
using namespace tinyxml2;

Level::Level()
{
	m_objects.clear();
}


Level::~Level()
{

}

void Level::tick(sf::Time elapsedTime)
{
	list<LevelObject*>::iterator pos = m_objects.begin();
	while(pos != m_objects.end())
	{
		(*pos)->tick(elapsedTime);
	}
}

void Level::start()
{

}

void Level::pause()
{

}

void Level::stop()
{

}

void Level::addObject(LevelObject* object)
{
	m_objects.push_back(object);
}

void Level::removeObject(LevelObject* object)
{
	m_objects.remove(object);
}

std::list<LevelObject*>* Level::getObjects()
{
	return &m_objects;
}

std::string Level::getLevelID()
{
	return m_levelID;
}

bool Level::save(std::string filename)
{
	return false;
}

bool Level::load(std::string levelID)
{
	XMLDocument doc;

	m_objects.clear();

	// load XML file
	if(doc.LoadFile(("objects\\" + levelID + ".xml").c_str()) != XML_SUCCESS)
		return false;

	// get object node
	
	XMLElement* levelNode = doc.RootElement();
	if(levelNode == NULL)
		return false;

	// parse attributes
	if(levelNode->Attribute("id") == NULL)
		return false;
	m_levelID = levelNode->Attribute("id");

	if(levelNode->Attribute("bg") == NULL)
		return false;
	m_bg = levelNode->Attribute("bg");

	XMLElement* objectNode = levelNode->FirstChildElement("object");

	while(objectNode != NULL)
	{
		LevelObject* obj = new LevelObject(objectNode);
		m_objects.push_back(obj);

		objectNode = objectNode->NextSiblingElement("object");
	}

	return true;
}
