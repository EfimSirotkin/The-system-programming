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
