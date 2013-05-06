#pragma once

#include <SFML\Graphics.hpp>
#include <Thor\Graphics.hpp>
#include <Awesomium\WebCore.h>
#include <Awesomium\STLHelpers.h>
#include <Awesomium\BitmapSurface.h>

using namespace Awesomium;

class UiRenderer
{
public:
	UiRenderer(WebCore* webCore, WebSession* webSession, sf::RenderWindow* renderWindow, sf::Vector2i screenSize, char* url);
	~UiRenderer();

	void render();
	void handleEvent(sf::Event event);
	void setJSMethodHandler(JSMethodHandler* handler);
	void registerMethod(char* name, bool hasReturnValue);

	WebView* getWebView();
	void resize(int width, int height);
	void resize(sf::Vector2i size);

private:
	WebCore* m_webCore;
	WebView* m_webView;
	WebSession* m_webSession;

	JSObject* m_appObject;

	thor::BigSprite m_sprite;
	thor::BigTexture m_texture;
	

	sf::RenderWindow* m_renderWindow;

	sf::Vector2i m_screenSize;
};
