
#include "cuda_runtime.h"
#include "device_launch_parameters.h"

#include <stdio.h>
#include <windows.h>
#include <iostream>
#include <fstream>
#include <string>

#define CONVERT 1024*1024;
#define PERCENTAGE 100.0

using namespace std;

size_t GetGraphicDeviceVRamUsage(int _NumGPU)
{
	cudaSetDevice(_NumGPU);

	size_t l_free = 0;
	size_t l_Total = 0;
	cudaError_t error_id = cudaMemGetInfo(&l_free, &l_Total);
	double gpuUsage = l_free;
	gpuUsage /= l_Total;
	gpuUsage *= 100.0;
	cout << gpuUsage << endl;

	return (l_Total - l_free);
}
extern "C" __declspec(dllexport) double RetrieveGpuUsage() {
	cudaSetDevice(0);
	size_t l_free = 0;
	size_t l_Total = 0;
	cudaError_t error_id = cudaMemGetInfo(&l_free, &l_Total);
	cudaDeviceReset();
	return (double) PERCENTAGE * l_free/l_Total/ CONVERT;
}
extern "C" __declspec(dllexport) void printDiscreteGPUInfo() {
	int nDevices;

	cudaGetDeviceCount(&nDevices);
	for (int i = 0; i < nDevices; i++) {
		cudaDeviceProp prop;
		cudaGetDeviceProperties(&prop, i);
		printf("Device Number: %d\n", i);
		printf("  Device name: %s\n", prop.name);
		printf("  Memory Clock Rate (KHz): %d\n",
			prop.memoryClockRate);
		printf("  Memory Bus Width (bits): %d\n",
			prop.memoryBusWidth);
		printf("  Peak Memory Bandwidth (GB/s): %.3f\n\n",
			2.0*prop.memoryClockRate*(prop.memoryBusWidth / 8) / 1.0e6);
		printf("  Clock Rate (KHz): %d\n",
			prop.clockRate);
		printf("  L2CacheSize (bytes): %d\n", prop.l2CacheSize);
		printf("  Global memory(mbytes): %d\n", (prop.totalGlobalMem/1024/1024));

	}
}
extern "C" __declspec(dllexport) void saveGpuInfoToFile(ofstream& on)
{
	int nDevices;

	cudaGetDeviceCount(&nDevices);
	for (int i = 0; i < nDevices; i++) {
		cudaDeviceProp prop;
		cudaGetDeviceProperties(&prop, i);
		on << "==========   Информация о дискретной видеокарте   ============" << endl;
		on << "  Device Number:  " << i << endl;
		on << "  Device name: " << prop.name << endl;
		on << "  Memory Clock Rate (KHz): " <<
			prop.memoryClockRate << endl;
		on << "  Memory Bus Width (bits): " <<
			prop.memoryBusWidth << endl;
		on << "  Peak Memory Bandwidth (GB/s): " <<
			(int)2.0*prop.memoryClockRate*(prop.memoryBusWidth / 8) / 1.0e6;
		on << "  Clock Rate (KHz): " <<
			prop.clockRate << endl;
		on << "  L2CacheSize (bytes): " << prop.l2CacheSize << endl;
		on << "  Global memory(mbytes): " << prop.totalGlobalMem / 1024 / 1024 << endl;

	}
}
