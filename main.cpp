#include<iostream>
#include"List.h"
using namespace std;

int main() {
	cout << "Program Started." << endl;
	{
		List<int> l;
		cout << "Empty? " << l.isEmpty() << endl;
		l.insertAtStart(2);
		l.insertAtStart(1);
		l.insertAtEnd(3);
		cout << "Empty? " << l.isEmpty() << endl;
		l.Print();
		l.deleteFromStart();
		l.deleteFromEnd();
		l.Print();
	}
	cout << "Program Ended." << endl;
	cout << "Memory Leaks: " << _CrtDumpMemoryLeaks() << endl;
	return 0;
}