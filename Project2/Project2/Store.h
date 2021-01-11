#pragma once
#include "DynArray.h"


//item
struct Item {
	char type[16];
	char name[16];
	unsigned int cost;
	unsigned int weight;
};

class Store
{
	DynArray<Item> contents;
	unsigned int sof; // size of file

public:

	Store();
	~Store();

	void Load(const char * path);
	void SortByType();
	void SortByName();
	void SortByPrice();
	void SortByWeight();
	void Display();
	bool Search(const char * name);
	unsigned int size();
	Item GetItem(unsigned int index);
};

