#pragma once

#include <list>
#include <string>
#include <sstream>
#include <iostream>
#include <SFML\Graphics.hpp>
#include "StringHelper.h"
#include <Box2D\Box2D.h>
#include "GameObject.h"
#include "LevelEditor.h"
#include "Ufo.h"
#include "UfoEditor.h"
#include "UfoPart.h"
#include "UfoCarriage.h"
#include "UfoCockpit.h"
#include "UfoEngine.h"
#include "UfoFuelTank.h"
#include "Level.h"
#include "Game.h"
#include <Awesomium\WebCore.h>
#include <Awesomium\STLHelpers.h>
#include <Awesomium\BitmapSurface.h>
#include <Awesomium\DataPak.h>
#include <SFML\Graphics.hpp>
#include "UiRenderer.h"

class Game;

using namespace Awesomium;
using namespace std;

class Starter : public JSMethodHandler
{
public:
	Starter();
	~Starter();

	void run();

	static enum Gamestate
	{
		Menu = 1,
		Ingame,
		Editor
	};

	static const float DEG_TO_RAD;
	static const float RAD_TO_DEG;
	static const float PI;

	WebCore* getWebCore();
	WebSession* getWebSession();
	sf::Vector2f getScreenSize();

	float getScreenFactor();

	void resize(int width, int height);
	void toggleFullscreen();

private:
	bool init();
	void tick();
	void cleanup();

	Game* m_game;
	LevelEditor* m_editor;

	float m_screenFactor;

	sf::Clock m_clock;
	sf::Window* m_window;
	sf::RenderWindow* m_renderWindow;

	sf::Sprite m_spriteBg;

	sf::Font m_fontSegoe;
	sf::Font m_fontSegoeBold;

	Gamestate m_gamestate;

	WebCore* m_webCore;
	WebSession* m_webSession;
	UiRenderer* m_uiRenderer;

	virtual void OnMethodCall(WebView* caller, unsigned int remote_object_id, const WebString& method_name, const JSArray& args);
	virtual JSValue OnMethodCallWithReturnValue(Awesomium::WebView *caller, unsigned int remote_object_id, const Awesomium::WebString &method_name, const Awesomium::JSArray &args);
};
