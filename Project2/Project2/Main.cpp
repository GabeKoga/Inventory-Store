//includes
#include <iostream>
#include <iomanip>
#include "SLList.h"
#include "DynArray.h"
#include "Store.h"
#include "Inventory.h"
#include "TransactionManager.h"
////////////////////////////////////////////////////////////////////////////////////////////////
// LEAK DETECTION
////////////////////////////////////////////////////////////////////////////////////////////////
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

using namespace std;

int main(void)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	Store store;
	Inventory player;
	TransactionManager manager(player);
	store.Load("items.shp");

	while (true)
	{
		int input;
		player.Display();
		store.Display();
		cout << "Which action do you want to do? (1 - 6)" << endl;
		cout << "1. Buy an item from the store" << endl;
		cout << "2. Sort the store items" << endl;
		cout << "3. Search an item" << endl;
		cout << "4. Sell an item from your inventory" << endl;
		cout << "5. Undo the last transaction(" << manager.size() << ")\n";
		cout << "6. Exit\n";
		while (true)
		{
			if (cin >> input)
			{
				system("cls");
				switch (input)
				{
				case(1):
					unsigned int buy;
					store.Display();
					cout << "What item do you want to buy? (1-" << store.size() << ")" << endl;
					while (true)
					{
						if (cin >> buy && buy <= store.size() && buy > 0)
						{
							player.AddItem(store.GetItem(buy - 1));
							manager.Buy(store.GetItem(buy - 1));
							break;
						}
						else {
							cin.clear();
							cin.ignore(INT_MAX, '\n');
							cout << "invalid Input\n";
						}
					}
					break;
				case(2):
					int sort;
					cout << "Sort by:" << endl;
					cout << "1. Type\n2. Name\n3. Cost\n4. Weight\n";
					cin >> sort;
					cout << endl;
					switch (sort)
					{
					case(1):
						store.SortByType();
						break;
					case(2):
						store.SortByName();
						break;
					case(3):
						store.SortByPrice();
						break;
					case(4):
						store.SortByWeight();
						break;
					default:
						cout << "Invalid input";
						break;
					}
					break;
				case(3):
					char search[16];
					cout << "What item are you looking for?" << endl;
					cin >> search;
					system("cls");
					cout << "NAME\t\t\tTYPE\t\t\tCOST\tWEIGHT" << endl;
					if (store.Search(search)) {
						cout << "Successfully found the item" << endl;
					}
					else {
						cout << "Item not found" << endl;
					}
					system("pause");
					break;
				case(4):
					unsigned int sell;
					player.Display();
					cout << "What item do you want to sell? (1-" << player.size() << ")" << endl;
					if (cin >> sell && sell <= player.size() && sell > 0)
					{
						Item temp = player.GetItem(sell);
						player.RemoveItem(temp);
						manager.Sell(temp);
						break;
					}
					else {
						cin.clear();
						cin.ignore(INT_MAX, '\n');
						cout << "invalid Input\n";
					}
					break;
				case(5):
					if (manager.size() != 0)
					{
						manager.Undo();
					}
					break;
				case(6):
					return 0;
				default:
					cout << "Invalid input\n";
					break;
				}
				break;
			}
			else
			{
				cin.clear();
				cin.ignore(INT_MAX, '\n');
				cout << "invalid Input\n";
			}
		}
	}
}
