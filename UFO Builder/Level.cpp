#include "Level.h"
#include "LevelObject.h"
#include "Ufo.h"

using namespace std;
using namespace tinyxml2;

Level::Level(sf::RenderWindow* window)
{
	m_renderWindow = window;
	m_objects.clear();
	m_ufo = NULL;

	m_levelID = "";
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
		pos++;
	}

	if(m_ufo) m_ufo->tick(elapsedTime);
}

void Level::start()
{
	if(m_levelID == "")
	{
		load("test");
	}

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

bool Level::save(std::string filename)
{
	XMLDocument doc;

	// create level node
	XMLElement* levelNode = doc.NewElement("level");
	if(levelNode == NULL)
		return false;

	// set attributes
	levelNode->SetAttribute("id", m_levelID.c_str());
	levelNode->SetAttribute("name", filename.c_str());

	list<LevelObject*>::iterator pos = m_objects.begin();
	while(pos != m_objects.end())
	{
		// create object node
		XMLElement* objectNode = doc.NewElement("object");

		objectNode->SetAttribute("id", (*pos)->getObjectType().c_str());
		objectNode->SetAttribute("x", (*pos)->getPosition().x);
		objectNode->SetAttribute("y", (*pos)->getPosition().y);
		objectNode->SetAttribute("layer", (*pos)->getLayer());
		objectNode->SetAttribute("opacity", (*pos)->getOpacity());
		objectNode->SetAttribute("angle", (*pos)->getAngle());

		levelNode->InsertEndChild(objectNode);

		pos++;
	}

	doc.InsertEndChild(levelNode);

	if(doc.SaveFile(("saves\\" + filename + ".xml").c_str()) != XML_SUCCESS)
		return false;

	return true;
}

bool Level::load(std::string levelID)
{
	m_levelID = levelID;

	XMLDocument doc;

	m_objects.clear();

	// load XML file
	if(doc.LoadFile(("saves/" + levelID + ".xml").c_str()) != XML_SUCCESS)
		return false;

	// get object node
	
	XMLElement* levelNode = doc.RootElement();
	if(levelNode == NULL)
		return false;

	// parse attributes
	if(levelNode->Attribute("id") == NULL)
		return false;
	m_levelID = levelNode->Attribute("id");

	XMLElement* objectNode = levelNode->FirstChildElement("object");

	while(objectNode != NULL)
	{
		LevelObject* obj = new LevelObject(objectNode);
		obj->setRenderWindow(m_renderWindow);
		m_objects.push_back(obj);

		objectNode = objectNode->NextSiblingElement("object");
	}

	return true;
}

void Level::setUfo(Ufo* ufo)
{
	m_ufo = ufo;
}

Ufo* Level::getUfo()
{
	return m_ufo;
}
