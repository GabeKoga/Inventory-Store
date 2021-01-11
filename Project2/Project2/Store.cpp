#include "Store.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <locale>

using namespace std;

Store::Store() {

}

Store::~Store() {
	contents.~DynArray();
}

void Store::Load(const char * path) {
	ifstream fin;
	fin.open(path);
	Item iItem; //input Item

	if (fin.is_open()) {
		fin >> sof;
		while (!fin.eof())
		{
			fin >> iItem.type;
			fin >> iItem.name;
			fin >> iItem.cost;
			fin >> iItem.weight;

			contents.append(iItem);
		}
		fin.close();
	}
	else {
		cout << "File not properly opened";
	}
}

void Store::SortByPrice() {
	int index;
	Item temp;
	for (unsigned int i = 1; i < contents.size(); i++) {
		temp = contents[i];
		index = i - 1;
		while (index >= 0 && contents[index].cost > temp.cost) {
			contents[index + 1] = contents[index];
			index--;
		}
		contents[index + 1] = temp;
	}
}

void Store::SortByWeight() {
	int index;
	Item temp;
	for (unsigned int i = 1; i < contents.size(); i++) {
		temp = contents[i];
		index = i - 1;
		while (index >= 0 && contents[index].weight > temp.weight) {
			contents[index + 1] = contents[index];
			index--;
		}
		contents[index + 1] = temp;
	}
}

void Store::SortByType() {
	int index;
	Item temp;
	for (unsigned int i = 1; i < contents.size(); i++) {
		temp = contents[i];
		index = i - 1;
		while (index >= 0 && contents[index].type[0] > temp.type[0]) {
			contents[index + 1] = contents[index];
			index--;
		}
		contents[index + 1] = temp;
	}
}

void Store::SortByName() {
	int index;
	Item temp;
	for (unsigned int i = 1; i < contents.size(); i++) {
		temp = contents[i];
		index = i - 1;
		while (index >= 0 && contents[index].name[0] > temp.name[0]) {
			contents[index + 1] = contents[index];
			index--;
		}
		contents[index + 1] = temp;
	}
}

bool Store::Search(const char * name) {
	locale loc;
	bool doIt; 
	unsigned int count = 0;
	for (unsigned int i = 0; i < contents.size(); i++) {
		doIt = true;
		for (unsigned int j = 0; name[j] != '\0'; j++) {
			if (tolower(name[j], loc) != tolower(contents[i].name[j], loc)) {
				doIt = false;
				break;
			}
		}
		if (doIt)
		{
			count++;
			cout << setw(24) << left << contents[i].name << setw(24) << contents[i].type << setw(8) << contents[i].cost << contents[i].weight << endl;
		}
	}
	if (count == 0) {
		return false;
	}
	else {
		return true;
	}
}

void Store::Display() {
	cout << "-------------------------------STORE-------------------------------" << endl;
	cout << "INDEX\tNAME\t\t\tTYPE\t\t\tCOST\tWEIGHT" << endl;
	for (unsigned int i = 0; i < contents.size(); i++) {
		cout << (i+1) << ".\t" << setw(24) << left << contents[i].name << setw(24) << contents[i].type << setw(8) << contents[i].cost << contents[i].weight << endl;
	}
}

unsigned int Store::size() {
	return sof;
}

Item Store::GetItem(unsigned int index) {
	return contents.operator[](index);
}