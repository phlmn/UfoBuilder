#pragma once

#include <SFML\Graphics.hpp>
#include <Awesomium\WebCore.h>
#include <Awesomium\STLHelpers.h>
#include "UiRenderer.h"

class Starter;

using namespace Awesomium;

class LevelEditor
{
private:
	Starter* m_starter;

	sf::RenderWindow* m_renderWindow;

	sf::Sprite m_spriteBg;

	UiRenderer* m_uiRenderer;

public:
	LevelEditor(Starter* starter, sf::RenderWindow* window);
	~LevelEditor();

	void tick(sf::Time elapsedTime);
};
