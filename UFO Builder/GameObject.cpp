#include "GameObject.h"
#include "SaveObject.h"

GameObject::GameObject()
{
	m_objectID = "";
	m_imageFile = "";
	m_name = "";
	m_bodyDef.position = b2Vec2();

	b2World* world = new b2World(b2Vec2(0, 9.81f));
	b2Body* body = world->CreateBody(&m_bodyDef);

	b2FixtureDef fixDef = b2FixtureDef();
	fixDef.friction = 1;
	fixDef.density = 1;
	
	b2ChainShape* shape = new b2ChainShape();

	b2Vec2 vertices[7];
	vertices[0] = b2Vec2(0, 0);
	vertices[1] = b2Vec2(0, 0);
	vertices[2] = b2Vec2(0, 0);
	vertices[3] = b2Vec2(0, 0);
	vertices[4] = b2Vec2(0, 0);
	vertices[5] = b2Vec2(0, 0);
	vertices[6] = b2Vec2(0, 0);
	shape->CreateChain(vertices, 7);

	

	fixDef.shape = shape;

	b2Fixture* fixture = body->CreateFixture(&fixDef);
}

GameObject::GameObject(SaveObject saveObject)
{
	m_objectID = "";
	m_imageFile = saveObject.getImageFile();
	m_name = saveObject.getName();
	m_bodyDef.position = b2Vec2();

	b2World* world = new b2World(b2Vec2(0, 9.81f));
	b2Body* body = world->CreateBody(&m_bodyDef);

	b2FixtureDef fixDef = b2FixtureDef();
	fixDef.friction = 1;
	fixDef.density = 1;
	
	b2ChainShape* shape = new b2ChainShape();

	b2Vec2 vertices[7];
	vertices[0] = b2Vec2(0, 0);
	vertices[1] = b2Vec2(0, 0);
	vertices[2] = b2Vec2(0, 0);
	vertices[3] = b2Vec2(0, 0);
	vertices[4] = b2Vec2(0, 0);
	vertices[5] = b2Vec2(0, 0);
	vertices[6] = b2Vec2(0, 0);
	shape->CreateChain(vertices, 7);

	

	fixDef.shape = shape;

	b2Fixture* fixture = body->CreateFixture(&fixDef);
}

GameObject::~GameObject()
{

}

void GameObject::setObjectID(sf::String id)
{
	m_objectID = id;
}

sf::String GameObject::getObjectID()
{
	return m_objectID;
}
