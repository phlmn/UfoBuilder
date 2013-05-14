#pragma once

#include <Box2D\Box2D.h>
#include <list>

#include "enums.h"

class StorableFixture
{
private:
	std::list<b2Vec2> m_vertices;
	b2Vec2 m_position;
	PhysFixtureType m_type;
	float m_density;
	float m_friction;

public:
	StorableFixture();
	~StorableFixture();

	void setDensity(float density);
	float getDensity();

	void setType(PhysFixtureType type);
	PhysFixtureType getType();

	void setPosition(b2Vec2 position);
	b2Vec2 getPosition();

	void setFriction(float friction);
	float getFriction();

	std::list<b2Vec2>* getVertices();
};

