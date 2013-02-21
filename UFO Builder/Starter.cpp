#include "Starter.h"


Starter::Starter()
{
	PI = 3.14159265359f;
	DEG_TO_RAD = 0.0174532925f;
	RAD_TO_DEG = 57.2957795f;
}


Starter::~Starter()
{

}

void Starter::run()
{
	if(init())
	{
		while(m_window->isOpen())
		{
			tick();
		}
	}

	cleanup();
}

bool Starter::init()
{	
	m_window = new sf::RenderWindow(sf::VideoMode(1024, 600, 32), "UFO Builder");

	sf::Texture* texture = new sf::Texture();
	texture->loadFromFile("images/bg1.png");
	m_spriteTest.setTexture(*texture);
	m_spriteTest.setScale(2.0f, 1.2f);

	texture = new sf::Texture();
	texture->loadFromFile("images/body1.png");
	texture->setSmooth(true);
	m_spriteBody.setTexture(*texture);

	m_fontSegoe.loadFromFile("fonts/segoeui.ttf");

	m_physWorld = new b2World(b2Vec2(0.0f, 9.81f));

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

	m_spriteBody.setOrigin(m_spriteBody.getTexture()->getSize().x / 2.0f, m_spriteBody.getTexture()->getSize().y / 2.0f);

	sfg::Window::Ptr window = sfg::Window::Create();
	sfg::Box::Ptr box = sfg::Box::Create();
	window->Add(box);
	box->Pack(sfg::Button::Create("test"));
	box->Pack(sfg::Button::Create("2. Testsldklasdlksldkasldklasksdk"));
	
	desktop.Add( window );



	return true;
}

void Starter::tick()
{
	sf::Time elapsedTime = m_clock.restart();
	float fps = 1000000.0f / elapsedTime.asMicroseconds();

	m_physWorld->Step(elapsedTime.asSeconds(), 6, 2);

	m_window->clear(sf::Color(0, 0, 0));

	sf::Event event;
	while(m_window->pollEvent(event))
	{
		desktop.HandleEvent(event);
		if (event.type == sf::Event::Closed)
			m_window->close();
	}

	m_window->draw(m_spriteTest);

	m_spriteBody.setRotation(m_bodyTest->GetAngle() * RAD_TO_DEG);
	
	m_spriteBody.setPosition(m_bodyTest->GetPosition().x * 64.0f, m_bodyTest->GetPosition().y * 64.0f);
	m_window->draw(m_spriteBody);
	
	sf::Text text;
	text.setFont(m_fontSegoe);
	text.setString("FPS: " + StringHelper::toString(fps));
	text.setPosition(18.0f, 10.0f);
	text.setCharacterSize(16);
	m_window->draw(text);
	
	desktop.Update(elapsedTime.asSeconds());

	m_sfgui.Display(*m_window);
	m_window->display();
}

void Starter::cleanup()
{
	delete m_window;
	delete m_physWorld;
}
