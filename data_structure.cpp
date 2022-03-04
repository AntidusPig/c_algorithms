#include <iostream>
#include<string>
#include<vector>
#include "data_structure.h"
#include "exceptions.h"
/*linked list*/
using namespace std;
template <class T>
LinkedList<T>::LinkedList(T arr[], int len) {
	if (len > 0) {
		start = new node;
		start->data = arr[0];
		node* last_n = start;
		node* n = start;
		for (int i = 1; i < len; i++)
		{
			n = new node();
			n->data = arr[i];
			last_n->next = n;
			last_n = n;
		}
		n->next = NULL;
		length = len;
	}
	else {
		cout << "Given length is less than one" << endl;
		//TODO
	}
}

template <class T>
LinkedList<T>::~LinkedList() {
	node* varptr = start;
	node* next = start->next;
	do {
		free(varptr);
		varptr = next;
		next = varptr->next;
	} while (next != NULL);
}

template <class T>
int LinkedList<T>::alterNode(T data, int pos) {
	if (pos > length-1||pos<0) {
		throw OutOfRange(length, pos);
	}
	node* varptr = start;
	while (pos > 0) {
		varptr = varptr->next;
		pos--;
	}

	varptr->data = data;
	return 0;
}

template <class T>
int LinkedList<T>::insertNode(T data, int pos) {
	if (pos > length) {
		throw OutOfRange(length, pos);
	}
	node* n = new node;
	n->data = data;
	if (pos < 1) {
		n->next = start;
		start = n;
		length++;
		return 0;
	}
	node* varptr = start;
	while (pos > 1) {
		varptr = varptr->next;
		pos--;
	}
	if (varptr->next != NULL) {
		n->next = varptr->next;
	}
	else {
		n->next = NULL;
	}
	varptr->next = n;
	length++;
	return 0;
}

template <class T>
T LinkedList<T>::findNode(int pos) {
	if (pos > length - 1||pos<0) {
		throw OutOfRange(length,pos);
	}
	node* varptr = start;
	while (pos > 0) {
		varptr = varptr->next;
		pos--;
	}
	return varptr->data;
}

template <class T>
vector<int> LinkedList<T>::findNodeByVal(T data) {
	node* varptr = start;
	vector<int> foundat;
	int i = 0;
	do {
		if (varptr->data == data) {
			foundat.push_back(i);
		}
		varptr = varptr->next;
		i++;
	} while (varptr != NULL);
	return foundat;
}

template <class T>
int LinkedList<T>::deleteNode(int pos) {
	if (pos > length-1||pos<0) {
		throw OutOfRange(length, pos);
	}
	if (pos == 0) {
		start = start->next;
		length--;
		return 0;
	}
	node* varptr = start;
	while (pos > 1) {
		varptr = varptr->next;
		pos--;
	}
	node* to_be_deleted = varptr->next;
	varptr->next = varptr->next->next;
	free(to_be_deleted);
	length--;
	return 0;
}

template <class T>
int LinkedList<T>::deleteNodeByVal(T data, bool all){   
	node * pre,*p;
	bool deleted = false;
	pre = start;
	p = pre->next;
	while (p != NULL) {
		if (pre->data == data && pre == start) {  //logically the second condition is always true if the first one is true
			start = start->next;
			pre = start;
			p = pre->next;
			length--;
			deleted = true;
			if (!all) { return 0; }
		}
		if (p->data == data) {      
			pre->next = p->next;
			free(p);  
			p = pre->next;
			length--;
			deleted = true;
			if (!all) { return 0; }
		}
		else {
			pre = p;         //should be pre=pre->next； 
			p = p->next;
		}
	}
	if (deleted) {
		return 0;
	}
	else { return 1; }
}

template <class T>
int LinkedList<T>::showList() {
	node* varptr = start;
	do {
		cout << varptr->data << ", ";
		varptr = varptr->next;
	} while (varptr != NULL);
	cout << endl;
	return 0;
}


int linked_list_test() {
	cout << "---------------------linked-list-test-module----------------------" << endl;
	string names[] = {"茄","Giao","蓝🐍","逸啸","笼包","老祁","慕斯"};
	int length = 7;

	//initialisation
	LinkedList<string> llist (names,length);
	string newName = "Stig";
	llist.showList();

	//alter node
	llist.alterNode(newName, 1);
	llist.showList();

	//insert node
	newName = "狗旭";
	llist.insertNode(newName,3);
	llist.showList();
	newName = "狗旭";
	llist.insertNode(newName, 8);
	llist.showList();
	newName = "燕南";
	llist.insertNode(newName, 0);
	llist.showList();

	//node deletion
	llist.deleteNode(0);
	llist.showList();
	llist.deleteNode(3);
	llist.showList();
	llist.deleteNode(7);
	llist.showList();

	//node found by value
	string findName = "慕斯";
	llist.insertNode(findName,0);
	llist.insertNode(findName,llist.size());
	llist.insertNode(findName,5);
	cout << "Now list is changed to: " << endl;
	llist.showList();
	vector<int> res = llist.findNodeByVal(findName);

	cout << "Found occurences of " << findName << " for " << to_string(res.size()) << " time(s) " << "at: " << endl;

	for (int i = 0; i < res.size();i++) {
		cout << to_string(res[i]) << "  ";
	}
	cout << endl;


	//node deletion by value
	llist.deleteNodeByVal(findName, true);
	llist.showList();

	//find node
	cout << "Node at 0: " << llist.findNode(0) << endl;
	cout << "Node at 4: " << llist.findNode(4) << endl;
	cout << "Node at the end: " << llist.findNode(llist.size()-1) << endl;

	return 0;
}





/*stack*/
template <class T>
Stack<T>::Stack()
{
	start = new T[m_stepSize];
	m_capacity = m_stepSize;
	m_len = 0;
}

template<class T>
Stack<T>::Stack(int length, T* array) { //load an array into stack
	start = new T[length + m_stepSize];
	for (size_t i = 0; i < length; i++)
	{
		start[i] = array[i];
	}
	m_capacity = length + m_stepSize;
	m_len = length;
}

template <class T>
int Stack<T>::push(T data)
{
	if (m_len < m_capacity) {
		start[m_len] = data;
		m_len++;
	}
	else {
		T* temp;
		temp = new T[m_capacity + m_stepSize];
		for (size_t i = 0; i < m_capacity; i++)
		{
			temp[i] = start[i];
		}
		delete[] start;
		start = temp;
		m_capacity += m_stepSize;
		start[m_len] = data;
		m_len++;
	}
	return m_len - 1;
}

template<class T>
T Stack<T>::pop() {
	if (m_len == 0) {
		throw OutOfRange();
	}
	else {
		T v = start[m_len - 1];
		m_len--;
		return v;
	}
}

int stack_test() {
	cout << "-------------------------stack-test-module----------------------" << endl;
	string name = "Richard";
	string name2 = "Louis";
	Stack<string> s{ 3, new string[3]{name,name,name} };
	cout << s.pop() << " ";
	cout << s.pop() << " ";
	s.push(name2);
	cout << s.pop() << endl;
	cout << "size of stack is "<< s.size() << endl;
	return 0;
}




/*pythonic array*/
template <class T>
Array<T>::Array() {
	start = (int*)malloc(sizeof(int) * m_stepSize);
	m_capacity = m_stepSize;
	m_len = 0;
}
template <class T>
T Array<T>::operator[](int index) const {
	if (index < 0 || index >= m_len) {
		throw OutOfRange(m_len, index);
	}
	return *(start + index);
}

template <class T>
int Array<T>::push(T data) {
	if (m_len >= m_capacity) {
		m_capacity += m_stepSize;
		start = (int*)realloc(start, sizeof(int) * m_capacity);
	}
	*(start + m_len) = data;
	m_len++;
	return m_len - 1;
}

template <class T>
int Array<T>::pop() {
	if (m_len == 0) {
		throw OutOfRange();
	}
	m_len--;
	return start[m_len]; //can this work
}

template <class T>
void Array<T>::print() {
	cout <<  "[";
	for (size_t i = 0; i < m_len - 1; i++)
	{
		cout << start[i] << ", ";
	}
	cout << start[m_len - 1] << "]";
}

int array_test() {
	cout << "-------------------------array-test-module----------------------" << endl;
	Array<int> a;
	cout << "Length of a is " << a.size() << endl;
	for (int i = 0; i < 10; i++)
	{
		a.push(i);
	}
	a.print();
	cout << "Pop an element: " << a.pop() << "." << endl;
	return 0;
}



/*Binary tree*/
BinaryTree<T>::BinaryTree()
{

}

BinaryTree<T>::~BinaryTree()
{
}