#pragma once

#include "LevelEditor.h"

class UfoCatalogPart;
class Ufo;

class UfoEditor : public LevelEditor
{
private:
	Ufo* m_ufo;
public:
	UfoEditor(Starter* starter, sf::RenderWindow* window);
	~UfoEditor();
};
