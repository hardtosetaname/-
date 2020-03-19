#include<Windows.h>
#include<stdlib.h>



HANDLE InitCOM()
{
	HANDLE hCom = INVALID_HANDLE_VALUE;
	hCom = CreateFile(("\\\\.\\COM14"), GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING,
		0/*同步方式打开串口*/, NULL);
	if (INVALID_HANDLE_VALUE == hCom)
	{
		return INVALID_HANDLE_VALUE;
	}
	SetupComm(hCom, 4096, 4096);//设置缓存

	DCB dcb;

	GetCommState(hCom, &dcb);//设置串口
	dcb.DCBlength = sizeof(dcb);
	dcb.BaudRate = CBR_9600;
	dcb.StopBits = ONESTOPBIT;
	SetCommState(hCom, &dcb);

	PurgeComm(hCom, PURGE_RXABORT | PURGE_TXCLEAR | PURGE_RXCLEAR | PURGE_TXABORT);//清空缓存

	COMMTIMEOUTS ct;
	//设置读取超时时间，及ReadFlie最长等待时间
	ct.ReadIntervalTimeout = 0;
	ct.ReadTotalTimeoutConstant = 5000;
	ct.ReadTotalTimeoutMultiplier = 500;

	ct.WriteTotalTimeoutMultiplier = 500;
	ct.WriteTotalTimeoutConstant = 5000;

	SetCommTimeouts(hCom, &ct);//设置超时

	return hCom;
}


void ComWrite(HANDLE hCom, LPBYTE buf, int &len)
{
	PurgeComm(hCom, PURGE_RXABORT | PURGE_TXCLEAR | PURGE_RXCLEAR | PURGE_TXABORT);
	BOOL rtn = FALSE;
	DWORD WriteSize = 0;
	rtn = WriteFile(hCom, buf, len, &WriteSize, NULL);
	while (!rtn);
}



int main(int argc, char *argv[])
{
	int sa = atoi(argv[1]);;
	unsigned char buffer[2] = { 0 };
	buffer[0] = sa / 1000;
	buffer[1] = sa % 1000;
	HANDLE My_Com = InitCOM();
	int len = sizeof(buffer);
	ComWrite(My_Com, (LPBYTE)buffer, len);
	Sleep(1);
	//CloseHandle(My_Com);
	return(0);
}
