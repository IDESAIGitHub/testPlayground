#pragma once
#include <string>
#include <windows.h>
class rs232lib
{
public:
	rs232lib(std::string portName, int baudRate, const std::string mode);
	~rs232lib(void);
	
	std::string read();
	int write(std::string data);

	
private:
	rs232lib(void);
	
	//members
	HANDLE hSerial;
	
	//helpers
	bool parseMode(const std::string& mode, int& byteSize, int& stopBits, int& parity);
};

