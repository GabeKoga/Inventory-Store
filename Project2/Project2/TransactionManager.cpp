#include "TransactionManager.h"



TransactionManager::TransactionManager(Inventory &inv)
{
	theInventory = &inv;
}


void TransactionManager::Buy(Item x) {
	if (theHistory.size() < 5)
	{
		Transaction temp;
		temp.theItem = x;
		temp.bought = true;
		theHistory.addHead(temp);
	}
}

void TransactionManager::Sell(Item x) {
	if (theHistory.size() < 5)
	{
		Transaction temp;
		temp.theItem = x;
		temp.bought = false;
		theHistory.addHead(temp);
	}
}

void TransactionManager::Undo() {
	SLLIter<Transaction> iter(theHistory);
	Item temp; //to adjust cost
	iter.begin();
	if (iter.current().bought) {
		temp = iter.current().theItem;
		temp.cost *= 2;
		theInventory->RemoveItem(temp);
		theHistory.remove(iter);
	}
	else {
		temp = iter.current().theItem;
		temp.cost /= 2;
		theInventory->AddItem(temp);
		theHistory.remove(iter);
	}
}

unsigned int TransactionManager::size() {
	return theHistory.size();
}