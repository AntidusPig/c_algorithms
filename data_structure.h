#ifndef _DATA_STRUCTURE_H_
#define _DATA_STRUCTURE_H_
#include <iostream>
#include<vector>
using namespace std;
//linked list
struct node {
	string data;
	node* next;
};
template <class T>
class LinkedList {
	public:
		LinkedList(T arr[], int len);
		~LinkedList();
		int alterNode(T data, int pos);
		int insertNode(T data, int pos);
		T findNode(int pos);
		vector<int> findNodeByVal(T data);
		int deleteNode(int pos);
		int deleteNodeByVal(T data, bool all);
		int showList();
		int size() const { return length; };
	private:
		node* start;
		unsigned length;
};



//stack
template <class T>
class Stack
{
public:
	Stack();
	Stack(int, T*);
	~Stack() { delete[]start; };
	int size() const { return m_len; };
	int push(T);
	T pop();
private:
	unsigned m_len;
	unsigned m_capacity;
	T* start;  //i always name the start of an array "start"
private:
	static const unsigned m_stepSize = 64;
};

//pythonic array
template <class T>
class Array
{
public:
	Array();
	~Array() { delete[]start; };
public:
	T operator[](int i) const;
	int push(T data);
	int pop();
	void print();
	int size() const { return m_len; };

private:
	unsigned m_len; //数组长度
	unsigned m_capacity; //容量
	T* start; //内存指针
private:
	static const unsigned m_stepSize = 64;

};

//binary tree
template <class T>
class BinaryTree
{
public:
	BinaryTree();
	~BinaryTree();

private:

};

//test modules
int linked_list_test();
int stack_test();
int array_test();

#endif