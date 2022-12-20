// testPlayground.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <ctime>
#include <chrono>
#include <iostream>
#include <vector>
#include <thread>

#include "modbus.h"

class dos {
public:
	int a;
	dos() {
		a = 0;
	}
	dos(int rec) {
		a = rec;
	}
};

class uno {
public:
	int u1;
	uno(){
		u1 = 0; 
	}
	std::vector <dos*> dosVec;
};

int printDos(std::vector<dos*> dosvec) {
	for (int i = 0; i < dosvec.size(); i++){
		std::cout << dosvec[i]->a << std::endl; 
	}
	return 0; 
}

int repushDos(std::vector<dos*>& dosvec) {
	dosvec.push_back(new dos(dosvec.size()));
	return 0;
}

int pushDos(std::vector<dos*>& dosvec) {
	dosvec.push_back(new dos(dosvec.size())); 
	repushDos(dosvec);
	return 0; 
}


int main()
{
	std::vector<uno*> unoVec;
	unoVec.push_back(new uno());
	unoVec[0]->dosVec.push_back(new dos());
	
	pushDos(unoVec[0]->dosVec);
	pushDos(unoVec[0]->dosVec);
	
	printDos(unoVec[0]->dosVec);

    return 0;
}