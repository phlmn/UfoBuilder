#include "Ufo.h"

#include "Starter.h"

Ufo::Ufo(sf::RenderWindow* window)
{
	m_renderWindow = window;

	// create physical world
	m_physWorld = new b2World(b2Vec2(0.0f, 9.81f));

	m_cameraPos = sf::Vector2f();
	m_sensitivity = 5.0f;

	// load images
	m_spriteBody = new sf::Sprite();
	sf::Texture* texture = new sf::Texture();
	texture->loadFromFile("objects/images/ufo.png");
	texture->setSmooth(true);
	m_spriteBody->setTexture(*texture);
	m_spriteBody->setOrigin(m_spriteBody->getTexture()->getSize().x / 2.0f, m_spriteBody->getTexture()->getSize().y / 2.0f);

	// create physical bodies
	b2BodyDef* def = new b2BodyDef();
	def->position = b2Vec2(1.0f, 1.0f);
	def->type = b2_dynamicBody;
	
	m_bodyTest = m_physWorld->CreateBody(def);
	m_bodyTest->SetLinearDamping(0.2f);
	m_bodyTest->SetFixedRotation(true);

	b2CircleShape* shape = new b2CircleShape();
	shape->m_radius = 1.1f;
	b2Fixture* fixture = m_bodyTest->CreateFixture(shape, 2.0f);
	fixture->SetFriction(2.0f);	

	def = new b2BodyDef();
	def->position = b2Vec2(0.0f, 5.0f);
	m_bodyGround = m_physWorld->CreateBody(def);

	b2PolygonShape* shape2 = new b2PolygonShape();
	shape2->SetAsBox(10.0f, 0.1f, b2Vec2(0.0f, 0.0f), 0.0f);

	m_bodyGround->CreateFixture(shape2, 2.0f);
}


Ufo::~Ufo()
{
	if(m_physWorld) delete m_physWorld;
}

void Ufo::tick(sf::Time elapsedTime)
{
	// update physics
	m_physWorld->Step(elapsedTime.asSeconds(), 6, 2);

	// user event handling
	#pragma region event handling
	sf::Event event;
	while(m_renderWindow->pollEvent(event))
	{
		if(event.type == sf::Event::KeyPressed)
		{
			// key has been pressed
		}
		else if(event.type == sf::Event::KeyReleased)
		{
			// key has been released
		}
	}
	#pragma endregion	

	// Key control
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		m_bodyTest->ApplyForce(b2Vec2(0, -200), b2Vec2(m_bodyTest->GetPosition().x, m_bodyTest->GetPosition().y));
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		m_bodyTest->ApplyForce(b2Vec2(-200, 0), b2Vec2(m_bodyTest->GetPosition().x, m_bodyTest->GetPosition().y));
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		m_bodyTest->ApplyForce(b2Vec2(200, 0), b2Vec2(m_bodyTest->GetPosition().x, m_bodyTest->GetPosition().y));
	}
	
	m_spriteBody->setPosition((((m_bodyTest->GetPosition().x * 64.0f) - m_cameraPos.x * Starter::getScreenFactor()) + 960.0f) * Starter::getScreenFactor(), (((m_bodyTest->GetPosition().y * 64.0f) + m_cameraPos.y * Starter::getScreenFactor()) + 500.0f) * Starter::getScreenFactor());
		
	if(m_spriteBody)
		m_renderWindow->draw(*m_spriteBody);
}

void Ufo::resize(float scale)
{
	m_spriteBody->setScale(scale, scale);
}

void Ufo::addPart()
{

}
void Ufo::removePart()
{

}

void Ufo::setCameraPos(sf::Vector2f pos)
{
	m_cameraPos = pos;
}

sf::Vector2f Ufo::getCameraPos() 
{
	return m_cameraPos;
}

void Ufo::setPos(sf::Vector2f pos)
{
	m_bodyTest->SetTransform(b2Vec2(pos.x / 64.0f, -pos.y / 64.0f), m_bodyTest->GetAngle());
}

sf::Vector2f Ufo::getPos()
{
	return sf::Vector2f(m_bodyTest->GetPosition().x * 64.0f,  -m_bodyTest->GetPosition().y * 64.0f);
}
