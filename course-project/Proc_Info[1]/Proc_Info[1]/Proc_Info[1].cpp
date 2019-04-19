// Proc_Info[1].cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#define _WIN32_WINNT 0x0600
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <stdexcept>
#include <Windows.h>
#include <powrprof.h>
#include <powerbase.h>
#include <vector>
#pragma comment(lib, "PowrProf.lib")



typedef struct _PROCESSOR_POWER_INFORMATION {
	ULONG  Number;
	ULONG  MaxMhz;
	ULONG  CurrentMhz;
	ULONG  MhzLimit;
	ULONG  MaxIdleState;
	ULONG  CurrentIdleState;
} PROCESSOR_POWER_INFORMATION, *PPROCESSOR_POWER_INFORMATION;


using namespace std;


int main(int argc, char* argv[])	{

	SYSTEM_INFO si = { 0 };
	GetNativeSystemInfo(&si);
	std::vector<PROCESSOR_POWER_INFORMATION> powerInformationVector(si.dwNumberOfProcessors);
	DWORD dwSize = sizeof(PROCESSOR_POWER_INFORMATION)*si.dwNumberOfProcessors; //* si.dwNumberOfProcessors;
	
	do
	{
		CallNtPowerInformation(ProcessorInformation, NULL, 0, &powerInformationVector[0], dwSize);
		cout << "Max Mhz: " << powerInformationVector[0].MaxMhz << endl;
		cout << "Current Mhz: " << powerInformationVector[0].CurrentMhz << endl;
		cout << "Idle state: " << powerInformationVector[0].CurrentIdleState << endl;
		cout << "Max idle state:" << powerInformationVector[0].MaxIdleState << endl;
		Sleep(1000);
	} while (true);

	powerInformationVector.clear();
	system("pause");

	return 0;  // возвращаем код завершения программы
}


// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
