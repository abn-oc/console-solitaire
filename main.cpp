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
		while (!solitaire.checkWin()) {
			cout << "S O L I T A I R E" << endl;
			cout << "----------------------------------------------------------------------------------------------------------\n";
			solitaire.Print();
			cout << "----------------------------------------------------------------------------------------------------------\n";
			cout << "Controls: z - undo, s - draw, m src des num - move num cards from src to des, u - undo all, o - restart, e - exit" << endl;
			solitaire.Process();
			system("cls");
		}
		cout << "Y O U  W I N" << endl;
		cout << "----------------------------------------------------------------------------------------------------------\n";
		solitaire.Print();
		cout << "----------------------------------------------------------------------------------------------------------\n";
		cout << "Y O U  W I N" << endl;
	}
	cout << "Memory Leaks: " << _CrtDumpMemoryLeaks() << endl;
	return 0;
}