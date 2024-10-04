#include<iostream>
using namespace std;

template <typename T>
class List {
private:
	
	class Node {
	public:
		T data;
		Node* next;
		Node* prev;
		Node(T val, Node* nxt, Node* prv) { data = val; next = nxt; prev = prv; }
	};

	Node* head;
	Node* tail;

public:
	List() {
		head = nullptr;
		tail = nullptr;
	}
	~List() {
		if (isEmpty()) return;
		Node* currNode = head;
		while (currNode != nullptr) {
			Node* temp = currNode;
			currNode = currNode->next;
			delete temp;
		}
		head = nullptr;
		tail = nullptr;
	}
	bool isEmpty() {
		return !head;
	}
	void Print() {
		if (isEmpty()) return;
		Node* curr = head;
		while (curr != nullptr) {
			cout << curr->data << "  ";
			curr = curr->next;
		}
		cout << endl;
	}
	void insertAtStart(T newItem) {
		if (isEmpty()) {
			head = new Node(newItem, nullptr, nullptr);
			tail = head;
		}
		else {
			head = new Node(newItem, head, nullptr);
			head->next->prev = head;
		}
	}
	void insertAtEnd(T newItem) {
		if (isEmpty()) {
			head = new Node(newItem, nullptr, nullptr);
			tail = head;
		}
		else {
			tail = new Node(newItem, nullptr, tail);
			tail->prev->next = tail;
		}
	}
	void deleteFromStart() {
		if (head == tail) {
			delete head;
			head = tail = nullptr;
		}
		else {
			Node* temp = head;
			head = head->next;
			head->prev = nullptr;
			delete temp;
		}
	}
	void deleteFromEnd() {
		if (head == tail) {
			delete head;
			head = tail = nullptr;
		}
		else {
			Node* temp = tail;
			tail = tail->prev;
			tail->next = nullptr;
			delete temp;
		}
	}
};