// Dll1.cpp : Определяет экспортированные функции для приложения DLL.
//

#include "stdafx.h"
#include <iostream>
#include <string>

using namespace std;
#define NUM_OF_SYMBOLS 100
#define AMOUNT_OF_FILES 5
#define STR_SIZE 64
#define MAX_FILESIZE 65535

char resultBuffer[MAX_FILESIZE];
HANDLE enableWritingEvent;
HANDLE enableReadingEvent;
HANDLE TerminationEvent;

extern "C" __declspec(dllexport) void ReadFiles() {
	
	/*
	Объекты-события синхронизации, создаём события с автосбросом, причём, 
	т.к. чтение выполняется сразу же, событие для синхронизации чтения - в сигнальном состоянии
	*/
	enableReadingEvent = CreateEvent(NULL, false, true, NULL);
	enableWritingEvent = CreateEvent(NULL, false, false, NULL);
	TerminationEvent = CreateEvent(NULL, false, false, NULL);

	TCHAR fileNames[AMOUNT_OF_FILES][STR_SIZE] =
	{
		TEXT("file1.txt"),
		TEXT("file2.txt"),
		TEXT("file3.txt"),
		TEXT("file4.txt"),
		TEXT("file5.txt")
	};

	
	char buffer[NUM_OF_SYMBOLS + 1];
	DWORD bytesRead;
	OVERLAPPED overlapped;
	overlapped.hEvent = CreateEvent(NULL, true, true, NULL);

	/*
		Из каждого файла мы считываем только по NUM_OF_SYMBOLS в буфер, т.к. нельзя точно предсказать,
		какого размера данные в файле. Как только прочитанных символов в файле становится меньше 
		NUM_OF_SYMBOLS, это означает, что мы прочитали все содержимое файла и можно приступать к записи
	*/
	for (int i = 0; i < AMOUNT_OF_FILES; i++) {
		WaitForSingleObject(enableReadingEvent, INFINITE);
		overlapped.Offset = 0;
		overlapped.OffsetHigh = 0;
		strcpy_s(resultBuffer, sizeof(resultBuffer), "");
		HANDLE fileHandle = CreateFile(fileNames[i], GENERIC_READ, 0, NULL, OPEN_EXISTING, 0, NULL);
		/*
		Буфер на каждой итерации содержит предыдущие записи, поэтому его стоит всегда "занулять"
		*/
		do {
			memset(buffer, '\0', sizeof(buffer));
			if (ReadFile(fileHandle, buffer, sizeof(buffer), &bytesRead, &overlapped) == FALSE) {
				printf("Error occured, %d", GetLastError());
				break;
			}
			WaitForSingleObject(fileHandle, INFINITE);
			strcat_s(resultBuffer, sizeof(resultBuffer), buffer);
			/* После каждого считывания смещаемся в файле, чтобы не считывать одно и то же*/
			overlapped.Offset += bytesRead;

		} while (bytesRead == NUM_OF_SYMBOLS);  
		/* После успешного считывания можно оповестить писателя о том, что пора работать:)*/
		SetEvent(enableWritingEvent);
		CloseHandle(fileHandle);
	}
	/* Оповещаем главный поток о завершении работы читателя*/
	SetEvent(TerminationEvent);
	CloseHandle(overlapped.hEvent);

}

extern "C" __declspec(dllexport) void WriteToFile() {

	TCHAR file[STR_SIZE] = TEXT("result.txt");

	HANDLE fileHandler = CreateFile(file, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, 0, NULL);
	DWORD bytesWritten;
	OVERLAPPED overlapped;

	overlapped.hEvent = CreateEvent(NULL, false, true, NULL);
	overlapped.Offset = 0;
	overlapped.OffsetHigh = 0;
	/*
		Поток-писатель находится всегда на чеку: функции ожидания передают управление коду
		сразу же после проверки состояния дескрипторов. Таким образом реализуется асинхронность.
		Ведь WriteFile - функция ядра ОС. Нам стоит просто вызвать ее, а выполнится она за счет ОС.
		Только после завершения записи разрешается чтение следующего файла.
	*/
	while (true) {

		if (WaitForSingleObject(enableWritingEvent, 0) == WAIT_OBJECT_0) {

			WriteFile(fileHandler, &resultBuffer, strlen(resultBuffer), &bytesWritten, &overlapped);

			WaitForSingleObject(overlapped.hEvent, INFINITE);
			overlapped.Offset += bytesWritten;
			SetEvent(enableReadingEvent);
		}
		if (WaitForSingleObject(TerminationEvent, 0) == WAIT_OBJECT_0) {
			break;
		}
	}

	CloseHandle(fileHandler);
	CloseHandle(enableReadingEvent);
	CloseHandle(enableWritingEvent);
	CloseHandle(TerminationEvent);
}

