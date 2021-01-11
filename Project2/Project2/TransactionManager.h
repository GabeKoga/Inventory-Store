#pragma once
#include "Inventory.h"

class TransactionManager
{
	struct Transaction
	{
		Item theItem;
		bool bought;
	};

	Inventory *theInventory;
	SLList<Transaction> theHistory;
public:
	TransactionManager(Inventory &inv);
	void Buy(Item x);
	void Sell(Item x);
	void Undo();
	unsigned int size();
};
