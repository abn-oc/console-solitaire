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
		des.Push(drawnCard);
	}
	void ListtoList(List<Card>& src, List<Card>& des) {
		Card drawnCard = src.tailItem();
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

	bool toCValid(Card c1, List<Card>& c2) {

		if (c2.isEmpty() && c1.getRank() == 13) return true;

		if (c2.isEmpty() && c1.getRank() != 13) return false;

		if ((c1.getRank() == c2.tailItem().getRank() - 1) &&
			((c1.isBlack() && c2.tailItem().isRed()) ||
			(c1.isRed() && c2.tailItem().isBlack()))) {
			return true;
		}
		else return false;
	}
	bool toFValid(Card c1, Stack<Card>& f) {

		if (f.isEmpty() && c1.getRank() == 1) return true;

		if (f.isEmpty() && c1.getRank() != 1) return false;
	
		if ((c1.getRank() == f.topItem().getRank() + 1) &&
			(c1.getSuite() == f.topItem().getSuite())) {
			return true;
		}
		else return false;
	}

	void Process() {
		while (1) {
			Command command;
			command.getInput();
			if (command.getCommand() == 'u') {
				Restart();
				while (!commands.isEmpty()) commands.Pop();
				break;
			}
			if (command.getCommand() == 'o') {
				shuffleCards(deck);
				Restart();
				while (!commands.isEmpty()) commands.Pop();
				break;
			}
			if (command.getCommand() == 'e') {
				exit(0);
			}
			if (command.getCommand() == 's') {
				if (!stock.isEmpty()) {
					stock.topItem().show();
					StacktoStack(stock, waste);
					commands.Push(command);
					break;
				}
				else if (stock.isEmpty()) {
					while (!waste.isEmpty()) {
						waste.topItem().hide();
						StacktoStack(waste, stock);
					}
					stock.topItem().show();
					StacktoStack(stock, waste);
					commands.Push(command);
					break;
				}
			}
			if (command.getCommand() == 'm') {
				if (command.getSource()[0] == 'c' && command.getDest()[0] == 'c') {
					if (command.getSource()[1] < '1' || command.getSource()[1] > '7') {
						cout << "Source Column Number is Invalid. ";
						continue;
					}
					if (command.getDest()[1] < '1' || command.getDest()[1] > '7') {
						cout << "Destination Column Number is Invalid. ";
						continue;
					}
					if (command.getSource()[1] == command.getDest()[1]) {
						cout << "Source Column Can't be same as Destnation Column. ";
						continue;
					}
					int sc = (command.getSource()[1] - '0') - 1;
					int dc = (command.getDest()[1] - '0') - 1;
					if (command.getNum() > tableu[sc].Size()) {
						cout << "Can't move this many cards. ";
						continue;
					}
					Stack<Card> movingCards;
					bool allVisible = true;
					for (int i = 0; i < command.getNum(); i++) {
						if (!tableu[sc].tailItem().isVisible()) {
							allVisible = false;
						}

						ListtoStack(tableu[sc], movingCards);
					}
					if (!allVisible) {
						for (int i = 0; i < command.getNum(); i++) {
							StacktoList(movingCards, tableu[sc]);
						}
						cout << "Can't move hidden cards. ";
						continue;
					}
					if (toCValid(movingCards.topItem(), tableu[dc])) {
						for (int i = 0; i < command.getNum(); i++) {
							StacktoList(movingCards, tableu[dc]);
						}
						if(!tableu[sc].isEmpty()) tableu[sc].tailItem().show();
						commands.Push(command);
						break;
					}
					else {
						cout << "Rank/Color of source card NOT valid. ";
						continue;
					}
				}
				if (command.getSource()[0] == 'w' && command.getDest()[0] == 'c') {
					if (waste.isEmpty()) {
						cout << "Waste Stack is Empty. ";
						continue;
					}
					if (command.getNum() != 1) {
						cout << "can ONLY move 1 card from waste to tableu columns. ";
						continue;
					}
					if (command.getDest()[1] < '1' || command.getDest()[1] > '7') {
						cout << "Destination Column Number is Invalid. ";
						continue;
					}
					int dc = (command.getDest()[1] - '0') - 1;
					if (toCValid(waste.topItem(), tableu[dc])) {
						StacktoList(waste, tableu[dc]);
						commands.Push(command);
						break;
					}
					else {
						cout << "Rank/Color of source card NOT valid. ";
						continue;
					}
				}
				if (command.getSource()[0] == 'w' && command.getDest()[0] == 'f') {
					if (waste.isEmpty()) {
						cout << "Waste Stack is Empty. ";
						continue;
					}
					if (command.getNum() != 1) {
						cout << "Can ONLY move 1 card from Waste to Foundation. ";
						continue;
					}
					if (command.getDest()[1] < '1' || command.getDest()[1] > '4') {
						cout << "Destination Column Number is Invalid. ";
						continue;
					}
					int dc = (command.getDest()[1] - '0') - 1;
					if (toFValid(waste.topItem(), foundation[dc])) {
						StacktoStack(waste, foundation[dc]);
						commands.Push(command);
						break;
					}
					else {
						cout << "Rank/Color of source card NOT valid. ";
						continue;
					}
				}
				if (command.getSource()[0] == 'c' && command.getDest()[0] == 'f') {
					if (command.getNum() != 1) {
						cout << "Can ONLY move 1 card from Waste to Foundation. ";
						continue;
					}
					if (command.getSource()[1] < '1' || command.getSource()[1] > '7') {
						cout << "Source Column Number is Invalid. ";
						continue;
					}
					if (command.getDest()[1] < '1' || command.getDest()[1] > '4') {
						cout << "Destination Column Number is Invalid. ";
						continue;
					}
					int sc = (command.getSource()[1] - '0') - 1;
					int dc = (command.getDest()[1] - '0') - 1;
					if (toFValid(tableu[sc].tailItem(), foundation[dc])) {
						ListtoStack(tableu[sc], foundation[dc]);
						if (!tableu[sc].isEmpty()) tableu[sc].tailItem().show();
						commands.Push(command);
						break;
					}
					else {
						cout << "Rank/Color of source card NOT valid. ";
						continue;
					}
				}
				if (command.getSource()[0] == 'f' && command.getDest()[0] == 'c') {
					if (command.getNum() != 1) {
						cout << "Can ONLY move 1 card from Foundation to Tableu Columns. ";
						continue;
					}
					if (command.getSource()[1] < '1' || command.getSource()[1] > '4') {
						cout << "Source Column Number is Invalid. ";
						continue;
					}
					if (command.getDest()[1] < '1' || command.getDest()[1] > '7') {
						cout << "Destination Column Number is Invalid. ";
						continue;
					}
					int sc = (command.getSource()[1] - '0') - 1;
					int dc = (command.getDest()[1] - '0') - 1;
					if (toCValid(foundation[sc].topItem(), tableu[dc])) {
						StacktoList(foundation[sc], tableu[dc]);
						commands.Push(command);
						break;
					}
					else {
						cout << "Rank/Color of source card NOT valid. ";
						continue;
					}
				}
			}
			if (command.getCommand() == 'z') {
				if (commands.isEmpty()) {
					cout << "Can't undo from start of game. ";
					continue;
				}
				Command lastCommand = commands.Pop();
				if (lastCommand.getCommand() == 's') {
					if (waste.Size() == 1 && !commands.isEmpty()) {
						waste.topItem().hide();
						StacktoStack(waste, stock);
						while (!stock.isEmpty()) {
							stock.topItem().show();
							StacktoStack(stock, waste);
						}
						break;
					}
					else {
						waste.topItem().hide();
						StacktoStack(waste, stock);
						break;
					}
				}
				if (lastCommand.getCommand() == 'm') {
					if (lastCommand.getSource()[0] == 'c' && lastCommand.getDest()[0] == 'c') {
						int sc = (lastCommand.getSource()[1] - '0') - 1;
						int dc = (lastCommand.getDest()[1] - '0') - 1;
						if(!tableu[sc].isEmpty())tableu[sc].tailItem().hide();
						Stack<Card> movingCards;
						for (int i = 0; i < lastCommand.getNum(); i++) {
							ListtoStack(tableu[dc], movingCards);
						}
						for (int i = 0; i < lastCommand.getNum(); i++) {
							StacktoList(movingCards, tableu[sc]);
						}
						break;
					}
					if (lastCommand.getSource()[0] == 'w' && lastCommand.getDest()[0] == 'c') {
						int dc = (lastCommand.getDest()[1] - '0') - 1;
						ListtoStack(tableu[dc], waste);
						break;
					}
					if (lastCommand.getSource()[0] == 'w' && lastCommand.getDest()[0] == 'f') {
						int dc = (lastCommand.getDest()[1] - '0') - 1;
						StacktoStack(foundation[dc], waste);
						break;
					}
					if (lastCommand.getSource()[0] == 'c' && lastCommand.getDest()[0] == 'f') {
						int sc = (lastCommand.getSource()[1] - '0') - 1;
						int dc = (lastCommand.getDest()[1] - '0') - 1;
						if (!tableu[sc].isEmpty()) tableu[sc].tailItem().hide();
						StacktoList(foundation[dc], tableu[sc]);
						break;
					}
					if (lastCommand.getSource()[0] == 'f' && lastCommand.getDest()[0] == 'c') {
						int sc = (lastCommand.getSource()[1] - '0') - 1;
						int dc = (lastCommand.getDest()[1] - '0') - 1;
						ListtoStack(tableu[dc], foundation[sc]);
						break;
					}
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
		if (stock.Size() == 1) cout << "(" << stock.Size() << " card)\t";
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

	bool checkWin() {
		bool win = true;
		for (int i = 0; i < 4; i++) {
			if (foundation[i].Size() != 13) win = false;
		}
		return win;
	}

	void Restart() {
		for (int i = 0; i < 52; i++) deck[i].hide();
		for (int i = 0; i < 4; i++) {
			while (!foundation[i].isEmpty()) foundation[i].Pop();
		}
		for (int i = 0; i < 7; i++) {
			while (!tableu[i].isEmpty()) tableu[i].deleteFromEnd();
		}
		while (!stock.isEmpty()) stock.Pop();
		while (!waste.isEmpty()) waste.Pop();
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
};