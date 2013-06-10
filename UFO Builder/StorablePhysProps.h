#pragma once

#include <list>

#include "StorableFixture.h"
#include "enums.h"

class StorablePhysProps
{
private:
	PhysBodyType m_type;
	std::list<StorableFixture> m_fixtures;

public:
	StorablePhysProps();
	~StorablePhysProps();

	void setBodyType(PhysBodyType bodyType);
	PhysBodyType getBodyType();

	std::list<StorableFixture>* getFixtures();
};
