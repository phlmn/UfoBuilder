#include "LevelEditor.h"


LevelEditor::LevelEditor(Starter* starter, sf::RenderWindow* window, sfg::Desktop* desktop)
{
	m_starter = starter;
	m_renderWindow = window;
	m_desktop = desktop;
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
}

void LevelEditor::show()
{

}

void LevelEditor::hide()
{

}
