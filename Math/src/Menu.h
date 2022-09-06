#pragma once
#include <initializer_list>


class Menu
{
public:
	static void Run();
	static void UIntMenu();
	static void UIntComparisonMenu();
private:
	static void ClearScreen();
	static bool In(int comand, std::initializer_list<int> il);
};
