#pragma once

#include <list>

class UfoCatalogObject;

class UfoEditor
{
private:
	std::list<UfoCatalogObject*> m_ufoCatalogObjects;
public:
	UfoEditor();
	~UfoEditor();
};
