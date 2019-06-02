#include "DiskInfo.h"

void DiskInfo::printDiskInfo()
{
		system("cls");
		cout << "\tDisks's iformation: " << endl;
		int k = 0;
		int sz = GetLogicalDriveStrings(NULL, 0);
		TCHAR* szLogicalDrives = new TCHAR[sz];
		GetLogicalDriveStrings(sz, szLogicalDrives);
		while (*szLogicalDrives)
		{
				TCHAR szDisk[80];
				lstrcpy(szDisk, szLogicalDrives);
				UINT uDriveType = GetDriveType(szDisk);

				k = k + 1; //считаем кол-во жестких дисков
				cout << " Disk " << szDisk << " - "; //выписываем название
				switch (GetDriveType(szDisk))
				{
				case DRIVE_UNKNOWN: cout << " unknown type" << endl; break;
				case DRIVE_NO_ROOT_DIR: cout << " doesn't exist" << endl; break;
				case DRIVE_REMOVABLE: cout << " removable disk" << endl; break;
				case DRIVE_FIXED: cout << " fixed disk" << endl; break;
				case DRIVE_REMOTE: cout << " network-disk" << endl; break;
				case DRIVE_CDROM: cout << " CD-ROM" << endl; break;
				case DRIVE_RAMDISK: cout << " RAM disk" << endl; break;
				}
				__int64 Free, Total;
				Free = 0;
				Total = 0;
				GetDiskFreeSpaceEx(szDisk, NULL, (PULARGE_INTEGER)&Total, (PULARGE_INTEGER)&Free); //определяем объем    
				cout << " Disk capacity: " << Total / (1024 * 1024) << " MB" << endl;
				cout << " Free: " << Free / (1024 * 1024) << " MB" << endl;
				cout << " Loaded: " << (Total - Free) / (1024 * 1024) << " MB" << endl;

				char FileSystemNameBuffer[20];
				BOOL GetVolumeInformationFlag = GetVolumeInformationA(
						(LPCSTR)szDisk,
						NULL, //name
						100,
						NULL,
						NULL, //&MaximumComponentLength,
						NULL, //&FileSystemFlags,
						FileSystemNameBuffer,
						100
				);
				if (GetVolumeInformationFlag != 0)
				{
						cout << " Fyle system: " << FileSystemNameBuffer << endl << endl;
				}
				else cout << " Fyle system: Н/д" << endl << endl;

				while (*szLogicalDrives) szLogicalDrives++;
				szLogicalDrives++;
		}

		system("pause");
}

void DiskInfo::printToFile(ofstream &on)
{
		on << "========================================" << endl;
		on << "\tDisks's iformation: " << endl;
		int k = 0;
		int sz = GetLogicalDriveStrings(NULL, 0);
		TCHAR* szLogicalDrives = new TCHAR[sz];
		GetLogicalDriveStrings(sz, szLogicalDrives);
		while (*szLogicalDrives)
		{
			TCHAR szDisk[80];
			lstrcpy(szDisk, szLogicalDrives);
			UINT uDriveType = GetDriveType(szDisk);

			k = k + 1; //считаем кол-во жестких дисков
			on << " Disk " << szDisk << " - "; //выписываем название
			switch (GetDriveType(szDisk))
			{
			case DRIVE_UNKNOWN: on << " unknown type" << endl; break;
			case DRIVE_NO_ROOT_DIR: on << " doesn't exist" << endl; break;
			case DRIVE_REMOVABLE: on << " removable disk" << endl; break;
			case DRIVE_FIXED: on << " fixed disk" << endl; break;
			case DRIVE_REMOTE: on << " network-disk" << endl; break;
			case DRIVE_CDROM: on << " CD-ROM" << endl; break;
			case DRIVE_RAMDISK: on << " RAM disk" << endl; break;
			}
			__int64 Free, Total;
			Free = 0;
			Total = 0;
			GetDiskFreeSpaceEx(szDisk, NULL, (PULARGE_INTEGER)&Total, (PULARGE_INTEGER)&Free); //определяем объем    
			on << " Disk capacity: " << Total / (1024 * 1024) << " MB" << endl;
			on << " Free: " << Free / (1024 * 1024) << " MB" << endl;
			on << " Loaded: " << (Total - Free) / (1024 * 1024) << " MB" << endl;

			char FileSystemNameBuffer[20];
			BOOL GetVolumeInformationFlag = GetVolumeInformationA(
				(LPCSTR)szDisk,
				NULL, //name
				100,
				NULL,
				NULL, //&MaximumComponentLength,
				NULL, //&FileSystemFlags,
				FileSystemNameBuffer,
				100
			);
			if (GetVolumeInformationFlag != 0)
			{
				on << " Fyle system: " << FileSystemNameBuffer << endl << endl;
			}
			else on << " Fyle system: Н/д" << endl << endl;

			while (*szLogicalDrives) szLogicalDrives++;
			szLogicalDrives++;
		}
}