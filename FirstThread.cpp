// FirstThread.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <iostream>
#include <stdio.h>
#include <thread>
#include <vector>
#include "matrix.h"
#include <iostream>
#include <sstream>

//double correct_input_double()
//{
//	double input = -1;
//	bool valid = false;
//	do {
//		std::cin >> input;
//		if (std::cin.good()) {
//			valid = true;
//		}
//		else {
//			std::cin.clear();
//			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
//			std::cout << "Invalid input, re-enter." << std::endl;
//		}
//	} while (!valid);
//
//	return input;
//}
//
//int correct_input_int()
//{
//	int input = -1;
//	bool valid = false;
//	do {
//		std::cin >> input;
//		if (std::cin.good() && input > 0) {
//			valid = true;
//		}
//		else {
//			std::cin.clear();
//			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
//			std::cout << "Invalid input, re-enter." << std::endl;
//		}
//	} while (!valid);
//
//	return input;
//}
//
//std::vector<std::vector<double>> input_matrix()
//{
//	int size = 0;
//	std::cout << "Enter size matrix :";
//	size = correct_input_int();
//	std::vector<std::vector<double>> mx(size, std::vector<double>(size));
//	for (int i = 0; i < size; ++i) {
//		for (int j = 0; j < size; ++j) {
//			std::cout << "mx[" << i << "][" << j << "]:";
//			mx[i][j] = correct_input_double();
//		}
//	}
//	return mx;
//}
using namespace std;

int main(int argc, char* argv[])
{
	cout <<"argc: "<< argc<< endl;
	int sum = 0;
	for (int i = 0; i < argc; ++i)
	{
		int sample=0;
		stringstream ss;
		ss.str(argv[i]);
		ss >> sample;
		sum += sample;
	}
	cout << "sum: " << sum << endl;
	std::thread::id this_id = std::this_thread::get_id();
	std::cout << "ThreadID : " << this_id <<std::endl;
	return 0;
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
