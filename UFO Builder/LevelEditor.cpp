#include "LevelEditor.h"

#include "Level.h"
#include "CatalogObject.h"
#include "LevelObject.h"

using namespace std;
using namespace Awesomium;

LevelEditor::LevelEditor()
{
	m_renderWindow = Starter::getRenderWindow();
	m_level = new Level(m_renderWindow);
	m_lastObjectID = 0;
	m_selectedObject = NULL;
	m_action = none;

	// load images
	sf::Texture* texture;
	texture = new sf::Texture();
	texture->loadFromFile("images/bg_editor.png");
	texture->setRepeated(true);
	m_spriteBg.setTexture(*texture);

	m_uiRenderer = new UiRenderer(Starter::getWebCore(), Starter::getWebSession(), m_renderWindow, (sf::Vector2i)Starter::getScreenSize(), "asset://res/editor.html");
	m_uiRenderer->setJSMethodHandler(this);

	// register js methods
	m_uiRenderer->registerMethod("newLevel", false);
	m_uiRenderer->registerMethod("save", false);
	m_uiRenderer->registerMethod("createObject", false);
	m_uiRenderer->registerMethod("objectSelected", false);

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
			Starter::resize(event.size.width, event.size.height);
			m_uiRenderer->resize((sf::Vector2i)Starter::getScreenSize());
			resize();
		}
		else if(event.type == sf::Event::KeyPressed)
		{
			// key has been pressed
			if(event.key.code == sf::Keyboard::Escape)
			{
				// escape has been pressed -> call Menu
				Starter::setGamestate(Starter::Menu);
			}
			else if(event.key.code == sf::Keyboard::S)
			{
				if(m_selectedObject)
					m_action = scale;
			}
			else if(event.key.code == sf::Keyboard::O)
			{
				if(m_selectedObject)
					m_action = opacity;
			}
			else if(event.key.code == sf::Keyboard::M)
			{
				if(m_selectedObject)
					m_action = move;
			}
			else if(event.key.code == sf::Keyboard::R)
			{
				if(m_selectedObject)
					m_action = rotate;
			}
			else if(event.key.code == sf::Keyboard::BackSpace || event.key.code == sf::Keyboard::Delete)
			{
				if(m_selectedObject)
				{
					m_level->removeObject(m_selectedObject);
					m_uiRenderer->executeJavascript(ToWebString(string("") + "removeObject(" + StringHelper::toString(m_selectedObject->getObjectID()) + ");")); 
				}
			}
		}
		else if(event.type == sf::Event::MouseButtonPressed)
		{
			if(m_action == move) m_action = none;
			if(m_action == scale) m_action = none;
			if(m_action == opacity) m_action = none;
			if(m_action == rotate) m_action = none;
		}
		if(!sf::Keyboard::isKeyPressed(sf::Keyboard::Tab))
			m_uiRenderer->handleEvent(event);
	}


	if(m_selectedObject)
	{
		if(m_action == move)
		{
			m_selectedObject->setPosition(sf::Vector2f(m_selectedObject->getPosition().x + mouseDelta.x / Starter::getScreenFactor(), m_selectedObject->getPosition().y + mouseDelta.y / Starter::getScreenFactor()));
		}
		else if(m_action == scale)
		{
			m_selectedObject->setScale(m_selectedObject->getScale() + (mouseDelta.x - mouseDelta.y) / 100.0f);
	
		}
		else if(m_action == opacity)
		{
			m_selectedObject->setOpacity(m_selectedObject->getOpacity() + (mouseDelta.x - mouseDelta.y) / 200.0f);
		}
		else if(m_action == rotate)
		{
			m_selectedObject->setAngle(m_selectedObject->getAngle() + (mouseDelta.x - mouseDelta.y) / 200.0f);
		}
	}

	m_renderWindow->draw(m_spriteBg);
	m_level->tick(elapsedTime);
	if(!sf::Keyboard::isKeyPressed(sf::Keyboard::Tab))
		m_uiRenderer->render();
}

void LevelEditor::resize()
{
	float scale = Starter::getScreenFactor();

	m_spriteBg.setScale(3.2f * scale, 3.2f * scale);
}

void LevelEditor::OnMethodCall(WebView* caller, unsigned int remote_object_id, const WebString& method_name, const JSArray& args)
{
	if(method_name == WSLit("newLevel"))
	{
		
	}
	else if(method_name == WSLit("save"))
	{
		m_level->save(ToString(args.At(0).ToString()));
	}
	else if(method_name == WSLit("createObject"))
	{
		if(args.size() == 2)
		{
			createObject(ToString(args.At(0).ToString()), args.At(1).ToInteger());
		}
	}
	else if(method_name == WSLit("objectSelected"))
	{
		if(args.size() == 1)
		{
			int id = args.At(0).ToInteger();
			list<LevelObject*>::iterator pos = m_level->getObjects()->begin();
			while(pos != m_level->getObjects()->end())
			{
				if((*pos)->getObjectID() == id)
				{
					m_selectedObject = (*pos);
					break;
				}
				pos++;
			}
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
	m_selectedObject = levelObject;
	m_action = move;
}
