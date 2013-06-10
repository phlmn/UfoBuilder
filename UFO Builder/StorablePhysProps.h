#pragma once

#include <list>

#include "StorableFixture.h"

class StorablePhysProps
{
public:
	enum BodyType
	{
		Static,
		Dynamic
	};
private:
	BodyType m_type;
	std::list<StorableFixture> m_fixtures;

public:
	StorablePhysProps();
	~StorablePhysProps();

	void setBodyType(BodyType bodyType);
	BodyType getBodyType();

	std::list<StorableFixture>* getFixtures();
};
