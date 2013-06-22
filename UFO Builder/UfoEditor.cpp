#include "UfoEditor.h"
#include "UfoCatalogPart.h"
#include "Ufo.h"

UfoEditor::UfoEditor(Starter* starter, sf::RenderWindow* window) : LevelEditor(starter, window)
{
	m_ufo = new Ufo();
}


UfoEditor::~UfoEditor()
{
}
