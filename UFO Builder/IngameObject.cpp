#include "IngameObject.h"

using namespace std;

IngameObject::IngameObject() : GameObject()
{
	m_position = sf::Vector2f();
	m_scale = 1.0f;
	m_opacity = 1.0f;
	m_angle = 0.0f;
	m_layer = 0;
	m_sprite = NULL;
}

IngameObject::IngameObject(GameObject gameObject)
{
	m_position = sf::Vector2f();
	m_scale = 1.0f;
	m_opacity = 1.0f;
	m_angle = 0.0f;
	m_layer = 0;
	m_sprite = NULL;

	if(!m_imageFile.isEmpty())
	{
		sf::Texture texture;
		texture.loadFromFile(string("objects\\images\\") + m_objectID + m_imageFile);

		m_sprite = new sf::Sprite();
		m_sprite->setTexture(texture);
	}
}

IngameObject::IngameObject(GameObject gameObject, int layer, sf::Vector2f position, float scale, float opacity, float angle)
{
	m_layer = layer;
	m_position = position;
	m_scale = scale;
	m_opacity = opacity;
	m_angle = angle;

	sf::Texture texture;
	texture.loadFromFile(string("objects\\") + m_objectID + string("\\body.png"));

	m_sprite = new sf::Sprite();
	m_sprite->setTexture(texture);
}

IngameObject::~IngameObject()
{
	if(m_sprite != NULL) delete m_sprite;
}

void IngameObject::setLayer(int layer)
{
	m_layer = layer;
}

int IngameObject::getLayer()
{
	return m_layer;
}

void IngameObject::setPosition(sf::Vector2f position)
{
	m_position = position;
}

sf::Vector2f IngameObject::getPosition()
{
	return m_position;
}

void IngameObject::setScale(float scale)
{
	m_scale = scale;
}

float IngameObject::getScale()
{
	return m_scale;
}

void IngameObject::setOpacity(float opacity)
{
	m_opacity = opacity;
}

float IngameObject::getOpacity()
{
	return m_opacity;
}

void IngameObject::setAngle(float angle)
{
	m_angle = angle;
}

float IngameObject::getAngle()
{
	return m_angle;
}
