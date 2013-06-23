#include "Starter.h"

#include "Game.h"
#include "LevelEditor.h"

using namespace Awesomium;

// set some usefull variables
const float Starter::PI = 3.14159265359f;
const float Starter::DEG_TO_RAD = 0.0174532925f;
const float Starter::RAD_TO_DEG = 57.2957795f;
float Starter::screenFactor = 1;

Starter::Starter()
{
	m_game = NULL;
	m_editor = NULL;
}


Starter::~Starter()
{
	delete m_uiRenderer;
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
	m_renderWindow = new sf::RenderWindow(sf::VideoMode(1024, 576, 32), "UFO Builder");
	m_renderWindow->setFramerateLimit(60);

	Starter::screenFactor = m_renderWindow->getSize().x / 1920.0f; // aspect ratio from window

	// load fonts
	m_fontSegoe.loadFromFile("fonts/segoeui.ttf");
	m_fontSegoeBold.loadFromFile("fonts/segoeuib.ttf");

	// load images
	sf::Texture* texture;
	texture = new sf::Texture();
	texture->loadFromFile("images/bg_menu.png");
	m_spriteBg.setTexture(*texture);

	// specify configuration settings for the WebCore
	WebConfig webConfig;
	webConfig.child_process_path = WSLit("./ufobuilder-ui.exe");
	// initialize WebCore with configuration settings from WebConfig
	m_webCore = WebCore::Initialize(webConfig);

	m_webSession = m_webCore->CreateWebSession(WSLit(""), WebPreferences());

	// pack all files in a certain directory, into a PAK file
	unsigned short filesWritten;
	WriteDataPak(WSLit("resource.pak"), WSLit("resource"), WSLit(""), filesWritten);
	
	m_webSession->AddDataSource(WSLit("res"), new DataPakSource(WSLit("resource.pak")));
	
	m_uiRenderer = new UiRenderer(m_webCore, m_webSession, m_renderWindow, sf::Vector2i(1024, 600), "asset://res/menu.html");
	
	// convert methods to js-methods and register them
	m_uiRenderer->registerMethod("startGame", false);
	m_uiRenderer->registerMethod("startEditor", false);
	m_uiRenderer->registerMethod("exit", false);

	// register a handler for custom js-object methods
	m_uiRenderer->setJSMethodHandler(this);
	
	// set the gamestate to menu
	m_gamestate = Starter::Menu;

	return true;
}

void Starter::tick()
{
	// put the time counter back to 0, return elapsed time since the clock was started
	sf::Time elapsedTime = m_clock.restart();
	float fps = 1000000.0f / elapsedTime.asMicroseconds();

	m_renderWindow->clear(sf::Color(0x0, 0x0, 0x0)); // clear the entire target with a single color

	// update webcore
	m_webCore->Update();

	if(m_gamestate == Starter::Menu)
	{
		sf::Event event; // holds all the informations about a system event that just happened
		// go to the event on top of the event queue and handle it
		while(m_renderWindow->pollEvent(event))// go to top
		{
			if (event.type == sf::Event::Closed)
			{
				// the close button was clicked
				m_renderWindow->close();
			}
			else if(event.type == sf::Event::Resized)
			{
				// the windows has been resized
				resize(event.size.width, event.size.height);
				m_uiRenderer->resize(event.size.width, event.size.height);				
			}
			m_uiRenderer->handleEvent(event);
		}
		m_renderWindow->draw(m_spriteBg);
		m_uiRenderer->render();
	}
	else if(m_gamestate == Starter::Ingame)
	{
		m_game->tick(elapsedTime);

		std::string posstr;

		// show fps
		showText("FPS: " + StringHelper::toString(fps), 16, 18.0f, 10.0f, true);

		/*
		posstr = StringHelper::toString(m_game->getMousePosition().x) + ", " + StringHelper::toString(m_game->getMousePosition().y);
		showText("Mouse Position: " + posstr, 16, 18.0f, 30.0f, true);

		posstr = StringHelper::toString(m_game->getLastClick().x) + ", " + StringHelper::toString(m_game->getLastClick().y);
		showText("Letzer Klick: " + posstr, 16, 18.0f, 50.0f, true);
		*/
	}
	else if(m_gamestate == Starter::Editor)
	{
		m_editor->tick(elapsedTime);
	}

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

void Starter::OnMethodCall(WebView* caller, unsigned int remote_object_id, const WebString& method_name, const JSArray& args)
{
	if(method_name == WSLit("startGame"))
	{
		if(m_game == NULL)
		{
			m_game = new Game(this, m_renderWindow);
		}

		m_gamestate = Starter::Ingame;
	}
	else if(method_name == WSLit("startEditor"))
	{
		if(m_editor == NULL)
		{
			m_editor = new LevelEditor(this, m_renderWindow);
		}

		m_gamestate = Starter::Editor;
	}
	else if(method_name == WSLit("exit"))
	{
		m_renderWindow->close();
	}
}

JSValue Starter::OnMethodCallWithReturnValue(Awesomium::WebView *caller, unsigned int remote_object_id, const Awesomium::WebString &method_name, const Awesomium::JSArray &args)
{
	return JSValue::Undefined();
}

void Starter::showText(std::string value, int size, float x, float y, bool shadow)
{
	sf::Text text;
	text.setFont(m_fontSegoe);
	text.setString(value);
	text.setCharacterSize(size);

	if(shadow)
	{
		text.setColor(sf::Color(0x0, 0x0, 0x0, 0x55));
		text.setPosition(x + 1, y + 1);
		m_renderWindow->draw(text);
	}

	text.setColor(sf::Color(0xff, 0xff, 0xff, 0xff));
	text.setPosition(x, y);
	m_renderWindow->draw(text);
}

void Starter::setGamestate(Gamestate state)
{
	m_gamestate = state;
}

WebCore* Starter::getWebCore()
{
	return m_webCore;
}

WebSession* Starter::getWebSession()
{
	return m_webSession;
}

float Starter::getScreenFactor()
{
	return Starter::screenFactor;
}

void Starter::resize(int width, int height)
{

	float goalAspect = 16.0f / 9.0f;
	float viewAspect = width / (float)height;

	float realWidth, realHeight;

	if(goalAspect > viewAspect)
	{
		realWidth = (float)width;
		realHeight = height * (viewAspect / goalAspect);		
	}
	else if(goalAspect < viewAspect)
	{
		realWidth = width * (goalAspect / viewAspect);
		realHeight = (float)height;
	}
	else
	{
		realWidth = (float)width;
		realHeight = (float)height;
	}

	Starter::screenFactor = realWidth / 1920.0f;
	// "2D camera", defines what region is shown on screen (scroll, rotate, zoom without altering the way objects are drawn
	sf::View view = sf::View(sf::Vector2f(realWidth / 2.0f, realHeight / 2.0f), sf::Vector2f(realWidth, realHeight));
	// set the target viewport.
	// the viewprt is the rectangle into which the contents of the view are dislayed (witch factor beetween 0 - 1)
	view.setViewport(sf::FloatRect((width - realWidth) / width / 2.0f, (height - realHeight) / height / 2.0f, realWidth / width, realHeight / height));

	m_renderWindow->setView(view);
}

sf::Vector2f Starter::getScreenSize()
{
	return m_renderWindow->getView().getSize();
}
