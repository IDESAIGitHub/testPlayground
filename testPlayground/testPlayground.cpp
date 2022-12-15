// testPlayground.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <ctime>
#include <chrono>
#include <iostream>
#include <vector>
#include <thread>

#include "modbus.h"

using namespace std::chrono;
void countToBillion() {
    int i = 0;
    while (i<1000000000) {
        i++;
    }
    return;
}

typedef struct structtest {
    std::chrono::milliseconds time_last_in;
    structtest() {	//constructor
        time_last_in = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch() );
    }
}structtest;

class classtest {
public:
    int a;
    int b;
    std::vector <int> vecna;
	classtest() {	//constructor
		a = 0;
		b = 0;
	}
	
};

void add(classtest* c) {
	c->a++;
	c->b++;
    c->vecna.push_back(c->a + c->b);
}


int main()
{
	
	//WEIDMULLER
	modbus_t* ctx;
    ctx = modbus_new_tcp("192.168.111.125", 502);
    //connect
	if (modbus_connect(ctx) == -1) {
		std::cout << "Connection failed: " << modbus_strerror(errno) << "\n";
		modbus_free(ctx);
		return -1;
	}
	else {
		std::cout << "Connection successful.\n";
	}
	Sleep(2000);
       
	//read1
	uint8_t* myread = nullptr;
	myread = new uint8_t[32]{0};
	microseconds comienzoLectura = duration_cast<microseconds>(high_resolution_clock::now().time_since_epoch());
	modbus_read_input_bits(ctx, 0x0000, 32, myread);
	microseconds tiempoLectura = duration_cast<microseconds>(high_resolution_clock::now().time_since_epoch()) - comienzoLectura;
	for (int i = 0; i < 32; i++) {
		std::cout << "Value "<< i<<":" << (int)myread[i] << "\n";
	}
	std::cout << "Time modbus_read_input_bits: " << tiempoLectura << "\n";
	
	Sleep(2000);
	//write1
	uint8_t* writeBit = nullptr;
	writeBit = new uint8_t[32]{0};
	writeBit[0] = 1;
	writeBit[2] = 1;
	writeBit[17] = 1;
	writeBit[19] = 1;
	comienzoLectura = duration_cast<microseconds>(high_resolution_clock::now().time_since_epoch());
	modbus_write_bits(ctx, 0x8000, 32, writeBit);
	tiempoLectura = duration_cast<microseconds>(high_resolution_clock::now().time_since_epoch()) - comienzoLectura;
	std::cout << "Time modbus_write_bits: " << tiempoLectura << "\n";
	
	Sleep(2000);
	
	//read2
	uint16_t* dest = new uint16_t[2]{0};
	comienzoLectura = duration_cast<microseconds>(high_resolution_clock::now().time_since_epoch());
	modbus_read_input_registers(ctx, 0x0000, 2, dest);
	tiempoLectura = duration_cast<microseconds>(high_resolution_clock::now().time_since_epoch()) - comienzoLectura;
	std::cout << "Value: " << (int)dest[0] << "\n";
	std::cout << "Value: " << (int)dest[1] << "\n";
	std::cout << "Time modbus_read_input_registers: " << tiempoLectura << "\n";
	Sleep(2000);
	//write2
	uint16_t* writevalue = nullptr;
	writevalue = new uint16_t[2]{0};
	writevalue[0] = 0xFFFF;
	writevalue[1] = 0x03;
	comienzoLectura = duration_cast<microseconds>(high_resolution_clock::now().time_since_epoch());
	modbus_write_registers(ctx, 0x0800, 2, writevalue);
	tiempoLectura = duration_cast<microseconds>(high_resolution_clock::now().time_since_epoch()) - comienzoLectura;
	std::cout << "Time modbus_write_registers: " << tiempoLectura << "\n";
	
	Sleep(5000);
	//close
	modbus_close(ctx);
	modbus_free(ctx);
	
	
	/*
	//VIPA	
	modbus_t* ctx;
	ctx = modbus_new_tcp("192.168.112.100", 502);
	//connect
	if (modbus_connect(ctx) == -1) {
		std::cout << "Connection failed: " << modbus_strerror(errno) << "\n";
		modbus_free(ctx);
		return -1;
	}
	else {
		std::cout << "Connection successful.\n";
	}
	Sleep(2000);
	//read1
	uint8_t* myread = nullptr;
	myread = new uint8_t[32]{0};
	microseconds comienzoLectura = duration_cast<microseconds>(high_resolution_clock::now().time_since_epoch());
	modbus_read_input_bits(ctx, 0x10000, 32, myread);
	microseconds tiempoLectura = duration_cast<microseconds>(high_resolution_clock::now().time_since_epoch()) - comienzoLectura;
	for (int i = 0; i < 32; i++) {
		std::cout << "Value "<< i<<":" << (int)myread[i] << "\n";
	}
	std::cout << "Time modbus_read_input_bits: " << tiempoLectura << "\n";

	Sleep(2000);
	//write1
	uint8_t* writeBit = nullptr;
	writeBit = new uint8_t[32]{ 0 };
	writeBit[0] = 1;
	writeBit[2] = 1;
	writeBit[17] = 1;
	writeBit[19] = 1;
	comienzoLectura = duration_cast<microseconds>(high_resolution_clock::now().time_since_epoch());
	modbus_write_bits(ctx, 0x00000, 32, writeBit);
	tiempoLectura = duration_cast<microseconds>(high_resolution_clock::now().time_since_epoch()) - comienzoLectura;
	std::cout << "Time modbus_write_bits: " << tiempoLectura << "\n";
	
	Sleep(2000);

	//read2
	uint16_t* dest = new uint16_t[2]{0};
	comienzoLectura = duration_cast<microseconds>(high_resolution_clock::now().time_since_epoch());
	modbus_read_input_registers(ctx, 0x10000, 2, dest);
	tiempoLectura = duration_cast<microseconds>(high_resolution_clock::now().time_since_epoch()) - comienzoLectura;
	std::cout << "Value: " << (int)dest[0] << "\n";
	std::cout << "Value: " << (int)dest[1] << "\n";
	std::cout << "Time modbus_read_input_registers: " << tiempoLectura << "\n";
	Sleep(2000);
	//write2
	uint16_t* writevalue = nullptr;
	writevalue = new uint16_t[2]{ 0 };
	writevalue[0] = 0x0204;
	writevalue[1] = 0x0301;
	comienzoLectura = duration_cast<microseconds>(high_resolution_clock::now().time_since_epoch());
	modbus_write_registers(ctx, 0x40000, 2, writevalue);
	tiempoLectura = duration_cast<microseconds>(high_resolution_clock::now().time_since_epoch()) - comienzoLectura;
	std::cout << "Time modbus_write_registers: " << tiempoLectura << "\n";

	Sleep(5000);
	//close
	modbus_close(ctx);
	modbus_free(ctx);
	*/

    return 0;
}