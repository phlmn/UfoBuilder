#include "UiRenderer.h"


UiRenderer::UiRenderer(WebCore* webCore, WebSession* webSession, sf::RenderWindow* renderWindow, sf::Vector2i screenSize, char* url)
{
	m_webCore = webCore;
	m_screenSize = screenSize;
	m_renderWindow = renderWindow;
	m_webSession = webSession;

	m_webView = m_webCore->CreateWebView(m_screenSize.x, m_screenSize.y, m_webSession);
	m_webView->SetTransparent(true);

	m_webView->LoadURL(WebURL(WSLit(url)));
}

UiRenderer::~UiRenderer()
{

}

void UiRenderer::render()
{
	if(!m_webView->IsLoading())
	{
		BitmapSurface* bitmapSurface = (BitmapSurface*)m_webView->surface();

		if(bitmapSurface != NULL && bitmapSurface->is_dirty())
		{
			size_t size = bitmapSurface->row_span() * bitmapSurface->height();
			std::vector<sf::Uint8> charBuffer;
			charBuffer.resize(size);

			sf::Uint8* charPtr = &charBuffer[0];

			bitmapSurface->CopyTo(charPtr, bitmapSurface->row_span(), 4, true, false);
			
			sf::Image image;
			image.create(m_screenSize.x, m_screenSize.y, charPtr);
			
			m_texture.loadFromImage(image);

			m_sprite.setTexture(m_texture);
		}
		m_renderWindow->draw(m_sprite);
	}		
}

WebView* UiRenderer::getWebView()
{
	return m_webView;
}

void UiRenderer::handleEvent(sf::Event event)
{
	if(event.type == sf::Event::MouseButtonPressed)
	{
		if(event.mouseButton.button == sf::Mouse::Button::Left)
		{
			m_webView->InjectMouseDown(MouseButton::kMouseButton_Left);
		}
		else if(event.mouseButton.button == sf::Mouse::Button::Middle)
		{
			m_webView->InjectMouseDown(MouseButton::kMouseButton_Middle);
		}
		else if(event.mouseButton.button == sf::Mouse::Button::Right)
		{
			m_webView->InjectMouseDown(MouseButton::kMouseButton_Right);
		}
	}
	else if(event.type == sf::Event::MouseButtonReleased)
	{
		if(event.mouseButton.button == sf::Mouse::Button::Left)
		{
			m_webView->InjectMouseUp(MouseButton::kMouseButton_Left);
		}
		else if(event.mouseButton.button == sf::Mouse::Button::Middle)
		{
			m_webView->InjectMouseUp(MouseButton::kMouseButton_Middle);
		}
		else if(event.mouseButton.button == sf::Mouse::Button::Right)
		{
			m_webView->InjectMouseUp(MouseButton::kMouseButton_Right);
		}
	}
	else if(event.type == sf::Event::MouseMoved)
	{
		m_webView->InjectMouseMove(event.mouseMove.x, event.mouseMove.y);
	}
}

void UiRenderer::setJSMethodHandler(JSMethodHandler* handler)
{
	m_webView->set_js_method_handler(handler);
}

void UiRenderer::registerMethod(char* name, bool hasReturnValue)
{
	//TODO: use a more beautiful way
	JSValue result = m_webView->CreateGlobalJavascriptObject(WSLit("App"));
	m_appObject = &result.ToObject();
	m_appObject->SetCustomMethod(WSLit(name), hasReturnValue);
}

void UiRenderer::resize(int width, int height)
{
	m_screenSize = sf::Vector2i(width, height);
	m_webView->Resize(width, height);
}
