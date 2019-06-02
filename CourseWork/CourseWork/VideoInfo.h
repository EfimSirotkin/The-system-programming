#pragma once
#include <windows.h>
#include <iostream>
#include <iomanip>
#include "ComputerPart.h"
#include <string.h>


using namespace std;

class VideoInfo : public ComputerPart
{
public:
	void printVideoInfo();
	void printToFile(ofstream & on);
	void getGpuInformation();
	void RetrieveGpuUsage();
	float getDiagSize();
	double getGpuUsage();
	void getDesktop();
private:
	DISPLAY_DEVICE lpDisplayDevice;
	HDC hdcScreen;
	float gpuUsage;
};