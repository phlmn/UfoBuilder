#include "StorablePhysProps.h"


StorablePhysProps::StorablePhysProps()
{

}

StorablePhysProps::~StorablePhysProps()
{

}

void StorablePhysProps::setBodyType(PhysBodyType bodyType)
{
	m_type = bodyType;
}

PhysBodyType StorablePhysProps::getBodyType()
{
	return m_type;
}

std::list<StorableFixture>* StorablePhysProps::getFixtures()
{
	return &m_fixtures;
}
