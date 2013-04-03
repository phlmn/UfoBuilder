#include "Starter.h"

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

	// load images
	sf::Texture* texture;
	texture = new sf::Texture();
	texture->loadFromFile("images/bg_menu.png");
	m_spriteBg.setTexture(*texture);

	WebConfig webConfig;
	webConfig.child_process_path = WSLit("./ufobuilder-ui.exe");
	m_webCore = WebCore::Initialize(webConfig);

	m_webSession = m_webCore->CreateWebSession(WSLit(""), WebPreferences());

	unsigned short filesWritten;
	WriteDataPak(WSLit("resource.pak"), WSLit("resource"), WSLit(""), filesWritten);
	
	m_webSession->AddDataSource(WSLit("res"), new DataPakSource(WSLit("resource.pak")));
	
	m_uiRenderer = new UiRenderer(m_webCore, m_webSession, m_renderWindow, sf::Vector2i(1024, 600), "asset://res/menu.html");
	
	m_uiRenderer->registerMethod("startGame", false);
	m_uiRenderer->registerMethod("startEditor", false);
	m_uiRenderer->registerMethod("exit", false);

	m_uiRenderer->setJSMethodHandler(this);
	
	// set the gamestate to menu
	m_gamestate = Starter::Menu;

	return true;
}

void Starter::tick()
{
	sf::Time elapsedTime = m_clock.restart();
	float fps = 1000000.0f / elapsedTime.asMicroseconds();

	m_renderWindow->clear(sf::Color(0x0, 0x0, 0x0));

	// update webcore
	m_webCore->Update();

	if(m_gamestate == Starter::Menu)
	{
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
	return JSValue();
}

WebCore* Starter::getWebCore()
{
	return m_webCore;
}

WebSession* Starter::getWebSession()
{
	return m_webSession;
}

sf::Vector2i Starter::getScreenSize()
{
	return sf::Vector2i(m_renderWindow->getSize().x, m_renderWindow->getSize().y);
}
