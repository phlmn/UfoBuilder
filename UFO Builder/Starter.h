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

	static float m_screenFactor;

	sf::Clock m_clock; // measures the elapsed time
	sf::Window* m_window; // window that serves a target for OpenGL rendering
	static sf::RenderWindow* m_renderWindow; // wrapper for sf::Window, allows easy 2D rendering

	// drawable representation of a texture -> allows to easily display a texture on a render target
	sf::Sprite m_spriteBg;

	// loading character fonts
	sf::Font m_fontSegoe;
	sf::Font m_fontSegoeBold;

	static Gamestate m_gamestate;

	static Awesomium::WebCore* m_webCore; // manages the lifetime of all WebViews, resource and network connections
	static Awesomium::WebSession* m_webSession; // storing all user-generated data (cookies, cache)
	UiRenderer* m_uiRenderer;

	virtual void OnMethodCall(Awesomium::WebView* caller, unsigned int remote_object_id, const Awesomium::WebString& method_name, const Awesomium::JSArray& args); // react on js-method-calls
	virtual Awesomium::JSValue OnMethodCallWithReturnValue(Awesomium::WebView *caller, unsigned int remote_object_id, const Awesomium::WebString &method_name, const Awesomium::JSArray &args);

	void resizeSprites();

public:
	Starter();
	~Starter();

	void run();

	static const float DEG_TO_RAD;
	static const float RAD_TO_DEG;
	static const float PI;

	static Awesomium::WebCore* getWebCore(); 
	static Awesomium::WebSession* getWebSession(); 
	static sf::Vector2f getScreenSize(); // manipulating 2 dimensional vectors (x, y)

	static float getScreenFactor(); // scale size (factor to Full HD)

	static void setGamestate(Gamestate state);
	void showText(std::string value, int size, float x, float y, bool shadow);

	static void resize(int width, int height);
	static void toggleFullscreen();

	static sf::RenderWindow* getRenderWindow();
};
