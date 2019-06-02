#include "Menu.h"

#include <locale.h>
#include <iostream>

using namespace std;

int main()
{
	setlocale(LC_ALL, "Russian");
	Menu M;
	CpuInfo CI;
	CI.getCpuInfo();
	while (true)
	{
		M.showMenu();
		M.getChoice(CI);
		rewind(stdin);
		system("cls");
	}
}