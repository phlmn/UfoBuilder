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
#include "StringHelper.h"

class CatalogObject;
class LevelObject;
class Level;

class LevelEditor : Awesomium::JSMethodHandler
{
private:
	Starter* m_starter;

	sf::RenderWindow* m_renderWindow;
	sf::Sprite m_spriteBg;

	UiRenderer* m_uiRenderer;

	Level* m_level;
	int m_lastObjectID;

	std::list<CatalogObject*> m_catalogObjects;

	void resize();
	void createObject(std::string id, int layer);

	void OnMethodCall(Awesomium::WebView* caller, unsigned int remote_object_id, const Awesomium::WebString& method_name, const Awesomium::JSArray& args);
	Awesomium::JSValue OnMethodCallWithReturnValue(Awesomium::WebView* caller, unsigned int remote_object_id, const Awesomium::WebString& method_name, const Awesomium::JSArray& args);

public:
	LevelEditor(Starter* starter, sf::RenderWindow* window);
	~LevelEditor();

	void tick(sf::Time elapsedTime);
};
