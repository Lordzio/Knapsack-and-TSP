#include "stdafx.h"

LARGE_INTEGER startTimer()
{
	LARGE_INTEGER start;
	DWORD_PTR oldmask = SetThreadAffinityMask(GetCurrentThread(), 0);
	QueryPerformanceCounter(&start);
	SetThreadAffinityMask(GetCurrentThread(), oldmask);
	return
		start;
}
LARGE_INTEGER endTimer()
{
	LARGE_INTEGER stop;
	DWORD_PTR oldmask = SetThreadAffinityMask(GetCurrentThread(), 0);
	QueryPerformanceCounter(&stop);
	SetThreadAffinityMask(GetCurrentThread(), oldmask);
	return
		stop;
}


void run_tests_knapsack() {

	LARGE_INTEGER freq;
	QueryPerformanceFrequency(&freq);

	LARGE_INTEGER countStart, countEnd;

	const int n = 5;
	const int b = 3;
	int tests = 100;

	long double bruteWynikiAvg[n][b];
	long double greedyWynikiAvg[n][b];

	int size_range = 50;
	int values_range = 50;
	int N[n] = { 5, 10, 20, 25, 30 };
	double b_ratio[b] = { 0.50, 0.25, 0.10 };
	int B[n][b];

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < b; j++)
		{
			B[i][j] = (int)N[i] * size_range * b_ratio[j];
			bruteWynikiAvg[i][j] = 0;
			greedyWynikiAvg[i][j] = 0;
		}
	}

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < b; j++)
		{
			RandKnapsackDataGen gen = *(new RandKnapsackDataGen(B[i][j], N[i], size_range, values_range));
			gen.saveToFile("knapsack_tests_input");

			Knapsack knapsack = *(new Knapsack());

			if (i == 4)
				tests = 5;
			std::cout << "\nRunning tests for " << N[i] << " elements and capacity " << B[i][j] << std::endl;
			for (int t = 0; t < tests; t++)
			{
				std::cout << ". ";
				//////// 100 tests //////////////

				knapsack.loadItemsSet("knapsack_tests_input");
				bool wynik;
				/*pomiar*/
				countStart = startTimer();
				wynik = knapsack.greedy_pack(true);
				countEnd = endTimer();
				/*pomiar*/
				if (!wynik) {
					throw new IndexOutOfBoundsException("Incorrect result for knapsack greedy.");
				}
				else
					greedyWynikiAvg[i][j] += (long double)(countEnd.QuadPart - countStart.QuadPart);

				knapsack.loadItemsSet("knapsack_tests_input");
				/*pomiar*/
				countStart = startTimer();
				wynik = knapsack.brute_force_pack();
				countEnd = endTimer();
				/*pomiar*/
				if (!wynik) {
					throw new IndexOutOfBoundsException("Incorrect result for salesman brute.");
				}
				else
					bruteWynikiAvg[i][j] += (long double)(countEnd.QuadPart - countStart.QuadPart);

				//////////////////////////////////
			}

			greedyWynikiAvg[i][j] = greedyWynikiAvg[i][j] / (tests*freq.QuadPart);
			bruteWynikiAvg[i][j] = bruteWynikiAvg[i][j] / (tests*freq.QuadPart);
		}

		std::fstream plik_greedy;
		std::fstream plik_brute;

		std::stringstream ssgreedy;
		std::stringstream ssbrute;

		std::string nazwa_greedy;
		std::string nazwa_brute;

		nazwa_greedy.append("knapsack_greedy_");
		nazwa_brute.append("knapsack_brute_");

		ssgreedy << "N_" << N[i] << ".txt";
		ssbrute << "N_" << N[i] << ".txt";

		nazwa_greedy.append(ssgreedy.str());
		nazwa_brute.append(ssbrute.str());

		plik_greedy.open(nazwa_greedy, std::ios::out);
		plik_brute.open(nazwa_brute, std::ios::out);

		for (int j = 0; j < b; j++)
		{
			plik_greedy << greedyWynikiAvg[i][j] << ";";
			plik_brute << bruteWynikiAvg[i][j] << ";";
		}

		plik_greedy.close();
		plik_brute.close();
	}
	///TESTING LOOP END
	return;
}
void run_tests_voyager() {

	LARGE_INTEGER freq;
	QueryPerformanceFrequency(&freq);

	LARGE_INTEGER countStart, countEnd;

	const int n = 5;
	int tests = 10;

	long double bruteWynikiAvg[n];
	long double greedyWynikiAvg[n];

	int values_range = 20;
	int N_brute[n] = { 5, 8, 10, 11, 12 };
	int N[n] = { 10, 50, 100, 200, 500 };

	for (int i = 0; i < n; i++)
	{
		bruteWynikiAvg[i] = 0;
		greedyWynikiAvg[i] = 0;
	}

	RandGraphGen gen = *(new RandGraphGen());
	Towns towns = *(new Towns());

	for (int i = 0; i < n; i++)
	{
		if (i == 3)
			tests = 10;
		if (i == 5)
			tests = 1;

		std::cout << "\nRunning tests for " << N_brute[i] << " towns for brute_force and " << N[i] << " for greedy." << std::endl;

		gen.generate(N[i], values_range);
		gen.saveToFile("voyager_greedy_input");

		gen.generate(N_brute[i], values_range);
		gen.saveToFile("voyager_brute_input");



		for (int t = 0; t < tests; t++)
		{
			std::cout << ". ";
			//////// 100 tests //////////////
			towns.loadTownsMap("voyager_greedy_input");
			int* wynik;
			/*pomiar*/
			countStart = startTimer();
			wynik = towns.greedy(0);
			countEnd = endTimer();
			/*pomiar*/
			if (!wynik) {
				throw new IndexOutOfBoundsException("Incorrect result for salesman greedy.");
			}
			else
				greedyWynikiAvg[i] += (long double)(countEnd.QuadPart - countStart.QuadPart);

			delete[] wynik;


			//delete[] wynik;
			//towns.loadTownsMap("voyager_brute_input");
			/*pomiar*/
			//countStart = startTimer();
			//wynik = towns.brute_force();
			//countEnd = endTimer();

			/*pomiar*/
			//if (!wynik) {
			//throw new IndexOutOfBoundsException("Incorrect result for salesman brute.");
			//}
			//else
			//bruteWynikiAvg[i] += (long double)(countEnd.QuadPart - countStart.QuadPart);

			//////////////////////////////////
		}

		greedyWynikiAvg[i] = greedyWynikiAvg[i] / (tests * freq.QuadPart);
		//greedyWynikiAvg2[i] = greedyWynikiAvg2[i] / (tests * freq.QuadPart);

		bruteWynikiAvg[i] = bruteWynikiAvg[i] / (tests * freq.QuadPart);

	}

	std::fstream plik_greedy;
	std::fstream plik_brute;

	std::string nazwa_greedy;
	std::string nazwa_brute;

	nazwa_greedy.append("voyager_greedy.txt");
	nazwa_brute.append("voyager_brute.txt.");

	plik_greedy.open(nazwa_greedy, std::ios::out);
	plik_brute.open(nazwa_brute, std::ios::out);

	for (int j = 0; j < n; j++)
	{
		plik_greedy << greedyWynikiAvg[j] << ";";
		plik_brute << bruteWynikiAvg[j] << ";";
	}

	plik_greedy << std::endl;

	plik_greedy.close();
	plik_brute.close();
	///TESTING LOOP END
	return;
}

int main() {

	RandGraphGen gen = *(new RandGraphGen());
	Towns town = *(new Towns());
	Knapsack knapsack = *(new Knapsack());
	

	bool end = false;
	bool bad_command = false;
	while (!end) {

		std::cout << "\nMENU GLOWNE\n";
		std::cout << "***************************************************************************\n\n";
		std::cout << "\n***PROBLEM PLECAKOWY***\n";
		std::cout << "1. Wygeneruj plik z danymi dla problemu plecakowego.\n";
		std::cout << "2. Algorytm zachlanny dla problemu plecakowego.\n";
		std::cout << "3. Przeglad zupelny dla problemu plecakowego.\n";
		std::cout << "\n***PROBLEM KOMIWOJAZERA***\n";
		std::cout << "4. Wygeneruj plik z danymi dla problemu komiwojazera.\n";
		std::cout << "5. Algorytm zachlanny dla problemu komiwojazera.\n";
		std::cout << "6. Przeglad zupelny dla problemu komiwojazera.\n";
		std::cout << "\nk. Zakoncz program...\n";

		bool badInsideCommand = false;
		std::cin.clear();
		std::cin.sync();
		char decision;

		if (bad_command)
		{
			std::cout << "Bledny numer opcji! Twoj wybor-> ";
			bad_command = false;

			std::cin >> decision;
		}
		else {
			std::cout << "\nTwoj wybor -> ";
			std::cin >> decision;
		}





		//fflush(stdin);






		switch (decision) {
				  //Generowanie przedmiotów do plecaka
		case '1': {

			int t = 2;
			char* teksty[] = { "pojemnosc plecaka", "liczbe przedmiotow" };

			int* val = new int[t];
			bool blad = false;
			for (int i = 0; i < t; i++)
			{
				std::cout << "Podaj " << teksty[i] << ": ";

				std::cin >> val[i];

				if (val[i] <= 0)
				{
					std::cout << "BLAD! Pojemnosc nie moze przyjac takiej wartosci!\n";
					blad = true;
					break;
				}
			}
			if (blad)
				break;

			int wagi = (int)(val[0] * 0.75);
			int wartosci = 50;

			RandKnapsackDataGen knapgen = *(new RandKnapsackDataGen(val[0], val[1], wagi, wartosci));
			std::cout << "Podaj nazwe pliku do zapisu:  ";
			std::string nazwa;
			std::cin >> nazwa;

			try {
				knapgen.saveToFile(nazwa);
			}
			catch (std::runtime_error err) {
				std::cout << "ZAPIS NIEUDANY! " << err.what() << std::endl;
				break;
			}
			std::cout << "Zapis udany!\n";

			break;
		}
				  //Algorytm zach³anny plecak
		case '2': {

			std::cout << "Podaj nazwe pliku do odczytu zbioru przedmiotow:  ";
			std::string nazwa;
			std::cin >> nazwa;

			try {
				knapsack.loadItemsSet(nazwa);
			}
			catch (std::runtime_error err) {
				std::cout << "Odczyt nieudany!\n";
				std::cout << err.what();
				break;
			}
			std::cout << "Odczyt udany!\n";
			knapsack.printItemsSet();
			std::cout << "Uruchamiam algorytm zachlanny!\n";
			if (knapsack.greedy_pack(true))
				std::cout << "Wynik:\n" << knapsack;
			break;
		}
				  //Przegl¹d zupe³ny plecak
		case '3': {
			std::cout << "Podaj nazwe pliku do odczytu zbioru przedmiotow:  ";
			std::string nazwa;
			std::cin >> nazwa;

			try {
				knapsack.loadItemsSet(nazwa);
			}
			catch (std::runtime_error err) {
				std::cout << "Odczyt nieudany!\n";
				std::cout << err.what();
				break;
			}
			std::cout << "Odczyt udany!\n";
			knapsack.printItemsSet();
			std::cout << "Uruchamiam przeglad zupelny!\n";
			if (knapsack.brute_force_pack())
				std::cout << "Wynik:\n" << knapsack;
			break;
		}
				  //Generowanie mapy miast
		case '4': {

			int N;
			std::cout << "Podaj liczbe miast: ";

			std::cin >> N;

			if (N <= 0)
			{
				std::cout << "BLAD! Pojemnosc nie moze przyjac takiej wartosci!\n";
				break;
			}

			gen.generate(N, 2 * N);

			std::cout << "Podaj nazwe pliku do zapisu:  ";
			std::string nazwa;
			std::cin >> nazwa;

			try {
				gen.saveToFile(nazwa);
			}
			catch (std::runtime_error err) {
				std::cout << "ZAPIS NIEUDANY! " << err.what() << std::endl;
				break;
			}
			std::cout << "Zapis udany!\n";
			break;
		}
				  //Algorytm zach³anny komi
		case '5': {
			std::cout << "Podaj nazwe pliku do odczytu mapy miast:  ";
			std::string nazwa;
			std::cin >> nazwa;

			try {
				town.loadTownsMap(nazwa);
			}
			catch (std::runtime_error err) {
				std::cout << "Odczyt nieudany!\n";
				std::cout << err.what();
				break;
			}
			std::cout << "Odczyt udany!" << town << "\nUruchamiam algorytm zachlanny!\n";
			int* wynik = town.greedy(0);
			if (wynik) {
				std::cout << "Wynik:\n";
				for (int i = 2; i < wynik[0] + 2; i++)
				{
					if (i < wynik[0] + 1)
						std::cout << wynik[i] << " -> ";
					else
						std::cout << wynik[i] << std::endl;
				}
				std::cout << "Koszt = " << wynik[1] << std::endl;
			}
			else
				std::cout << "Blad algorytmu!\n";

			break;
		}
				  //Przegl¹d zupe³ny komi
		case '6': {
			std::cout << "Podaj nazwe pliku do odczytu mapy miast:  ";
			std::string nazwa;
			std::cin >> nazwa;

			try {
				town.loadTownsMap(nazwa);
			}
			catch (std::runtime_error err) {
				std::cout << "Odczyt nieudany!\n";
				std::cout << err.what();
				break;
			}
			std::cout << "Odczyt udany!" << town << "\nUruchamiam przeglad zupelny!\n";
			int* wynik = town.brute_force();
			if (wynik) {
				std::cout << "Wynik:\n";

				for (int i = 2; i < wynik[0] + 2; i++)
				{
					if (i < wynik[0] + 1)
						std::cout << wynik[i] << " -> ";
					else
						std::cout << wynik[i] << std::endl;
				}
				std::cout << "Koszt = " << wynik[1] << std::endl;
			}
			else
				std::cout << "Blad algorytmu!\n";

			break;
		}

		case 'k': {
			end = true;
			break;
		}

		default:
			bad_command = true;

		}
	}

	return 0;
}