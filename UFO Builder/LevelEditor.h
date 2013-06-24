#pragma once

#include <SFML\Graphics.hpp>
#include <Awesomium\WebCore.h>
#include <Awesomium\STLHelpers.h>

#include <list>
#include "UiRenderer.h"
#include "Starter.h"
#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include "StringHelper.h"

class CatalogObject;
class LevelObject;
class Level;

class LevelEditor : Awesomium::JSMethodHandler
{
private:
	enum Action
	{
		none,
		move,
		scale,
		opacity,
		rotate
	};

	sf::RenderWindow* m_renderWindow;
	sf::Sprite m_spriteBg;

	Action m_action;

	UiRenderer* m_uiRenderer;

	Level* m_level;
	int m_lastObjectID;
	sf::Vector2i m_mouseLastPos;

	std::list<CatalogObject*> m_catalogObjects;

	LevelObject* m_selectedObject;

	void resize();
	void createObject(std::string id, int layer);

	void OnMethodCall(Awesomium::WebView* caller, unsigned int remote_object_id, const Awesomium::WebString& method_name, const Awesomium::JSArray& args);
	Awesomium::JSValue OnMethodCallWithReturnValue(Awesomium::WebView* caller, unsigned int remote_object_id, const Awesomium::WebString& method_name, const Awesomium::JSArray& args);

public:
	LevelEditor();
	~LevelEditor();

	void tick(sf::Time elapsedTime);
};
