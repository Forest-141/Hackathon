#include <windows.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
	DCB dcb;
	HANDLE hCom;
	BOOL fSuccess;
	wchar_t pcCommPort[32] = L"COM3";

	hCom = ::CreateFile(&pcCommPort[0],
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
////////////////////////////////////////////////////////////////////////////////////////////////	
	
	wchar_t TempChar, sensor_value; //Temporary character used for reading
	wchar_t SerialBuffer[256];//Buffer for storing Rxed Data
	DWORD NoBytesRead;
	int i = 0;

	do
	{
		ReadFile(hCom,           //Handle of the Serial port
			&TempChar,       //Temporary character
			sizeof(TempChar),//Size of TempChar
			&NoBytesRead,    //Number of bytes read
			NULL);

		SerialBuffer[i] = TempChar;// Store Tempchar into buffer

		sensor_value = TempChar;

		printf(sensor_value);

	}

	while (NoBytesRead > 0);
	
	
	
	
	
	
	
	return (0);
}