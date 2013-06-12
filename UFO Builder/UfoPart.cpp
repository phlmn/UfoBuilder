#include "UfoPart.h"


UfoPart::UfoPart() : LevelObject()
{
	
}

UfoPart::UfoPart(UfoCatalogPart gameObject) : LevelObject(gameObject)
{

}

UfoPart::UfoPart(UfoCatalogPart gameObject, int layer, sf::Vector2f position, float scale, float opacity, float angle) : LevelObject(gameObject, layer, position, scale, opacity, angle) 
{

}


UfoPart::~UfoPart()
{

}
