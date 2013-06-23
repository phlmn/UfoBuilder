#include "Game.h"

Game::Game(Starter* starter, sf::RenderWindow* window)
{
	m_starter = starter;
	m_level = new Level();
	m_renderWindow = window;

	m_isPressed = false;

	m_mousePosition = sf::Vector2i(0, 0);
	m_lastClick = sf::Vector2i(0, 0);

	// create physical world
	m_physWorld = new b2World(b2Vec2(0.0f, 9.81f));

	// load textures
	sf::Texture* texture = new sf::Texture();
	texture->loadFromFile("images/bg1.png");
	m_spriteTest.setTexture(*texture);

	texture = new sf::Texture();
	texture->loadFromFile("images/body1.png");
	texture->setSmooth(true);
	m_spriteBody.setTexture(*texture);
	m_spriteBody.setOrigin(m_spriteBody.getTexture()->getSize().x / 2.0f, m_spriteBody.getTexture()->getSize().y / 2.0f);

	// load level
	/*
	if(m_level->load("bagdadbahn")) {
	} else {
	}
	*/

	// calculate sprite scales
	resize();

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
	if(m_level) delete m_level;
}

void Game::tick(sf::Time elapsedTime)
{
	// update physics
	m_physWorld->Step(elapsedTime.asSeconds(), 6, 2);

	// user event handling
	#pragma region event handling
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
			m_starter->resize(event.size.width, event.size.height);
			resize();
		}
		else if(event.type == sf::Event::KeyPressed)
		{
			// key has been pressed
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			{
				// escape has been pressed -> call Menu
				m_starter->setGamestate(m_starter->Menu);
			}
		}
		else if(event.type == sf::Event::MouseMoved)
		{
			// mouse has been moved
			m_mousePosition = sf::Mouse::getPosition();
		}
		else if(event.type == sf::Event::MouseButtonPressed)
		{
			// mouse down
			if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				// left mouse button has been clicked
				m_lastClick = sf::Mouse::getPosition();
				m_difference = sf::Vector2i(m_lastClick.x - m_spriteBody.getPosition().x, m_lastClick.y - m_spriteBody.getPosition().y);

				if(isSelected(m_spriteBody))
					m_isPressed = true;
			}
		}
		else if(event.type == sf::Event::MouseButtonReleased)
		{
			// mouse up
			m_isPressed = false;
		}
	}
	#pragma endregion

	m_renderWindow->draw(m_spriteTest);

	float scale = m_starter->getScreenFactor();

	if(m_isPressed)
	{
		m_spriteBody.setPosition(m_mousePosition.x - m_difference.x, m_mousePosition.y - m_difference.y);
		m_bodyTest->SetTransform(b2Vec2(m_mousePosition.x, m_mousePosition.y), m_bodyTest->GetAngle());
	}
	else
	{
		// draw testobject
		m_spriteBody.setRotation(m_bodyTest->GetAngle() * Starter::RAD_TO_DEG);	
		//m_spriteBody.setPosition(m_bodyTest->GetPosition().x * 64.0f * scale, m_bodyTest->GetPosition().y * 64.0f * scale);
		//m_spriteBody.setPosition(m_bodyTest->GetPosition().x, m_bodyTest->GetPosition().y);
	}

	m_renderWindow->draw(m_spriteBody);
}


void Game::resize()
{
	float scale = m_starter->getScreenFactor();

	m_spriteBody.setScale(scale, scale);
	m_spriteTest.setScale(scale * 4.0f, scale * 2.2f);
}

sf::Vector2i Game::getMousePosition()
{
	return m_mousePosition;
}

sf::Vector2i Game::getLastClick()
{
	return m_lastClick;
}

bool Game::isSelected(const sf::Sprite object)
{
	if(m_lastClick.x >= object.getPosition().x)
		if(m_lastClick.x <= object.getPosition().x + object.getTexture()->getSize().x)
			if(m_lastClick.y >= object.getPosition().y + object.getTexture()->getSize().y / 2)
				if(m_lastClick.y <= object.getPosition().y + object.getTexture()->getSize().y + object.getTexture()->getSize().y / 2)
					return true;
	return false;
}
