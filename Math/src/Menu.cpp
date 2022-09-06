#include "Menu.h"
#include "UInt.h"
#include "Benchmarking.h"
#include "Alghoritm/Factorial.h"

#include <iostream>
#include <array>


void Menu::Run()
{
	std::cout << std::boolalpha;
	int comand;
	do {
		std::cout << "0 -> EXIT" << std::endl;
		std::cout << "1 -> UInt" << std::endl;
		std::cout << "Enter a comand: "; std::cin >> comand;

		ClearScreen();

		switch (comand)
		{
		case 1:
			UIntMenu();
		break;
		}

	} while (comand);
	std::cout << std::noboolalpha;
}

void Menu::UIntMenu()
{
	int comand;
	do {
		std::cout << "UInt Menu" << std::endl;
		std::cout << "0 -> EXIT" << std::endl;
		std::cout << "1 -> Sum between 2 numbers" << std::endl;
		std::cout << "2 -> Sum of all numbers in given interval [a, b)" << std::endl;
		std::cout << "3 -> Product between 2 numbers" << std::endl;
		std::cout << "4 -> Product of all numbers in given interval [a, b)" << std::endl;
		std::cout << "5 -> n!" << std::endl;
		std::cout << "6 -> Difference between 2 numbers" << std::endl;
		std::cout << "7 -> Comparison of 2 numbers" << std::endl;
		std::cout << "Enter a comand: "; std::cin >> comand;
		ClearScreen();

		switch (comand)
		{
		case 1:
		{
			UInt a, b;
			std::cout << "a = "; std::cin >> a;
			std::cout << "b = "; std::cin >> b;

			BENCHMARKING();
			std::cout << a << " + " << b << " = " << a + b << std::endl;
		} break;
		case 2:
		{
			UInt a, b;
			std::cout << "a = "; std::cin >> a;
			std::cout << "b = "; std::cin >> b;

			BENCHMARKING();
				UInt sum = 0;
			for (UInt i = a; i < b; i++)
				sum += i;
			std::cout << "Sum of all numbers in given interval [" << a << ", " << b << ") = " << sum << std::endl;
		} break;
		case 3:
		{
			UInt a, b;
			std::cout << "a = "; std::cin >> a;
			std::cout << "b = "; std::cin >> b;

			BENCHMARKING();
			std::cout << a << " * " << b << " = " << a * b << std::endl;
		}
			break;
		case 4:
		{
			UInt a, b;
			std::cout << "a = "; std::cin >> a;
			std::cout << "b = "; std::cin >> b;

			BENCHMARKING();
			UInt prod = 1;
			for (UInt i = a; i < b; i++)
				prod *= i;
			std::cout << "Product of all numbers in given interval [" << a << ", " << b << ") = " << prod << std::endl;
		} break;
		case 5:
		{
			UInt n;
			std::cout << "n = "; std::cin >> n;

			BENCHMARKING();
			UInt fact = Factorial::Run(n);
			std::cout << n << "! = " << fact << std::endl;
		} break;
		case 6:
		{
			UInt a, b;

			std::cout << "a = "; std::cin >> a;
			std::cout << "b = "; std::cin >> b;

			BENCHMARKING();
			std::cout << a << " - " << b << " = " << a - b << std::endl;
		} break;
		case 7:
		{
			UIntComparisonMenu();
		} break;
		}

		if (!In(comand, { 0, 7 }))
		{
			std::cout << "Press enter to continue...";
			std::cin.get();
			std::cin.get();
		}
		ClearScreen();
	} while (comand);
}

void Menu::UIntComparisonMenu()
{
	int comand;
	do {
		std::cout << "UInt Comparison Menu" << std::endl;
		std::cout << "0 -> EXIT" << std::endl;
		std::cout << "1 -> a < b" << std::endl;
		std::cout << "2 -> a > b" << std::endl;
		std::cout << "3 -> a <= b" << std::endl;
		std::cout << "4 -> a >= b" << std::endl;
		std::cout << "5 -> a == b" << std::endl;
		std::cout << "6 -> a != b" << std::endl;
		std::cout << "Enter a comand: "; std::cin >> comand;
		ClearScreen();

		if (comand > 0 && comand < 7)
		{
			UInt a, b;
			std::cout << "a = "; std::cin >> a;
			std::cout << "b = "; std::cin >> b;

			switch (comand)
			{
			case 1:
			{
				BENCHMARKING();
				std::cout << a << " < " << b << " -> " << (a < b) << std::endl;
			} break;
			case 2:
			{
				BENCHMARKING();
				std::cout << a << " > " << b << " -> " << (a > b) << std::endl;
			} break;
			case 3:
			{
				BENCHMARKING();
				std::cout << a << " <= " << b << " -> " << (a <= b) << std::endl;
			} break;
			case 4:
			{
				BENCHMARKING();
				std::cout << a << " >= " << b << " -> " << (a >= b) << std::endl;
			} break;
			case 5:
			{
				BENCHMARKING();
				std::cout << a << " == " << b << " -> " << (a == b) << std::endl;
			} break;
			case 6:
			{
				BENCHMARKING();
				std::cout << a << " != " << b << " -> " << (a != b) << std::endl;
			} break;
			}

			std::cout << "Press enter to continue...";
			std::cin.get();
			std::cin.get();
			ClearScreen();
		}
		
	} while (comand);
}

void Menu::ClearScreen()
{
	system("CLS");
}

bool Menu::In(int comand, std::initializer_list<int> il)
{
	for (auto el : il)
	{
		if (el == comand)
			return true;
	}
	return false;
}
