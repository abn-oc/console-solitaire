#pragma once
#include<iostream>
#include"List.h"
using namespace std;

template <typename T>
class Stack {
private:
	List<T> list;
public:
	void Push(T newItem) {
		list.insertAtStart(newItem);
	}
	T Pop() {
		T temp = list.headItem();
		list.deleteFromStart();
		return temp;
	}
	T topItem() {
		return list.headItem();
	}
	bool isEmpty() {
		return list.isEmpty();
	}
	void Print() {
		list.Print();
	}
};