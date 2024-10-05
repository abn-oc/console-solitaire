#pragma once
#include<iostream>
#include"List.h"
#include"Stack.h"
#include"Card.h"
#include"Command.h"
using namespace std;

class Game {
private:
	Card deck[52];
	List<Card> tableu[7];
	Stack<Card> foundation[4];
	Stack<Card> stock;
	Stack<Card> waste;
	Stack<Command> commands;
public:
	Game() {
		int ind = 0;
		for (int i = 1; i <= 13; i++) {
			deck[ind++] = Card(i, 'd', false);
		}
		for (int i = 1; i <= 13; i++) {
			deck[ind++] = Card(i, 'h', false);
		}
		for (int i = 1; i <= 13; i++) {
			deck[ind++] = Card(i, 'c', false);
		}
		for (int i = 1; i <= 13; i++) {
			deck[ind++] = Card(i, 's', false);
		}
	}
	void shuffleCards(Card cards[]) {
		srand(time(0));
		for (int i = 0; i < 52; i++) {
			int ri = rand() % 52;
			Card temp = cards[i];
			cards[i] = cards[ri];
			cards[ri] = temp;
		}
	}
	void Setup() {
		shuffleCards(deck);
		int ind = 0;
		for (int i = 0; i < 24; i++) {
			deck[ind].hide();
			stock.Push(deck[ind++]);
		}
		for (int i = 0; i < 7; i++) {
			for (int j = 0; j <= i; j++) {
				if (j == 0) deck[ind].show();
				tableu[i].insertAtStart(deck[ind++]);
			}
		}
	}
	void StacktoStack(Stack<Card>& src, Stack<Card>& des) {
		Card drawnCard = src.Pop();
		drawnCard.show();
		des.Push(drawnCard);
	}
	void ListtoList(List<Card>& src, List<Card>& des) {
		Card drawnCard = src.tailItem();
		//drawnCard.show();
		src.deleteFromEnd();
		des.insertAtEnd(drawnCard);
	}
	void ListtoStack(List<Card>& src, Stack<Card>& des) {
		Card drawnCard = src.tailItem();
		src.deleteFromEnd();
		des.Push(drawnCard);
	}
	void StacktoList(Stack<Card>& src, List<Card>& des) {
		Card drawnCard = src.Pop();
		des.insertAtEnd(drawnCard);
	}
	void Process() {
		Command command;
		command.getInput();
		//if(z then call undo function) - takes last command and inverts it
		if (command.getCommand() == 'z') {
			Command lastCommand = commands.Pop();
			if (lastCommand.getCommand() == 's') {
				StacktoStack(waste, stock);
				if (waste.isEmpty() && !commands.isEmpty()) {
					int len = stock.Size();
					for (int i = 0; i < len; i++) {
						StacktoStack(stock, waste);
					}
				}
			}
			else if (lastCommand.getCommand() == 'm') {
				if (lastCommand.getSource()[0] == 'c' && lastCommand.getDest()[0] == 'c') {
					int sc = (lastCommand.getSource()[1] - '0') - 1;
					int dc = (lastCommand.getDest()[1] - '0') - 1;
					for (int i = 0; i < lastCommand.getNum(); i++) {
						if (!tableu[sc].isEmpty()) tableu[sc].tailItem().hide();
						ListtoList(tableu[dc], tableu[sc]);
					}
				}
				else if (lastCommand.getSource()[0] == 'c' && lastCommand.getDest()[0] == 'f') {
					int sc = (lastCommand.getSource()[1] - '0') - 1;
					int dc = (lastCommand.getDest()[1] - '0') - 1;
					for (int i = 0; i < lastCommand.getNum(); i++) {
						tableu[sc].tailItem().hide();
						StacktoList(foundation[dc], tableu[sc]);
					}
				}
			}
		}
		//if(s then call drawFromstock function) - pop from stock push to waste
		if (command.getCommand() == 's') {
			if (stock.isEmpty()) {
				int len = waste.Size();
				for (int i = 0; i < len; i++) {
					StacktoStack(waste, stock);
				}
				StacktoStack(stock, waste);
				commands.Push(command);
			}
			else {
				StacktoStack(stock, waste);
				commands.Push(command);
			}
		}
		//if(m) then take out source dest and num of cards
		//call move function with source dest and num as args - check if placing is right, then do, otherwise dont
		if (command.getCommand() == 'm') {
			if (command.getSource()[0] == 'c' && command.getDest()[0] == 'c') {
				int sc = (command.getSource()[1] - '0') - 1;
				int dc = (command.getDest()[1] - '0') - 1;
				for (int i = 0; i < command.getNum(); i++) {
					if (!tableu[sc].tailItem().isVisible()) {
						cout << "\nInvalid Command.";
						return;
					}
					ListtoList(tableu[sc], tableu[dc]);
					commands.Push(command);
					if(!tableu[sc].isEmpty()) tableu[sc].tailItem().show();
				}
			}
			else if (command.getSource()[0] == 'c' && command.getDest()[0] == 'f') {
				int sc = (command.getSource()[1] - '0') - 1;
				int dc = (command.getDest()[1] - '0') - 1;
				for (int i = 0; i < command.getNum(); i++) {
					if (!tableu[sc].tailItem().isVisible()) {
						cout << "\nInvalid Command.";
						return;
					}
					ListtoStack(tableu[sc], foundation[dc]);
					commands.Push(command);
					if (!tableu[sc].isEmpty()) tableu[sc].tailItem().show();
				}
			}
		}
	}
	void Print() {
		//first line
		cout << "Stock\t\tWaste\t\t\tFoundation 1\tFoundation 2\tFoundation 3\tFoundation 4" << endl;
		//second line
		if (!waste.isEmpty())cout << "[   ]\t\t" << waste.topItem() << "\t\t\t";
		else cout << "[   ]\t\t[   ]\t\t\t";
		for (int i = 0; i < 4; i++) {
			if (!foundation[i].isEmpty()) {
				cout << foundation[i].topItem() << "\t\t";
			}
			else {
				cout << "[   ]\t\t";
			}
		}
		cout << endl;
		//third line
		if(stock.Size() == 1) cout << "(" << stock.Size() << " card)\t";
		else cout << "(" << stock.Size() << " cards)\t";
		if (waste.Size() == 1) cout << "(" << waste.Size() << " card)\t\t";
		else cout << "(" << waste.Size() << " cards)\t\t";
		for (int i = 0; i < 4; i++) {
			if (foundation[i].Size() == 1) cout << "(" << foundation[i].Size() << " card)\t";
			else cout << "(" << foundation[i].Size() << " cards)\t";
		}
		cout << endl << endl;
		//fifth line
		for (int i = 1; i <= 7; i++) {
			cout << "Column " << i << "\t";
		}
		cout << endl;
		//sixth line
		for (int i = 0; i < 7; i++) {
			if (tableu[i].Size() == 1) cout << "(" << tableu[i].Size() << " card)\t";
			else cout << "(" << tableu[i].Size() << " cards)\t";
		}
		cout << endl;
		//columns
		List<Card>::iter itrs[7];
		for (int i = 0; i < 7; i++) itrs[i] = tableu[i].begin();
		bool display = true;
		while (display) {
			display = false;
			for (int i = 0; i < 7; i++) {
				if (itrs[i] != tableu[i].end()) {
					cout << *itrs[i] << "\t\t";
					display = true;
				}
				else cout << "\t\t";
			}
			cout << endl;
			for (int i = 0; i < 7; i++) {
				if (itrs[i] != tableu[i].end()) ++itrs[i];
			}
		}
	}
};