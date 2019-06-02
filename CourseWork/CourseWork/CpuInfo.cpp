#include "CpuInfo.h"
# define _WIN32_DCOM 
# pragma comment(lib, "wbemuuid.lib")
# include <Wbemidl.h> 
# include <comdef.h>

string bstrToStr(BSTR source) {
		_bstr_t wrapped_bstr = _bstr_t(source);
		int length = wrapped_bstr.length();
		char* char_array = new char[length];
		strcpy_s(char_array, length + 1, wrapped_bstr);
		return char_array;
}

void CpuInfo::getCpuInfo()
{
		GetSystemInfo(&SysInfo);

		HRESULT hres;
		//Инициализация COM
		hres = CoInitializeEx(0, COINIT_MULTITHREADED);
		if (FAILED(hres))
		{
				cout << "Error initialisng COM-library" << endl;
				return;
		}

		//установка общих уровней безопасности COM
		hres = CoInitializeSecurity(
				NULL,
				-1,
				NULL,
				NULL,
				RPC_C_AUTHN_LEVEL_DEFAULT,
				RPC_C_IMP_LEVEL_IMPERSONATE,
				NULL,
				EOAC_NONE,
				NULL
		);


		if (FAILED(hres))
		{
				cout << "Error initialising security properties" << endl;
				CoUninitialize();
				return;
		}

		//Получаем исходный локатор в WMI
		IWbemLocator *pLoc = NULL;

		hres = CoCreateInstance(
				CLSID_WbemLocator,
				0,
				CLSCTX_INPROC_SERVER,
				IID_IWbemLocator, (LPVOID *)&pLoc);
		if (FAILED(hres))
		{
				cout << "Error creating IWbemLocator" << endl;
				CoUninitialize();
				return;
		}
		//Подключение к WMI
		IWbemServices *pSvc = NULL;
		//Подключение к ветке root\cimv2
		hres = pLoc->ConnectServer(
				_bstr_t(L"ROOT\\CIMV2"),
				NULL,
				NULL,
				0,
				NULL,
				0,
				0,
				&pSvc
		);

		if (FAILED(hres))
		{
				cout << "Couldn't connect"
						<< hex << hres << endl;
				pLoc->Release();
				CoUninitialize();
				return;
		}
		//Используем указатель на IWbemServices чтобы делать запросы к WMI 
		IEnumWbemClassObject* pEnumerator = NULL;
		hres = pSvc->ExecQuery(
				bstr_t("WQL"),
				bstr_t("SELECT * FROM Win32_Processor"),
				WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY,
				NULL,
				&pEnumerator);
		if (FAILED(hres))
		{
				cout << "Ошибка!"
						<< hex << hres << endl;
				pSvc->Release();
				pLoc->Release();
				CoUninitialize();
				return;
		}

		//Получаем данные
		IWbemClassObject *pclsObj;
		ULONG uReturn = 0;

		while (pEnumerator)
		{
				HRESULT hr = pEnumerator->Next(WBEM_INFINITE, 1,
						&pclsObj, &uReturn);
				if (0 == uReturn)
				{
						break;
				}
				VARIANT vtProp;
				hr = pclsObj->Get(L"Name", 0, &vtProp, 0, 0);
				name = bstrToStr(vtProp.bstrVal);

				hr = pclsObj->Get(L"NumberOfCores", 0, &vtProp, 0, 0);
				numberOfCores = vtProp.uintVal;

				hr = pclsObj->Get(L"MaxClockSpeed", 0, &vtProp, 0, 0);
				maxClockSpeed = vtProp.uintVal;

				hr = pclsObj->Get(L"Manufacturer", 0, &vtProp, 0, 0);
				manufacturer = bstrToStr(vtProp.bstrVal);

				hr = pclsObj->Get(L"Role", 0, &vtProp, 0, 0);
				role = bstrToStr(vtProp.bstrVal);

				hr = pclsObj->Get(L"Status", 0, &vtProp, 0, 0);
				status = bstrToStr(vtProp.bstrVal);

				hr = pclsObj->Get(L"L2CacheSize", 0, &vtProp, 0, 0);
				L2 = vtProp.uintVal;

				hr = pclsObj->Get(L"L3CacheSize", 0, &vtProp, 0, 0);
				L3 = vtProp.uintVal;

				pclsObj->Release();
		}
}

void CpuInfo::printCpuInfo()
{
		system("cls");
		cout << "\tProcessor's information" << endl << endl;
		cout << " Name: " << name << endl;
		cout << " Manufacturer: " << manufacturer << endl;
		cout << " Processor's architecture: ";
		if (SysInfo.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_AMD64)
				cout << " х64" << endl;
		if (SysInfo.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_INTEL)
				cout << " x32" << endl;
		cout << " The number of cores: " << numberOfCores << endl;
		cout << " The number of logical processors: " << SysInfo.dwNumberOfProcessors << endl;
		cout << " The max clock speed: " << maxClockSpeed << " МГц" << endl;
		cout << " Role: " << role << endl;
		cout << " Status: " << status << endl;
		cout << " Cache size L2: " << L2 << " Кб" << endl;
		cout << " Cache size L3: " << L3 << " Кб" << endl;
		cout << "============" << endl;
		cout << " CPU usage: " << getCpuUsage() << "%" << endl;

		system("pause");
}

void CpuInfo::printToFile(ofstream &on)
{
		on << "\tProcessor's information" << endl << endl;
		on << " Name: " << name << endl;
		on << " Manufacturer: " << manufacturer << endl;
		on << " Processor's architecture: ";
		if (SysInfo.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_AMD64)
			on << "х64" << endl;
		if (SysInfo.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_INTEL)
			on << "x32" << endl;
		on << " The number of cores: " << numberOfCores << endl;
		on << " The number of logical processors: " << SysInfo.dwNumberOfProcessors << endl;
		on << " The max clock speed: " << maxClockSpeed << " МГц" << endl;
		on << " Role: " << role << endl;
		on << " Status: " << status << endl;
		on << " Cache size L2: " << L2 << " Кб" << endl;
		on << " Cache size L3: " << L3 << " Кб" << endl;
		on << "============" << endl;
		on << " CPU usage: " << getCpuUsage() << "%" << endl;
}

int CpuInfo::getCpuUsage()
{
		FILETIME prev_idle, prev_kernel, prev_user;
		FILETIME idle, kernel, user;
		GetSystemTimes(&prev_idle, &prev_kernel, &prev_user);
		Sleep(WAIT_TIME);
		GetSystemTimes(&idle, &kernel, &user);
		ULONGLONG sys = (FT2ULL(user) - FT2ULL(prev_user)) +
				(FT2ULL(kernel) - FT2ULL(prev_kernel));
		int usage = int((sys - FT2ULL(idle) + FT2ULL(prev_idle)) * 100.0 / sys);
		return usage;
}

ULONGLONG CpuInfo::FT2ULL(FILETIME &ft)
{
		ULARGE_INTEGER ull;
		ull.HighPart = ft.dwHighDateTime;
		ull.LowPart = ft.dwLowDateTime;
		return ull.QuadPart;
}