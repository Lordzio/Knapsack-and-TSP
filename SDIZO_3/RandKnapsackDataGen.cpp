#include "RandKnapsackDataGen.h"
#include "stdafx.h"

RandKnapsackDataGen::RandKnapsackDataGen(unsigned int _knapsack_capacity, unsigned int _items_number, unsigned int _weights_range, unsigned int _values_range)
{
	knapsack_capacity = _knapsack_capacity;

	items_number = _items_number;
	weights_range = _weights_range;
	values_range = _values_range + 1;

	weights = new unsigned int[items_number];
	values = new unsigned int[items_number];

	generateNewItemsSet();

	return;
}

RandKnapsackDataGen::~RandKnapsackDataGen()
{
}

void RandKnapsackDataGen::generateNewItemsSet()
{
	srand(time(NULL));

	for (int i = 0; i < items_number; i++)
	{
		weights[i] = rand() % weights_range + 1;
		values[i] = rand() % (values_range);
	}
	return;
}

void RandKnapsackDataGen::generateNewItemsSet(unsigned int _knapsack_capacity)
{
	generateNewItemsSet(_knapsack_capacity, items_number, weights_range, values_range);
}

void RandKnapsackDataGen::generateNewItemsSet(unsigned int _knapsack_capacity, unsigned int _items_number)
{
	generateNewItemsSet(_knapsack_capacity, _items_number, weights_range, values_range);
}

void RandKnapsackDataGen::generateNewItemsSet(unsigned int _knapsack_capacity, unsigned int _items_number, unsigned int _weights_range, unsigned int _values_range)
{
	if (items_number != _items_number)
	{
		delete[] weights;
		delete[] values;
		items_number = _items_number;

		weights = new unsigned int[items_number];
		values = new unsigned int[items_number];
	}

	knapsack_capacity = _knapsack_capacity;

	weights_range = _weights_range;
	values_range = _values_range + 1;

	generateNewItemsSet();

	return;
}

void RandKnapsackDataGen::saveToFile(std::string fileName)
{
	if (fileName[fileName.length() - 1] != *"t" ||
		fileName[fileName.length() - 2] != *"x" ||
		fileName[fileName.length() - 3] != *"t" ||
		fileName[fileName.length() - 4] != *".")
		fileName.append(".txt");
	std::fstream output;
	output.open(fileName, std::ios::out);
	output << knapsack_capacity << " " << items_number << std::endl;

	for (int i = 0; i < items_number; i++) {

		output << weights[i] << " "; //waga/rozmiar
		output << values[i] << std::endl; //wartoœæ
	}
	output.close();
	return;
}
