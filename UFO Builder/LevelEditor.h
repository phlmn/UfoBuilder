#pragma once

#include <SFML\Graphics.hpp>
#include <SFGUI\SFGUI.hpp>

class Starter;

class LevelEditor
{
private:
	Starter* m_starter;

	sf::RenderWindow* m_renderWindow;

	sfg::SFGUI m_gui;

	sfg::Desktop* m_desktop;

public:
	LevelEditor(Starter* starter, sf::RenderWindow* window, sfg::Desktop* desktop);
	~LevelEditor();

	void tick(sf::Time elapsedTime);
	void show();
	void hide();
};
