#include "File.h"
#define FILE_NAME "SYSTEM_INFORMATION.txt"

void File::saveInFile(CpuInfo &CI)
{
		system("cls"); 
		on.open(FILE_NAME, ios_base::out | ios_base::trunc);
		if (!on.is_open())
		{
				cout << "Couldn't find or open file: " << FILE_NAME<<"!" << endl;
				cout << "Please, try again..." << endl;
				system("pause");
				return;
		}
		DiskInfo DI;
		MemoryInfo MI;
		SystemInfo SI;
		VideoInfo VI;
		Time Tim;
		Tim.getLocalTime();
		on << asctime (Tim.localTime) << endl;
		CI.printToFile(on);
		cout << "---Processor's information has been recorded" << endl;
		VI.printToFile(on);
		cout << "---Graphical card's information has been recorded" << endl;
		MI.printToFile(on);
		cout << "---Random acces memory information has been recorded" << endl;
		on << endl <<  "========= EXTRA INFORMATION ABOUT YOUR SYSTEM ============" << endl;
		DI.printToFile(on);
		cout << "---Disk capacity infromation has been recorded" << endl;
		SI.printToFile(on);
		cout << "---System information has been recorded" << endl;
		on.close();

		system("pause");
}