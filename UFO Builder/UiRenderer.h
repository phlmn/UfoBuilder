#pragma once

#include <SFML\Graphics.hpp>
#include <Thor\Graphics.hpp>
#include <Awesomium\WebCore.h>
#include <Awesomium\STLHelpers.h>
#include <Awesomium\BitmapSurface.h>

class UiRenderer
{
public:
	UiRenderer(Awesomium::WebCore* webCore, Awesomium::WebSession* webSession, sf::RenderWindow* renderWindow, sf::Vector2i screenSize, char* url);
	~UiRenderer();

	void render();
	void handleEvent(sf::Event event);
	void setJSMethodHandler(Awesomium::JSMethodHandler* handler);
	void registerMethod(char* name, bool hasReturnValue);

	void executeJavascript(Awesomium::WebString code);
	Awesomium::JSValue executeJavascriptWithResult(Awesomium::WebString code);

	Awesomium::WebView* getWebView();
	void resize(int width, int height);
	void resize(sf::Vector2i size);

private:
	Awesomium::WebCore* m_webCore;
	Awesomium::WebView* m_webView;
	Awesomium::WebSession* m_webSession;

	Awesomium::JSObject* m_appObject;

	thor::BigSprite m_sprite;
	thor::BigTexture m_texture;
	

	sf::RenderWindow* m_renderWindow;

	sf::Vector2i m_screenSize;
};
