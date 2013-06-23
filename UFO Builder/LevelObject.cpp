#include "LevelObject.h"

#include "CatalogObject.h"

using namespace std;
using namespace tinyxml2;

LevelObject::LevelObject()
{
	m_sprite = NULL;
	m_position = sf::Vector2f();
	m_scale = 1.0f;
	m_opacity = 1.0f;
	m_angle = 0.0f;
	m_layer = 0;
	m_objectID = 0;
	m_objectType = "";
	m_category = "";
}

LevelObject::LevelObject(XMLElement* element)
{
	m_layer = atoi(element->Attribute("layer"));

	m_objectID = 0;
	m_objectType = "";
	m_category = "";
	m_sprite = NULL;

	m_position = sf::Vector2f((float)atof(element->Attribute("x")), (float)atof(element->Attribute("y")));

	m_angle = (float)atof(element->Attribute("angle"));
	m_scale = (float)atof(element->Attribute("scale"));
	m_opacity = (float)atof(element->Attribute("opacity"));

	CatalogObject catObj;
	if(catObj.load(element->Attribute("id")))
		getDataFromCatalogObject(catObj);
}

LevelObject::LevelObject(CatalogObject gameObject)
{
	m_position = sf::Vector2f();
	m_scale = 1.0f;
	m_opacity = 1.0f;
	m_angle = 0.0f;
	m_layer = 0;
	m_objectID = 0;
	m_objectType = "";
	m_category = "";
	m_sprite = NULL;

	getDataFromCatalogObject(gameObject);
}

void LevelObject::getDataFromCatalogObject(CatalogObject catObj)
{
	m_sprite = NULL;
	m_name = catObj.getName();
	m_category = catObj.getCategory();
	m_objectType = catObj.getObjectID();

	if(!m_imageFile.isEmpty())
	{
		sf::Texture texture;
		texture.loadFromFile(string("objects/images/") + m_imageFile);

		m_sprite = new sf::Sprite();
		m_sprite->setTexture(texture);
	}

	b2World* world = new b2World(b2Vec2(0, 9.81f));
	b2Body* body = world->CreateBody(&m_bodyDef);

	b2FixtureDef fixDef = b2FixtureDef();
	fixDef.friction = 1;
	fixDef.density = 1;
	
	b2ChainShape* shape = new b2ChainShape();

	b2Vec2 vertices[7];
	vertices[0] = b2Vec2(0, 0);
	vertices[1] = b2Vec2(0, 0);
	vertices[2] = b2Vec2(0, 0);
	vertices[3] = b2Vec2(0, 0);
	vertices[4] = b2Vec2(0, 0);
	vertices[5] = b2Vec2(0, 0);
	vertices[6] = b2Vec2(0, 0);
	shape->CreateChain(vertices, 7);

	

	fixDef.shape = shape;

	b2Fixture* fixture = body->CreateFixture(&fixDef);
}

LevelObject::LevelObject(CatalogObject gameObject, int layer, sf::Vector2f position, float scale, float opacity, float angle)
{
	m_layer = layer;
	m_position = position;
	m_scale = scale;
	m_opacity = opacity;
	m_angle = angle;

	sf::Texture texture;
	texture.loadFromFile(string("objects/images/") + gameObject.getImageFile());

	m_sprite = new sf::Sprite();
	m_sprite->setTexture(texture);
}

LevelObject::~LevelObject()
{
	if(m_sprite != NULL) delete m_sprite;
}

void LevelObject::tick(sf::Time elapsedTime)
{
	
}


void LevelObject::setLayer(int layer)
{
	m_layer = layer;
}

int LevelObject::getLayer()
{
	return m_layer;
}

void LevelObject::setPosition(sf::Vector2f position)
{
	m_position = position;
}

sf::Vector2f LevelObject::getPosition()
{
	return m_position;
}

void LevelObject::setScale(float scale)
{
	m_scale = scale;
}

float LevelObject::getScale()
{
	return m_scale;
}

void LevelObject::setOpacity(float opacity)
{
	m_opacity = opacity;
}

float LevelObject::getOpacity()
{
	return m_opacity;
}

void LevelObject::setAngle(float angle)
{
	m_angle = angle;
}

float LevelObject::getAngle()
{
	return m_angle;
}

void LevelObject::setName(std::string name)
{
	m_name = name;
}

std::string LevelObject::getName()
{
	return m_name;
}

void LevelObject::setObjectType(std::string id)
{
	m_objectType = id;
}

std::string LevelObject::getObjectType()
{
	return m_objectType;
}

void LevelObject::setObjectID(int id)
{
	m_objectID = id;
}

int LevelObject::getObjectID()
{
	return m_objectID;
}

void LevelObject::setObjectCategory(std::string cat)
{
	m_category = cat;
}

std::string LevelObject::getObjectCategory()
{
	return m_category;
}
