#include "VideoInfo.h"

typedef double(*RetrieveGPULoad)();
typedef void(*RetrieveDiscreteGPUInfo)();
typedef void(*GpuInfoFileSaver)(ofstream& on);
#define UPDATE_RATE 500
LPCTSTR libName = TEXT("GpuUsage.dll");
LPCTSTR gpuLoadFuncName = TEXT("RetrieveGpuUsage");
HINSTANCE loadedLib = LoadLibrary(libName);
RetrieveGPULoad gpuLoadFunc = (RetrieveGPULoad)GetProcAddress(loadedLib, TEXT("RetrieveGpuUsage"));
RetrieveDiscreteGPUInfo gpuInfoRetriever = (RetrieveDiscreteGPUInfo)GetProcAddress(loadedLib, TEXT("printDiscreteGPUInfo"));
GpuInfoFileSaver gpuInfoFileRecord = (GpuInfoFileSaver)GetProcAddress(loadedLib, TEXT("saveGpuInfoToFile"));

void VideoInfo::getGpuInformation()
{
	lpDisplayDevice.cb = sizeof(lpDisplayDevice);
	EnumDisplayDevices(NULL,
		0,
		&lpDisplayDevice,
		0);
}
void VideoInfo::RetrieveGpuUsage()
{
	this->gpuUsage = gpuLoadFunc();

}
double VideoInfo::getGpuUsage()
{
	return this->gpuUsage;
}

float VideoInfo::getDiagSize()
{
	return (float)((sqrt(pow(GetDeviceCaps(hdcScreen, HORZSIZE), 2) + pow(GetDeviceCaps(hdcScreen, VERTSIZE), 2))) / 25.4);
}

void VideoInfo::getDesktop()
{
	hdcScreen = GetWindowDC(GetDesktopWindow());
}

void VideoInfo::printVideoInfo()
{
	system("cls");
	getGpuInformation();
	cout << "\tVideoCard and Monitor inforamtion" << endl << endl;

	cout << " "<< lpDisplayDevice.DeviceString << endl;
	cout << " Video memory capacity: " << lpDisplayDevice.StateFlags / 1024 / 1024 << " MB" << endl;
	cout << " Registry branch: " << lpDisplayDevice.DeviceKey << endl << endl;

	getDesktop();
	cout << " Display resolution: " << GetDeviceCaps(hdcScreen, HORZRES) << " x " << GetDeviceCaps(hdcScreen, VERTRES) << endl;
	cout << " Display size: " << GetDeviceCaps(hdcScreen, HORZSIZE) << " mm õ " << GetDeviceCaps(hdcScreen, VERTSIZE) << " mm" << endl;
	cout << " Display inch: " << setprecision(3) << getDiagSize() << " inch" << endl;
	cout << " Colors palette: " << GetDeviceCaps(hdcScreen, BITSPIXEL) << " bit" << endl;
	cout << " Update rate: " << GetDeviceCaps(hdcScreen, VREFRESH) << " Hz" << endl << endl;
	gpuInfoRetriever();
	system("pause");
}

void VideoInfo::printToFile(ofstream &on)
{
	on << "========================================" << endl;
	getGpuInformation();
	on << "\tVideoCard and Monitor inforamtion" << endl << endl;

	on << lpDisplayDevice.DeviceString << endl;
	on << " Video memory capacity: " << lpDisplayDevice.StateFlags / 1024 / 1024 << " MB" << endl;
	on << " Registry branch: " << lpDisplayDevice.DeviceKey << endl << endl;

	getDesktop();
	on << " Display resolution: " << GetDeviceCaps(hdcScreen, HORZRES) << " x " << GetDeviceCaps(hdcScreen, VERTRES) << endl;
	on << " Display size: " << GetDeviceCaps(hdcScreen, HORZSIZE) << " mm õ " << GetDeviceCaps(hdcScreen, VERTSIZE) << " mm" << endl;
	on << " Display inch: " << setprecision(3) << getDiagSize() << " inch" << endl;
	on << " Colors palette: " << GetDeviceCaps(hdcScreen, BITSPIXEL) << " bit" << endl;
	on << " Update rate: " << GetDeviceCaps(hdcScreen, VREFRESH) << " Hz" << endl << endl;
	gpuInfoFileRecord(on);
}