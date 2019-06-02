#pragma once
#include <windows.h>
#include <iostream>
#include "ComputerPart.h"
#define BUFSIZE 1024

using namespace std;

class SystemInfo : public ComputerPart
{
public:
		void printSystemInfo();
		void printToFile(ofstream & on);
		void getSystemInfo();
private:
		char computerName[BUFSIZE];
		char userName[BUFSIZE];
		char systemDirectory[BUFSIZE];
		char windowsDirectory[BUFSIZE];
		char tempDirectory[BUFSIZE];
};