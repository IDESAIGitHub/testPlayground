#include "rs232lib.h"

rs232lib::rs232lib(void)
{
}

rs232lib::rs232lib(std::string portName, int baudRate, const std::string mode)
{
	hSerial = CreateFileA(portName.c_str(), GENERIC_READ | GENERIC_WRITE, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
	if (hSerial == INVALID_HANDLE_VALUE) {
		if (GetLastError() == ERROR_FILE_NOT_FOUND) {
			//serial port does not exist. Inform user.
			printf("Serial port does not exist\n");
			throw std::exception("Serial port does not exist");
		}
		//some other error occurred. Inform user.
		printf("Error opening serial port\n");
		throw std::exception("Error opening serial port\n");
	}
	DCB dcbSerialParams = { 0 };
	dcbSerialParams.DCBlength = sizeof(dcbSerialParams);
	if (!GetCommState(hSerial, &dcbSerialParams)) {
		//error getting state
		printf("Error getting serial port state\n");
		throw std::exception("Error getting serial port state");
	}
	//parse ByteSize, StopBits and Parity from mode
	int byteSize = 8;
	int stopBits = ONESTOPBIT;
	int parity = NOPARITY;
	if (!parseMode(mode, byteSize, stopBits, parity))
	{
		printf("Invalid serial port mode\n");
		throw std::exception("Error parsing serial port mode");
	}
	dcbSerialParams.BaudRate = baudRate;
	dcbSerialParams.ByteSize = byteSize;
	dcbSerialParams.StopBits = stopBits;
	dcbSerialParams.Parity = parity;
	if (!SetCommState(hSerial, &dcbSerialParams)) {
		//error setting serial port state
		printf("Error setting serial port state\n");
		throw std::exception("Error setting serial port state");
	}
}

rs232lib::~rs232lib(void)
{
	CloseHandle(hSerial);
}

//reader
std::string rs232lib::read()
{
	DWORD dwBytesRead = 0;
	char buf[1024];
	std::string result;
	if (!ReadFile(hSerial, buf, 1024, &dwBytesRead, NULL)) {
		//error occurred. Report to user.
		printf("Error occurred\n");
		throw std::exception("Error occurred");
	}
	result = std::string(buf, dwBytesRead);
	return result;
}

//writer
int rs232lib::write(std::string data)
{
	DWORD dwBytesWritten = 0;
	if (!WriteFile(hSerial, data.c_str(), data.length(), &dwBytesWritten, NULL)) {
		//error occurred. Report to user.
		printf("Error occurred\n");
		throw std::exception("Error occurred");
	}
	return dwBytesWritten;
}

//Helpers
bool rs232lib::parseMode(const std::string& mode, int& byteSize, int& stopBits, int& parity)
{
	if (mode.length() == 3)
	{
		if (mode[0] == '8')
		{
			byteSize = 8;
		}
		else if (mode[0] == '7')
		{
			byteSize = 7;
		}
		else if (mode[0] == '6')
		{
			byteSize = 6;
		}
		else if (mode[0] == '5')
		{
			byteSize = 5;
		}
		else
		{
			printf("Invalid byte size\n");
			return false;
		}
		if (mode[1] == 'N')
		{
			parity = NOPARITY;
		}
		else if (mode[1] == 'E')
		{
			parity = EVENPARITY;
		}
		else if (mode[1] == 'O')
		{
			parity = ODDPARITY;
		}
		else
		{
			printf("Invalid parity\n");
			return false;
		}
		if (mode[2] == '1')
		{
			stopBits = ONESTOPBIT;
		}
		else if (mode[2] == '2')
		{
			stopBits = TWOSTOPBITS;
		}
		else
		{
			printf("Invalid stop bits\n");
			return false;
		}
	}
	else
	{
		printf("Invalid mode\n");
		return false;
	}
	return true;
}