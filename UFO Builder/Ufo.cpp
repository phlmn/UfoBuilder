#include "Ufo.h"


Ufo::Ufo(sf::RenderWindow* window)
{
	m_renderWindow = window;

	// create physical world
	m_physWorld = new b2World(b2Vec2(0.0f, 9.81f));

	m_mousePosition = sf::Vector2i(0, 0);
	m_lastClick = sf::Vector2i(0, 0);
	m_difference = sf::Vector2i(0, 0);
	m_mouseIsPressed = false;

	m_acceleration = 0;
	m_direcction = 0;

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
		else if(event.type == sf::Event::MouseMoved)
		{
			// mouse has been moved
			m_mousePosition = sf::Mouse::getPosition(*m_renderWindow);
		}
		else if(event.type == sf::Event::MouseButtonPressed)
		{
			// mouse down
			if(event.key.code == sf::Mouse::Left)
			{
				// left mouse button has been clicked
				m_lastClick = sf::Mouse::getPosition(*m_renderWindow);
				m_difference = sf::Vector2i(m_lastClick.x - (int)m_spriteBody->getPosition().x, m_lastClick.y - (int)m_spriteBody->getPosition().y);

				if(isSelected(m_spriteBody))
					m_mouseIsPressed = true;
			}
		}
		else if(event.type == sf::Event::MouseButtonReleased)
		{
			// mouse up
			m_mouseIsPressed = false;
		}
	}
	#pragma endregion

	if(m_mouseIsPressed)
	{
		// Mouse control
		m_spriteBody->setPosition((float)(m_mousePosition.x - m_difference.x), (float)(m_mousePosition.y - m_difference.y));
		m_bodyTest->SetTransform(b2Vec2((float)(m_mousePosition.x - m_difference.x), (float)(m_mousePosition.y - m_difference.y)), m_bodyTest->GetAngle());
	}
	else
	{
		// draw testobject
		//m_spriteBody.setRotation(m_bodyTest->GetAngle() * Starter::RAD_TO_DEG);
		m_spriteBody->setPosition(m_bodyTest->GetPosition().x, m_bodyTest->GetPosition().y);
	}

	// Key control
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		m_acceleration += 2;
	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		m_acceleration -= 2;
	}
	else
	{
		if(m_acceleration > 0)
		{
			m_acceleration--;
		}
		else if(m_acceleration < 0)
		{
			m_acceleration++;
		}
	}

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		m_direcction += 2;
	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		m_direcction -= 2;
	}
	else
	{
		if(m_direcction > 0)
		{
			m_direcction--;
		}
		else if(m_direcction < 0)
		{
			m_direcction++;
		}
	}

	m_bodyTest->SetTransform(b2Vec2(m_bodyTest->GetPosition().x - (float)m_direcction / m_sensitivity, m_bodyTest->GetPosition().y - (float)m_acceleration / m_sensitivity), m_bodyTest->GetAngle());

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

sf::Vector2i Ufo::getMousePosition()
{
	return m_mousePosition;
}

sf::Vector2i Ufo::getLastClick()
{
	return m_lastClick;
}


bool Ufo::isSelected(const sf::Sprite* object)
{
	if(m_lastClick.x >= object->getPosition().x - object->getTexture()->getSize().x / 4)
		if(m_lastClick.x <= object->getPosition().x + object->getTexture()->getSize().x / 4)
			if(m_lastClick.y >= object->getPosition().y - object->getTexture()->getSize().y / 4)
				if(m_lastClick.y <= object->getPosition().y + object->getTexture()->getSize().y / 4)
					return true;
	return false;
}
