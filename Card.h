#pragma once
#include<iostream>
using namespace std;

class Card {
private:
	int rank;
	char suite;
	bool visible;
public:
	Card(int r = 0, char s = '\0', bool v = true) {
		rank = r;
		suite = s;
		visible = v;
	}
	friend ostream& operator<<(ostream& cout, Card card) {
		if (!card.isVisible()) {
			cout << "[ ]";
			return cout;
		}
		string rank;
		string suite;
		if (card.rank == 1) rank = "A ";
		else if (card.rank == 10) rank = "10";
		else if (card.rank == 11) rank = "J ";
		else if (card.rank == 12) rank = "Q ";
		else if (card.rank == 13) rank = "K ";
		else rank = string(1, (card.rank + '0')) + " ";

		if (card.suite == 'd') suite = "\u2666";
		else if (card.suite == 'h') suite = "\u2665";
		else if (card.suite == 'c') suite = "\u2663";
		else if (card.suite == 's') suite = "\u2660";

		if (card.suite == 'd' || card.suite == 'h') {
			cout << "\033[31m" << rank << suite << "\033[0m";
		}
		else {
			cout << rank << suite;
		}

		return cout;
	}

	bool isVisible() {
		return visible;
	}
	void show() {
		visible = true;
	}
	void hide() {
		visible = false;
	}
	char getSuite() {
		return suite;
	}
	int getRank() {
		return rank;
	}
	bool isRed() {
		return (suite == 'h' || suite == 'd');
	}
	bool isBlack() {
		return (suite == 's' || suite == 'c');
	}
};