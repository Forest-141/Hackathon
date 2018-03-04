#include "header.h"

int main(void)
{
	FILE *infileA = NULL, *infileB = NULL, *infileC = NULL,*infileD=NULL,*output=NULL;
	int lotA = 5, lotB = 6,lotC=10,lotD=1,sumA=0,sumB=0,sumC=0,sumD=0,cont=0,i=0;
	int a[5] = { 0 }, b[6] = { 0 }, c[10] = { 0 }, d[1] = { 0 };
	
	DCB dcb;
	HANDLE hCom;
	BOOL fSuccess;
	wchar_t pcCommPort[32] = L"COM4";
	char TempChar;
	char SerialBuffer[256];
	DWORD NoBytesRead;


	hCom = CreateFile(&pcCommPort[0],
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

	dcb.BaudRate = CBR_9600;     // set the baud rate
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


	do
	{
		ReadFile(hCom, &TempChar, sizeof(TempChar), &NoBytesRead, NULL);
		SerialBuffer[i] = TempChar;
		i++;
		printf("Tempchar:  %c \n", TempChar);


		infileA = fopen("lotA.txt", "r");
		infileB = fopen("lotB.txt", "r");
		infileC = fopen("lotC.txt", "r");
		infileD = fopen("lotD.txt", "w");
		

		fprintf(infileD, "%c", TempChar);
		fclose(infileD);
		infileD = fopen("lotD.txt", "r");
		

		text_scan(infileA, a, 5);
		text_scan(infileB, b, 6);
		text_scan(infileC, c, 10);
		text_scan(infileD, d, 1);

		sumA = sum_array(a, 5);
		sumB = sum_array(b, 6);
		sumC = sum_array(c, 10);
		sumD = sum_array(d, 1);
	

	
		lot_space(lotA, sumA);
		lot_space(lotB, sumB);
		lot_space(lotC, sumC);
		lot_space(lotD, sumD);
		lotD = lotD - sumD;
		printf("LotD: %d\n", lotD);
		output = fopen("output.txt", "w");
		fprintf(output,"%d",lotD);//prints the number of spaces available in lots

		fclose(infileA);
		fclose(infileB);
		fclose(infileC);
		fclose(infileD);
		fclose(output);
		//system("pause");
		lotD = 1;
		
		
		}while (i < 256);
	
	return 0;
}