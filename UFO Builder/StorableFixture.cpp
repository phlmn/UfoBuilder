#include "StorableFixture.h"


StorableFixture::StorableFixture()
{
}


StorableFixture::~StorableFixture()
{
}

void StorableFixture::setDensity(float density)
{
	m_density = density;
}

float StorableFixture::getDensity()
{
	return m_density;
}

void StorableFixture::setType(Type type)
{
	m_type = type;
}

StorableFixture::Type StorableFixture::getType()
{
	return m_type;
}

void StorableFixture::setPosition(b2Vec2 position)
{
	m_position = position;
}

b2Vec2 StorableFixture::getPosition()
{
	return m_position;
}

void StorableFixture::setFriction(float friction)
{
	m_friction = friction;
}

float StorableFixture::getFriction()
{
	return m_friction;
}

std::list<b2Vec2>* StorableFixture::getVertices()
{
	return &m_vertices;
}
