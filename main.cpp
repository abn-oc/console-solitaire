#include<iostream>
using namespace std;

int main() {
	cout << "Program Started." << endl;
	{

	}
	cout << "Program Ended." << endl;
	cout << "Memory Leaks: " << _CrtDumpMemoryLeaks() << endl;
	return 0;
}