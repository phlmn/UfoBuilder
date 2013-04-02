#include "LevelEditor.h"
#include "Starter.h"


LevelEditor::LevelEditor(Starter* starter, sf::RenderWindow* window)
{
	m_starter = starter;
	m_renderWindow = window;

	// load images
	sf::Texture* texture;
	texture = new sf::Texture();
	texture->loadFromFile("images/bg_editor.png");
	m_spriteBg.setTexture(*texture);
	m_spriteBg.scale(2.0f, 2.0f);

	m_uiRenderer = new UiRenderer(starter->getWebCore(), starter->getWebSession(), window, starter->getScreenSize(), "asset://res/editor.html");
}


LevelEditor::~LevelEditor()
{

}

void LevelEditor::tick(sf::Time elapsedTime)
{
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
			m_renderWindow->setView(sf::View(sf::Vector2f(event.size.width / 2.0f, event.size.height / 2.0f), sf::Vector2f((float)event.size.width, (float)event.size.height)));
			m_uiRenderer->resize(event.size.width, event.size.height);
		}
		m_uiRenderer->handleEvent(event);
	}

	m_renderWindow->draw(m_spriteBg);
	m_uiRenderer->render();
}