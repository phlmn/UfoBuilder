#include "LevelEditor.h"

#include "Level.h"

LevelEditor::LevelEditor(Starter* starter, sf::RenderWindow* window)
{
	m_starter = starter;
	m_renderWindow = window;
	m_level = new Level();

	// load images
	sf::Texture* texture;
	texture = new sf::Texture();
	texture->loadFromFile("images/bg_editor.png");
	m_spriteBg.setTexture(*texture);

	m_uiRenderer = new UiRenderer(starter->getWebCore(), starter->getWebSession(), window, (sf::Vector2i)starter->getScreenSize(), "asset://res/editor.html");
	m_uiRenderer->setJSMethodHandler(this);

	// register js methods
	m_uiRenderer->registerMethod("newLevel", false);
	m_uiRenderer->registerMethod("createObject", false);

	// init sprite resizing
	resize();
}


LevelEditor::~LevelEditor()
{
	if(m_level != NULL)
		delete m_level;

	delete m_uiRenderer;
}

void LevelEditor::tick(sf::Time elapsedTime)
{
	
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
			m_starter->resize(event.size.width, event.size.height);
			m_uiRenderer->resize((sf::Vector2i)m_starter->getScreenSize());
			resize();
		}
		m_uiRenderer->handleEvent(event);
	}

	m_renderWindow->draw(m_spriteBg);
	m_uiRenderer->render();
}

void LevelEditor::resize()
{
	float scale = m_starter->getScreenFactor();

	m_spriteBg.setScale(3.2f * scale, 3.2f * scale);
}

void LevelEditor::OnMethodCall(WebView* caller, unsigned int remote_object_id, const WebString& method_name, const JSArray& args)
{
	if(method_name == WSLit("newLevel"))
	{

	}
	else if(method_name == WSLit("createObject"))
	{
		if(args.size() == 2)
		{
			createObject(args.At(0).ToInteger(), args.At(1).ToInteger());
		}
	}
}

JSValue LevelEditor::OnMethodCallWithReturnValue(WebView* caller, unsigned int remote_object_id, const WebString& method_name, const JSArray& args)
{
	return JSValue::Undefined();
}

void LevelEditor::createObject(int layer, int id)
{
	
}
