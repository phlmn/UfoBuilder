#pragma once

#include <Box2D\Box2D.h>
#include <list>

class StorableFixture
{
public:
	enum Type
	{
		Polygon,
		Line,
		Chain,
		Circle
	};
private:
	std::list<b2Vec2> m_vertices;
	b2Vec2 m_position;
	Type m_type;
	float m_density;
	float m_friction;

public:
	StorableFixture();
	~StorableFixture();

	void setDensity(float density);
	float getDensity();

	void setType(Type type);
	Type getType();

	void setPosition(b2Vec2 position);
	b2Vec2 getPosition();

	void setFriction(float friction);
	float getFriction();

	std::list<b2Vec2>* getVertices();
};

