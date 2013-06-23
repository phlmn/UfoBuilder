#include "LevelEditor.h"

#include "Level.h"
#include "CatalogObject.h"
#include "LevelObject.h"

using namespace std;
using namespace Awesomium;

LevelEditor::LevelEditor(Starter* starter, sf::RenderWindow* window)
{
	m_starter = starter;
	m_renderWindow = window;
	m_level = new Level(window);
	m_lastObjectID = 0;
	m_moveObject = NULL;

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

	m_catalogObjects.clear();
	
	// load object catalog
	ifstream stream = ifstream("objects/catalog.list");
	while(!stream.eof())
	{
		char line[128];
		stream.getline(line, sizeof(line));
		CatalogObject* object = new CatalogObject();
		if(object->load(line))
		{
			m_catalogObjects.push_back(object);
			m_uiRenderer->executeJavascript(ToWebString(string() + "addCatalogObject('" + object->getObjectID() + "', '" + object->getName() + "', '" + object->getCategory() + "');"));
		}
	}

	// init mouse pos
	m_mouseLastPos = sf::Mouse::getPosition();

	// init sprite resizing
	resize();
}


LevelEditor::~LevelEditor()
{
	if(m_level) delete m_level;
	delete m_uiRenderer;
}

void LevelEditor::tick(sf::Time elapsedTime)
{
	sf::Vector2i mousePos = sf::Mouse::getPosition();
	sf::Vector2i mouseDelta = mousePos - m_mouseLastPos;
	m_mouseLastPos = mousePos;

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
		else if(event.type == sf::Event::KeyPressed)
		{
			// key has been pressed
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			{
				// escape has been pressed -> call Menu
				m_starter->setGamestate(m_starter->Menu);
			}
		}
		else if(event.type == sf::Event::MouseButtonPressed)
		{
			m_moveObject = NULL;
		}
		m_uiRenderer->handleEvent(event);
	}

	if(m_moveObject)
	{
		m_moveObject->setPosition(sf::Vector2f(m_moveObject->getPosition().x + mouseDelta.x / Starter::getScreenFactor(), m_moveObject->getPosition().y + mouseDelta.y / Starter::getScreenFactor()));
	}

	m_renderWindow->draw(m_spriteBg);
	m_level->tick(elapsedTime);
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
			createObject(ToString(args.At(0).ToString()), args.At(1).ToInteger());
		}
	}
}

JSValue LevelEditor::OnMethodCallWithReturnValue(WebView* caller, unsigned int remote_object_id, const WebString& method_name, const JSArray& args)
{
	return JSValue::Undefined();
}

void LevelEditor::createObject(string id, int layer)
{
	CatalogObject* object = NULL;

	list<CatalogObject*>::iterator pos = m_catalogObjects.begin();
	while(pos != m_catalogObjects.end())
	{
		if((*pos)->getObjectID() == id)
		{
			object = (*pos);
			break;
		}
		pos++;
	}

	LevelObject* levelObject = new LevelObject(*object);
	m_level->addObject(levelObject);
	levelObject->setObjectID(++m_lastObjectID);
	levelObject->setRenderWindow(m_renderWindow);
	levelObject->setPosition(sf::Vector2f(sf::Mouse::getPosition(*m_renderWindow).x / Starter::getScreenFactor(), sf::Mouse::getPosition(*m_renderWindow).y / Starter::getScreenFactor()));
	m_uiRenderer->executeJavascript(ToWebString(string() + "appendObject('" + levelObject->getName() + "', '" + StringHelper::toString(levelObject->getObjectID()) + "', " + StringHelper::toString(layer) + ");"));
	m_moveObject = levelObject;
}
