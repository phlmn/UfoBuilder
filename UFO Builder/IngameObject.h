#pragma once

#include <SFML\Graphics.hpp>

#include "GameObject.h"


class IngameObject : public GameObject
{
private:
	int m_layer;
	sf::Vector2f m_position;
	float m_scale;
	float m_opacity;
	float m_angle;
	sf::Sprite* m_sprite;
public:
	IngameObject();
	IngameObject(GameObject gameObject);
	IngameObject(GameObject gameObject, int layer, sf::Vector2f position, float scale, float opacity, float angle);
	~IngameObject();

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

