#pragma once
#include "Store.h"
#include "SLList.h"

class Inventory
{
	SLList <Item> items;
	unsigned int coins, weight, maxWeight;

public:
	Inventory();
	~Inventory();

	void AddItem(Item x);
	void RemoveItem(Item x);
	void Display();
	unsigned int size();
	Item GetItem(unsigned int index);
};
