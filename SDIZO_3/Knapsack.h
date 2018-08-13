#pragma once
#include <iostream>
#include <sstream>
#include <fstream>

#include "FileNotFoundException.h"
#include "RandKnapsackDataGen.h"

struct Item {
	unsigned int weight;
	unsigned int value;
	double ratio;
};
class Knapsack
{
private:

	class sackElement {
	public:
		Item it;
		sackElement* next;

		sackElement(Item _it) {
			it = _it;
			next = nullptr;
		}
		~sackElement() {
			if (this->next != nullptr)
				delete next;

		}
	};

	unsigned int capacity;
	int packed_weight;
	int packed_value;

	sackElement* sack = nullptr;
	Item* itemsSet = nullptr;
	int itemsSet_size;

	void quickSort(Item* tab, int left, int right, bool ratio_mode);
	int partition(Item* tab, int left, int right, bool ratio_mode);
	void packItem(Item _it);
public:
	Knapsack();
	Knapsack(int _capacity);
	~Knapsack();

	void loadItemsSet(std::string fileName);
	void loadItemsSet(Item* items, unsigned int n);

	bool greedy_pack(bool ratio_mode);
	bool brute_force_pack();

	void printItemsSet();
	std::string toString();
	void saveToFile(std::string fileName);
	friend std::ostream & operator << (std::ostream & output, Knapsack & knapsack);

};

