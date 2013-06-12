#pragma once

#include <SFML\Graphics.hpp>

class CatalogObject;

class LevelObject
{
private:
	int m_layer;
	sf::Vector2f m_position;
	float m_scale;
	float m_opacity;
	float m_angle;
	sf::Sprite* m_sprite;
	sf::String m_imageFile;
	sf::String m_objectID;
	b2BodyDef m_bodyDef;
public:
	LevelObject();
	LevelObject(CatalogObject gameObject);
	LevelObject(CatalogObject gameObject, int layer, sf::Vector2f position, float scale, float opacity, float angle);
	~LevelObject();

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
};
