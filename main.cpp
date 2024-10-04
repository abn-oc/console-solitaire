#include<iostream>
#include"List.h"
#include"Stack.h"
#include"Card.h"
#include"Command.h"
using namespace std;

int main() {
	cout << "Program Started." << endl;
	{
		Command c;
		Command a;
		Command b;
		Command e;
	}
	cout << "Program Ended." << endl;
	cout << "Memory Leaks: " << _CrtDumpMemoryLeaks() << endl;
	return 0;
}