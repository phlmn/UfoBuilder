#pragma once

#include <list>
#include <string>
#include <sstream>
#include <iostream>
#include <SFML\Graphics.hpp>
#include <SFGUI\SFGUI.hpp>
#include "StringHelper.h"
#include <Box2D\Box2D.h>
#include "GameObject.h"
#include "LevelEditor.h"
#include "Ufo.h"
#include "UfoEditor.h"
#include "UfoPart.h"
#include "UfoCarriage.h"
#include "UfoCockpit.h"
#include "UfoEngine.h"
#include "UfoFuelTank.h"
#include "Level.h"
#include "Game.h"

class Game;

class Starter
{
public:
	Starter();
	~Starter();

	void run();

	static enum Gamestate
	{
		Menu = 1,
		Ingame,
		Editor
	};

	static const float DEG_TO_RAD;
	static const float RAD_TO_DEG;
	static const float PI;

	void show();
	void hide();

private:
	bool init();
	void tick();
	void cleanup();

	Game* m_game;
	LevelEditor* m_editor;

	sf::Clock m_clock;
	sf::RenderWindow* m_renderWindow;

	sf::Sprite m_spriteBg;

	sf::Font m_fontSegoe;
	sf::Font m_fontSegoeBold;

	sf::Text m_textTitle;

	sfg::SFGUI m_gui;
	sfg::Desktop m_desktop;
	sfg::Window::Ptr m_windowMenu;

	Gamestate m_gamestate;

	void onButtonStartGameClicked();
	void onButtonEditorClicked();
	void onButtonExitClicked();
};
