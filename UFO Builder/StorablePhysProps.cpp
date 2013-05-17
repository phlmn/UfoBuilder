#include "StorablePhysProps.h"


StorablePhysProps::StorablePhysProps()
{

}

StorablePhysProps::~StorablePhysProps()
{

}

void StorablePhysProps::setBodyType(BodyType bodyType)
{
	m_type = bodyType;
}

StorablePhysProps::BodyType StorablePhysProps::getBodyType()
{
	return m_type;
}

std::list<StorableFixture>* StorablePhysProps::getFixtures()
{
	return &m_fixtures;
}
