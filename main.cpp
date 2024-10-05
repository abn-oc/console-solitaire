#include<iostream>
#include"List.h"
#include"Stack.h"
#include"Card.h"
#include"Command.h"
#include"Game.h"
using namespace std;

int main() {
	{
		Game solitaire;
		solitaire.Setup();
		while (true) {
			cout << "S O L I T A I R E" << endl;
			cout << "----------------------------------------------------------------------------------------------------------\n";
			solitaire.Print();
			cout << "----------------------------------------------------------------------------------------------------------\n";
			cout << "S O L I T A I R E" << endl;
			solitaire.Process();
			system("cls");
		}
	}
	cout << "Memory Leaks: " << _CrtDumpMemoryLeaks() << endl;
	return 0;
}