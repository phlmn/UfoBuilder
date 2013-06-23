#pragma once

#include <SFML\Graphics.hpp>
#include <Box2D\Box2D.h>
#include "tinyxml2.h"

class CatalogObject;

class LevelObject
{
protected:
	int m_layer;
	sf::Vector2f m_position;
	float m_scale;
	float m_opacity;
	float m_angle;
	sf::Sprite* m_sprite;
	sf::String m_imageFile;
	sf::String m_objectType;
	sf::String m_category;
	b2BodyDef m_bodyDef;
	std::string m_name;
	int m_objectID;

public:
	LevelObject();
	LevelObject(tinyxml2::XMLElement* element);
	LevelObject(CatalogObject gameObject);
	LevelObject(CatalogObject gameObject, int layer, sf::Vector2f position, float scale, float opacity, float angle);
	~LevelObject();

	void tick(sf::Time elapsedTime);

	void getDataFromCatalogObject(CatalogObject catObj);

	void setLayer(int layer);
	int getLayer();

	void setPosition(sf::Vector2f position);
	sf::Vector2f getPosition();

	void setScale(float scale);
	float getScale();

	void setOpacity(float scale);
	float getOpacity();

	void setAngle(float angle);
	float getAngle();

	void setName(std::string name);
	std::string getName();

	void setObjectType(std::string id);
	std::string getObjectType();

	void setObjectID(int id);
	int getObjectID();

	void setObjectCategory(std::string cat);
	std::string getObjectCategory();
};
