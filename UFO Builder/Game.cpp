#include "Game.h"

Game::Game(Starter* starter, sf::RenderWindow* window)
{
	m_starter = starter;
	m_renderWindow = window;

	// create physical world
	m_physWorld = new b2World(b2Vec2(0.0f, 9.81f));

	// load textures
	sf::Texture* texture = new sf::Texture();
	texture->loadFromFile("images/bg1.png");
	m_spriteTest.setTexture(*texture);
	m_spriteTest.setScale(2.0f, 1.2f);

	texture = new sf::Texture();
	texture->loadFromFile("images/body1.png");
	texture->setSmooth(true);
	m_spriteBody.setTexture(*texture);
	m_spriteBody.setOrigin(m_spriteBody.getTexture()->getSize().x / 2.0f, m_spriteBody.getTexture()->getSize().y / 2.0f);

	// create physical bodies
	b2BodyDef* def = new b2BodyDef();
	def->position = b2Vec2(1.0f, 1.0f);
	def->type = b2_dynamicBody;
	m_bodyTest = m_physWorld->CreateBody(def);
	m_bodyTest->SetLinearDamping(0.1f);

	b2CircleShape* shape = new b2CircleShape();
	shape->m_radius = 1.1f;
	m_bodyTest->CreateFixture(shape, 2.0f);	
	m_bodyTest->ApplyTorque(60.0f);	

	def = new b2BodyDef();
	def->position = b2Vec2(0.0f, 5.0f);
	m_bodyGround = m_physWorld->CreateBody(def);

	b2PolygonShape* shape2 = new b2PolygonShape();
	shape2->SetAsBox(10.0f, 0.1f, b2Vec2(0.0f, 0.0f), 0.0f);

	m_bodyGround->CreateFixture(shape2, 2.0f);
}

Game::~Game()
{
	if(m_physWorld) delete m_physWorld;
}

void Game::tick(sf::Time elapsedTime)
{
	// update physics
	m_physWorld->Step(elapsedTime.asSeconds(), 6, 2);

	// user event handling
	sf::Event event;
	while(m_renderWindow->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			// the close button was clicked
			m_renderWindow->close();
		}
		else if(event.type == sf::Event::Resized)
		{
			// the windows has been resized
			m_renderWindow->setView(sf::View(sf::Vector2f(event.size.width / 2.0f, event.size.height / 2.0f), sf::Vector2f((float)event.size.width, (float)event.size.height)));
		}
	}

	m_renderWindow->draw(m_spriteTest);

	// draw testobject
	m_spriteBody.setRotation(m_bodyTest->GetAngle() * Starter::RAD_TO_DEG);	
	m_spriteBody.setPosition(m_bodyTest->GetPosition().x * 64.0f, m_bodyTest->GetPosition().y * 64.0f);
	m_renderWindow->draw(m_spriteBody);
}
