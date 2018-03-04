// ConsoleApplication1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


#if 0
#include<windows.h>
#include<stdio.h>
int main()
{
	HANDLE hComm;
	char *pPortName = "\\\\.\\COM12";

	hComm = CreateFile(pPortName, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);

	if (hComm == INVALID_HANDLE_VALUE)
	{
		printf("Error in opening serial port");
		// Handle the error.
		printf("CreateFile failed with error %d.\n", GetLastError());
		while (1);
	}


	else
		printf("opening serial port successful");

	char SerialBuffer[256];
	char TempChar;
	int NoBytesRead, i;

	do
	{
		ReadFile(hComm,           //Handle of the Serial port
			&TempChar,       //Temporary character
			sizeof(TempChar),//Size of TempChar
			&NoBytesRead,    //Number of bytes read
			NULL);
		printf(" %c", TempChar);
		//	SerialBuffer[i] = TempChar;// Store Tempchar into buffer
		//	i++;
	}

	while (NoBytesRead > 0);



	CloseHandle(hComm);//Closing the Serial Port

	return 0;
}
#endif
#include <windows.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
	DCB dcb;
	HANDLE hCom;
	BOOL fSuccess;
	LPCWSTR pcCommPort = "COM3";

	hCom = ::CreateFile(pcCommPort,
		GENERIC_READ | GENERIC_WRITE,
		0,    // must be opened with exclusive-access
		NULL, // no security attributes
		OPEN_EXISTING, // must use OPEN_EXISTING
		0,    // not overlapped I/O
		NULL  // hTemplate must be NULL for comm devices
	);

	if (hCom == INVALID_HANDLE_VALUE)
	{
		// Handle the error.
		printf("CreateFile failed with error %d.\n", GetLastError());
		while (1);
		return (1);
	}

	// Build on the current configuration, and skip setting the size
	// of the input and output buffers with SetupComm.

	fSuccess = GetCommState(hCom, &dcb);

	if (!fSuccess)
	{
		// Handle the error.
		printf("GetCommState failed with error %d.\n", GetLastError());
		return (2);
	}

	// Fill in DCB: 57,600 bps, 8 data bits, no parity, and 1 stop bit.

	dcb.BaudRate = CBR_57600;     // set the baud rate
	dcb.ByteSize = 8;             // data size, xmit, and rcv
	dcb.Parity = NOPARITY;        // no parity bit
	dcb.StopBits = ONESTOPBIT;    // one stop bit

	fSuccess = SetCommState(hCom, &dcb);

	if (!fSuccess)
	{
		// Handle the error.
		printf("SetCommState failed with error %d.\n", GetLastError());
		return (3);
	}

	printf("Serial port %s successfully reconfigured.\n", pcCommPort);
	return (0);
}
