#include "LevelEditor.h"


LevelEditor::LevelEditor(Starter* starter, sf::RenderWindow* window, sfg::Desktop* desktop)
{
	m_starter = starter;
	m_renderWindow = window;
	m_desktop = desktop;

	// load images
	sf::Texture* texture;
	texture = new sf::Texture();
	texture->loadFromFile("images/bg_editor.png");
	m_spriteBg.setTexture(*texture);
	m_spriteBg.scale(2.0f, 2.0f);

	sf::Texture* texture2;
	texture2 = new sf::Texture();
	texture2->loadFromFile("images/bg_editor_sidebar.png");
	m_sidebarBg.setTexture(*texture2);
	m_sidebarBg.setScale(0.7f, 0.7f);
	m_sidebarBg.setPosition(0.0f, 40.0f);
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
		m_desktop->HandleEvent(event);
		if (event.type == sf::Event::Closed)
		{
			// the close button was clicked
			m_renderWindow->close();
		}
		else if(event.type == sf::Event::Resized)
		{
			// the windows has been resized
			m_renderWindow->setView(sf::View(sf::Vector2f(event.size.width / 2.0f, event.size.height / 2.0f), sf::Vector2f((float)event.size.width, (float)event.size.height)));
		}
	}

	m_renderWindow->draw(m_spriteBg);
	m_renderWindow->draw(m_sidebarBg);
}

void LevelEditor::show()
{

}

void LevelEditor::hide()
{

}
