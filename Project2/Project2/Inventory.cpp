#include "Inventory.h"
#include <iostream>
#include <iomanip>

using namespace std;

Inventory::Inventory()
{
	coins = 5000;
	weight = 0;
	maxWeight = 50;
}

Inventory::~Inventory()
{
	items.~SLList();
}

void Inventory::AddItem(Item x) {
	if (x.cost > coins)
	{
		cout << "The player does not have enough money" << endl;
		system("pause");
	}
	else if (x.weight > maxWeight - weight)
	{
		cout << "The item is too heavy for the player" << endl;
		system("pause");
	}
	else {
		items.addHead(x);
		coins -= x.cost;
		weight += x.weight;
	}
}
void Inventory::RemoveItem(Item x) {
	SLLIter<Item> iter(items);
	bool correctWord;

	for (iter.begin(); !iter.end(); iter.operator++())
	{
		correctWord = true;
		for (unsigned int i = 0; x.name[i] != '\0'; i++) {
			if (x.name[i] != iter.current().name[i]) {
				correctWord = false;
				break;
			}
		}
		if (correctWord)
		{
			items.remove(iter);
			coins += (x.cost / 2);
			weight -= x.weight;
			return;
		}
	}
	cout << "Item not found in inventory\n";
	system("pause");
}
void Inventory::Display() {
	SLLIter<Item> iter(items);
	unsigned int index = 1;
	cout << "PLAYER---------------------------MONEY: " << coins << "\tWEIGHT: " << weight << "/" << maxWeight << endl;
	cout << "INDEX\tNAME\t\t\tTYPE\t\t\tCOST\tWEIGHT" << endl;
	for (iter.begin(); !iter.end(); iter.operator++()) {
		Item temp = iter.current();
		cout << (index) << ".\t" << setw(24) << left << temp.name << setw(24) << temp.type << setw(8) << temp.cost << temp.weight << endl;
		index++;
	}
}
unsigned int Inventory::size() {
	return items.size();
}
Item Inventory::GetItem(unsigned int index) {
	SLLIter<Item> iter(items);
	unsigned int it = 1;

	for (iter.begin(); it != index && !iter.end(); it++)
	{
		iter.operator++();
	}
	return iter.current();
}