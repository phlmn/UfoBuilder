#include "Starter.h"

using namespace std;

// set some usefull variables
const float Starter::PI = 3.14159265359f;
const float Starter::DEG_TO_RAD = 0.0174532925f;
const float Starter::RAD_TO_DEG = 57.2957795f;

Starter::Starter()
{
	m_game = NULL;
	m_editor = NULL;
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
	m_renderWindow->setFramerateLimit(60);

	// load fonts
	m_fontSegoe.loadFromFile("fonts/segoeui.ttf");
	m_fontSegoeBold.loadFromFile("fonts/segoeuib.ttf");


	m_textTitle.setFont(m_fontSegoeBold);
	m_textTitle.setString("UFO Builder");
	m_textTitle.setCharacterSize(50);
	m_textTitle.setColor(sf::Color(0x0, 0x0, 0x0, 0xbb));
	m_textTitle.setOrigin(m_textTitle.getGlobalBounds().width / 2.0f, m_textTitle.getGlobalBounds().height / 2.0f);
	m_textTitle.setPosition(sf::Vector2f(m_renderWindow->getView().getSize().x / 2.0f, m_renderWindow->getView().getSize().y / 2.0f - 100.0f));

	// load images
	sf::Texture* texture;
	texture = new sf::Texture();
	texture->loadFromFile("images/bg_menu.png");
	m_spriteBg.setTexture(*texture);
	
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
	m_windowMenu->SetPosition(sf::Vector2f((m_renderWindow->getView().getSize().x - m_windowMenu->GetRequisition().x) / 2.0f, (m_renderWindow->getView().getSize().y - m_windowMenu->GetRequisition().y) / 2.0f + 40.0f));
	m_windowMenu->SetStyle(m_windowMenu->GetStyle() & ~sfg::Window::TITLEBAR & ~sfg::Window::RESIZE);

	m_desktop.Add(m_windowMenu);

	// set the gamestate to menu
	m_gamestate = Starter::Menu;

	return true;
}

void Starter::onButtonStartGameClicked()
{
	if(m_game == NULL)
	{
		m_game = new Game(this, m_renderWindow, &m_desktop);
		if(m_editor) m_editor->hide();
		hide();
		m_game->show();
	}

	m_gamestate = Starter::Ingame;
}

void Starter::onButtonEditorClicked()
{
	if(m_editor == NULL)
	{
		m_editor = new LevelEditor(this, m_renderWindow, &m_desktop);
		if(m_game) m_editor->hide();
		hide();
		m_editor->show();
	}

	m_gamestate = Starter::Editor;
}

void Starter::onButtonExitClicked()
{
	m_renderWindow->close();
}

void Starter::tick()
{
	sf::Time elapsedTime = m_clock.restart();
	float fps = 1000000.0f / elapsedTime.asMicroseconds();

	m_renderWindow->clear(sf::Color(0x0, 0x0, 0x0));

	if(m_gamestate == Starter::Menu)
	{

		// user event handling
		sf::Event event;
		while(m_renderWindow->pollEvent(event))
		{
			m_desktop.HandleEvent(event);
			if (event.type == sf::Event::Closed)
			{
				// the close button was clicked
				m_renderWindow->close();
			}
			else if(event.type == sf::Event::Resized)
			{
				// the windows has been resized
				m_renderWindow->setView(sf::View(sf::Vector2f(event.size.width / 2.0f, event.size.height / 2.0f), sf::Vector2f((float)event.size.width, (float)event.size.height)));
				m_windowMenu->SetPosition(sf::Vector2f((m_renderWindow->getView().getSize().x - m_windowMenu->GetRequisition().x) / 2.0f, (m_renderWindow->getView().getSize().y - m_windowMenu->GetRequisition().y) / 2.0f + 40.0f));
				m_textTitle.setPosition(sf::Vector2f(m_renderWindow->getView().getSize().x / 2.0f, m_renderWindow->getView().getSize().y / 2.0f - 100.0f));
			}
		}

		m_renderWindow->draw(m_spriteBg);
		m_renderWindow->draw(m_textTitle);
	}
	else if(m_gamestate == Starter::Ingame)
	{
		m_game->tick(elapsedTime);
	}
	else if(m_gamestate == Starter::Editor)
	{
		m_editor->tick(elapsedTime);
	}

	// update gui desktop
	m_desktop.Update(elapsedTime.asSeconds());

	// render gui
	m_gui.Display(*m_renderWindow);

	// show fps
	sf::Text text;
	text.setFont(m_fontSegoe);
	text.setString("FPS: " + StringHelper::toString(fps));
	text.setCharacterSize(16);
	text.setColor(sf::Color(0x0, 0x0, 0x0, 0x55));
	text.setPosition(19.0f, 11.0f);
	m_renderWindow->draw(text);
	text.setColor(sf::Color(0xff, 0xff, 0xff, 0xff));
	text.setPosition(18.0f, 10.0f);
	m_renderWindow->draw(text);

	// render the whole scene
	m_renderWindow->display();
}

void Starter::cleanup()
{
	// cleanup (delete pointers, etc.)
	delete m_renderWindow;
	if(m_game) delete m_game;
	if(m_editor) delete m_editor;
}

void Starter::hide()
{
	m_windowMenu->Show(false);
}

void Starter::show()
{
	m_windowMenu->Show(true);
}
