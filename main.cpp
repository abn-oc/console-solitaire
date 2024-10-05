#include<iostream>
#include"List.h"
#include"Stack.h"
#include"Card.h"
#include"Command.h"
#include"Game.h"
using namespace std;

int main() {
	cout << "S O L I T A I R E" << endl;
	cout << "----------------------------------------------------------------------------------------------------------\n";
	{
		Game solitaire;
		solitaire.Setup();
		solitaire.Print();
	}
	cout << "----------------------------------------------------------------------------------------------------------\n";
	cout << "S O L I T A I R E" << endl;
	cout << "Memory Leaks: " << _CrtDumpMemoryLeaks() << endl;
	return 0;
}