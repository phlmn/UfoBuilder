#include "Game.h"
#include "Ufo.h"

Game::Game(Starter* starter, sf::RenderWindow* window)
{
	m_starter = starter;
	m_ufoEditor = new UfoEditor();
	m_level = new Level(window);
	m_renderWindow = window;

	// load level
	/*
	if(m_level->load("bagdadbahn")) {
	} else {
	}
	*/

	// calculate sprite scales
	resize();
}

Game::~Game()
{
	if(m_ufoEditor) delete m_ufoEditor;
	if(m_level) delete m_level;
}

void Game::tick(sf::Time elapsedTime)
{
	// user event handling
	#pragma region event handling
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
			m_starter->resize(event.size.width, event.size.height);
			resize();
		}
		else if(event.type == sf::Event::KeyPressed)
		{
			// key has been pressed
			if(event.key.code == sf::Keyboard::Escape)
			{
				// escape has been pressed -> call Menu
				m_starter->setGamestate(m_starter->Menu);
			}
		}
		else if(event.type == sf::Event::KeyReleased)
		{
			// key has been released
		}
	}
	#pragma endregion

	float scale = m_starter->getScreenFactor();

	m_level->tick(elapsedTime);
}

void Game::resize()
{
	float scale = m_starter->getScreenFactor();
	if(m_level->getUfo())
		m_level->getUfo()->resize(scale);
}

UfoEditor* Game::getUfoEditor()
{
	return m_ufoEditor;
}

Level* Game::getLevel()
{
	return m_level;
}
