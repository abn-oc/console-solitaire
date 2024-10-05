#pragma once
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

	class Iterator {
	private:
		Node* itr;
	public:
		friend class List;
		Iterator(Node* it = nullptr) { itr = it; }
		Iterator& operator++() {
			if (itr) itr = itr->next;
			return *this;
		}
		Iterator& operator--() {
			if (itr) itr = itr->prev;
			return *this;
		}
		Node* getNode() { return itr; }
		T& operator*() {
			return itr->data;
		}
		bool operator==(const Iterator b) {
			return itr == b.itr;
		}
		bool operator!=(const Iterator b) {
			return !(itr == b.itr);
		}
	};

	Node* head;
	Node* tail;

public:
	typedef Iterator iter;
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
	T headItem() {
		if (head) return head->data;
		else return T();
	}
	T& tailItem() {
		//if (tail) return tail->data;
		//else return T();
		return tail->data;
	}
	iter begin() {
		Iterator result;
		result.itr = head;
		return result;
	}
	iter end() {
		Iterator result;
		result.itr = nullptr;
		return result;
	}
	int Size() {
		if (isEmpty()) return 0;
		int size = 0;
		Node* curr = head;
		while (curr != nullptr) {
			curr = curr->next;
			size++;
		}
		return size;
	}
};