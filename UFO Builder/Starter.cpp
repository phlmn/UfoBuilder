#include "Starter.h"

using namespace std;

Starter::Starter()
{
	// set some usefull variables
	PI = 3.14159265359f;
	DEG_TO_RAD = 0.0174532925f;
	RAD_TO_DEG = 57.2957795f;
}


Starter::~Starter()
{

}

void Starter::run()
{
	// main loop
	if(init())
	{
		while(m_renderWindow->isOpen())
		{
			tick();
		}
	}

	cleanup();
}

bool Starter::init()
{	
	// create window to render
	m_renderWindow = new sf::RenderWindow(sf::VideoMode(1024, 600, 32), "UFO Builder");

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

	// load fonts
	m_fontSegoe.loadFromFile("fonts/segoeui.ttf");

	// create physical world
	m_physWorld = new b2World(b2Vec2(0.0f, 9.81f));

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

	// create menu gui
	m_windowMenu = sfg::Window::Create();

	sfg::Box::Ptr box = sfg::Box::Create(sfg::Box::VERTICAL, 10.0f);

	sfg::Button::Ptr button_start = sfg::Button::Create("Play Game");
	button_start->GetSignal(sfg::Button::OnLeftClick).Connect(&Starter::onButtonStartGameClicked, this);

	sfg::Button::Ptr button_editor = sfg::Button::Create("Start Editor");
	button_editor->GetSignal(sfg::Button::OnLeftClick).Connect(&Starter::onButtonEditorClicked, this);

	sfg::Button::Ptr button_exit = sfg::Button::Create("Exit");
	button_exit->GetSignal(sfg::Button::OnLeftClick).Connect(&Starter::onButtonExitClicked, this);

	box->Pack(button_start);
	box->Pack(button_editor);
	box->Pack(button_exit);
	m_windowMenu->Add(box);

	m_windowMenu->SetRequisition(sf::Vector2f(250.0f, 0.0f));
	m_windowMenu->SetPosition(sf::Vector2f((m_renderWindow->getView().getSize().x - m_windowMenu->GetRequisition().x) / 2.0f, (m_renderWindow->getView().getSize().y - m_windowMenu->GetRequisition().y) / 2.0f));
	m_windowMenu->SetStyle(m_windowMenu->GetStyle() & ~sfg::Window::TITLEBAR & ~sfg::Window::RESIZE);

	m_desktop.Add(m_windowMenu);

	return true;
}

void Starter::onButtonStartGameClicked()
{
	// TODO: handle game start button click
}

void Starter::onButtonEditorClicked()
{
	// TODO: handle editor start button click
}

void Starter::onButtonExitClicked()
{
	m_renderWindow->close();
}

void Starter::tick()
{
	sf::Time elapsedTime = m_clock.restart();
	float fps = 1000000.0f / elapsedTime.asMicroseconds();

	// update physics
	m_physWorld->Step(elapsedTime.asSeconds(), 6, 2);

	m_renderWindow->clear(sf::Color(0, 0, 0));

	sf::Event event;
	while(m_renderWindow->pollEvent(event))
	{
		m_desktop.HandleEvent(event);
		if (event.type == sf::Event::Closed)
		{
			// the window was closed
			m_renderWindow->close();
		}
		else if(event.type == sf::Event::Resized)
		{
			// the windows has been resized
			m_renderWindow->setView(sf::View(sf::Vector2f(event.size.width / 2.0f, event.size.height / 2.0f), sf::Vector2f((float)event.size.width, (float)event.size.height)));
			m_windowMenu->SetPosition(sf::Vector2f((m_renderWindow->getView().getSize().x - m_windowMenu->GetRequisition().x) / 2.0f, (m_renderWindow->getView().getSize().y - m_windowMenu->GetRequisition().y) / 2.0f));
		}
			
	}

	m_renderWindow->draw(m_spriteTest);

	// draw testobject
	m_spriteBody.setRotation(m_bodyTest->GetAngle() * RAD_TO_DEG);	
	m_spriteBody.setPosition(m_bodyTest->GetPosition().x * 64.0f, m_bodyTest->GetPosition().y * 64.0f);
	m_renderWindow->draw(m_spriteBody);
	
	// show fps
	sf::Text text;
	text.setFont(m_fontSegoe);
	text.setString("FPS: " + StringHelper::toString(fps));
	text.setPosition(18.0f, 10.0f);
	text.setCharacterSize(16);
	m_renderWindow->draw(text);
	
	// update gui desktop
	m_desktop.Update(elapsedTime.asSeconds());

	// render gui
	m_sfgui.Display(*m_renderWindow);

	// render the whole scene
	m_renderWindow->display();
}

void Starter::cleanup()
{
	// cleanup (delete pointers, etc.)
	delete m_renderWindow;
	delete m_physWorld;
}
