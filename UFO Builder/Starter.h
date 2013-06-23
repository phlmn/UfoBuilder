#pragma once

#include <SFML\Graphics.hpp>
#include <Box2D\Box2D.h>
#include <Awesomium\WebCore.h>
#include <Awesomium\STLHelpers.h>
#include <Awesomium\DataPak.h>
#include <SFML\Graphics.hpp>

#include "UiRenderer.h"
#include "StringHelper.h"

class Game;
class LevelEditor;

class Starter : public Awesomium::JSMethodHandler
{
public:
	static enum Gamestate
	{
		Menu = 1,
		Ingame,
		Editor
	};

private:
	bool init();
	void tick();
	void cleanup();

	Game* m_game;
	LevelEditor* m_editor;

	static float screenFactor;

	sf::Clock m_clock; // measures the elapsed time
	sf::Window* m_window; // window that serves a target for OpenGL rendering
	sf::RenderWindow* m_renderWindow; // wrapper for sf::Window, allows easy 2D rendering

	// drawable representation of a texture -> allows to easily display a texture on a render target
	sf::Sprite m_spriteBg;

	// loading character fonts
	sf::Font m_fontSegoe;
	sf::Font m_fontSegoeBold;

	Gamestate m_gamestate;

	Awesomium::WebCore* m_webCore; // manages the lifetime of all WebViews, resource and network connections
	Awesomium::WebSession* m_webSession; // storing all user-generated data (cookies, cache)
	UiRenderer* m_uiRenderer;

	virtual void OnMethodCall(Awesomium::WebView* caller, unsigned int remote_object_id, const Awesomium::WebString& method_name, const Awesomium::JSArray& args); // react on js-method-calls
	virtual Awesomium::JSValue OnMethodCallWithReturnValue(Awesomium::WebView *caller, unsigned int remote_object_id, const Awesomium::WebString &method_name, const Awesomium::JSArray &args);

public:
	Starter();
	~Starter();

	void run();

	static const float DEG_TO_RAD;
	static const float RAD_TO_DEG;
	static const float PI;

	Awesomium::WebCore* getWebCore(); 
	Awesomium::WebSession* getWebSession(); 
	sf::Vector2f getScreenSize(); // manipulating 2 dimensional vectors (x, y)

	static float getScreenFactor(); // scale size (factor to Full HD)

	void setGamestate(Gamestate state);
	void showText(std::string value, int size, float x, float y, bool shadow);

	void resize(int width, int height);
	void toggleFullscreen();
};
