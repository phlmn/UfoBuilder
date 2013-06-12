#pragma once

#include <SFML\Graphics.hpp>
#include <Awesomium\WebCore.h>
#include <Awesomium\STLHelpers.h>

#include <list>
#include "UiRenderer.h"
#include "Starter.h"
#include "LevelObject.h"
#include <iostream>
#include <fstream>
#include <string>

class Level;

class LevelEditor : JSMethodHandler
{
private:
	Starter* m_starter;

	sf::RenderWindow* m_renderWindow;
	sf::Sprite m_spriteBg;

	UiRenderer* m_uiRenderer;

	Level* m_level;

	std::list<CatalogObject*> m_catalogObjects;

	void resize();
	void createObject(int layer, int id);

	void OnMethodCall(WebView* caller, unsigned int remote_object_id, const WebString& method_name, const JSArray& args);
	JSValue OnMethodCallWithReturnValue(WebView* caller, unsigned int remote_object_id, const WebString& method_name, const JSArray& args);

public:
	LevelEditor(Starter* starter, sf::RenderWindow* window);
	~LevelEditor();

	void tick(sf::Time elapsedTime);
};
