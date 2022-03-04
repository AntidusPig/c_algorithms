#include <iostream>
#include <Windows.h>
#include <vector>
#include <time.h>
#include "sorting.h"


void output_array(int* array, int length) {
	for (int i = 0; i < length; i++) {
		std::cout << *(array + i) << " ";
	}
	std::cout << std::endl;
}

void randomize_array(int* array, int length) {
	//int numbers[] = { 4, 6, 8, 2, 7, 5, 0, 1, 3, 9 };
	//for (int i = 0; i < length; i++) {
	//	*(start + length) = numbers[i];
	//}
	std::vector<int> numbers;
	for (int i = 0; i < length; i++)
	{
		numbers.push_back(array[i]);
	}
	int x;
	for (int i = 0; i < length; i++)
	{
		time_t t;
		srand((unsigned)time(&t));
		x = rand() % (length - i);
		*(array + i) = numbers[x];
		numbers.erase(numbers.begin() + x);
	}
}

void swap(int* a, int* b) {
	int temp;
	temp = *b;
	*b = *a;
	*a = temp;
}

// simple sorts
void selection_sort(int* array, int length) {
	for (int i = 0; i < length; i++) {
		int max = *array;
		int max_i = 0;
		for (int j = 1; j < (length - i); j++) {
			//find out the maximum
			if (max < *(array + j)) {
				max = *(array + j);
				max_i = j;
			}
		}
		//put it at the rear end
		for (int k = max_i; k < (length - i - 1); k++) {
			*(array + k) = *(array + k + 1);
		}
		*(array + length - i - 1) = max;
	}
}

void insertion_sort(int* array, int length) {
	int temp;
	for (int i = 1; i < length; i++)
	{
		for (int j = 0; j < i; j++) {
			if (array[i] < array[j]) {
				temp = array[i];
				for (int k = i; k > j; k--) {
					array[k] = array[k - 1];
				}
				array[j] = temp;
			}
		}
	}
}

//efficient
/*iterationµü´ú
recursionµÝ¹é
Ê±¼ä¸´ÔÓ¶ÈÒ»Ñù£¬
µü´ú×ÊÔ´¿ªÏú´ó
µÝ¹éÂß¼­¼òµ¥*/
void merge_sort(int* array, int length) {
	if (length <= 1) {
		return;
	}
	int half = (int)floor(length / 2);
	//divide and conquer
	merge_sort(array, half);
	merge_sort(array + half, length - half);
	//merge two partially ranked
	int i = 0;
	int j = half;
	int temp;
	while (j < length&& i < j) {
		if (array[i] > array[j]) {
			temp = array[j];
			for (int k = j; k > i; k--) //perhaps make another array is more efficient than using the same one and shift the values
			{
				array[k] = array[k - 1];
			}
			array[i] = temp;
			i++;
			j++;
		}
		else {
			i++;
		}
	}
}

void heap_sort(int* array, int length) {
	if (length <= 1) {
		return;
	}
	//turn heap to max heap (complete binary tree, parent larger than child)
	for (int i = 0; i < (int)floor((length - 1) / 2); i++) //from the last parent
	{
		if (array[2 * i + 1] > array[2 * i + 2] && array[2 * i + 1] > array[i]) {
			swap(array + i, array + 2 * i + 1);
		}
		else if (array[2 * i + 2] > array[i]) {
			swap(array + i, array + 2 * i + 2);
		}
	}
	//the first element (first node) is now the largest. Put and seal it at the end
	swap(array, array + length - 1);
	//anything before the last element is **partially** sorted
	heap_sort(array, length - 1);  //this recursion can always be replaces with a while loop
}

void quick_sort(int* array, int length) {
	if (length <= 1) {
		return;
	}
	int half = (int)floor(length / 2);
	int* temp = new int[length];
	for (int i = 0; i < length; i++)
	{
		temp[i] = array[i];
	}
	int middle = array[half];
	int i = 0;
	int j = length - 1;
	int k = 0;
	while (i != j) {
		if (temp[k] < middle) {
			array[i] = temp[k];
			i++;
		}
		else {
			array[j] = temp[k];
			j--;
		}
		k++;
		if (k == half) {
			k++;
		}
	}
	array[i] = middle;
	delete[] temp;
	quick_sort(array, i);
	quick_sort(array + i + 1, length - i - 1);
}

void shell_sort(int* array, int length) {
	int h = 1;
	while (h < length / 3) {
		h = 3 * h + 1;
	}
	while (h >= 1) {
		for (int i = h; i < length; i++) {
			for (int j = i; j >= h && array[j] < array[j - h]; j -= h) {
				std::swap(array[j], array[j - h]);
			}
		}
		h = h / 3;
	}
}


//bubble sort and variants
void bubble_sort(int* array, int length) {
	for (int i = 0; i < length; i++)
	{
		for (int j = 0; j < length - i - 1; j++) {
			if (array[j] > array[j + 1]) {
				swap(array + j, array + j + 1);
			}
		}
	}
}

void comb_sort(int* array, int length) {
	const double k = 1.24733;
	int gap = length - 1;
	bool sorted = false;
	while (!sorted)
	{
		gap = (int)floor(gap / k);
		if (gap <= 1) {
			gap = 1;
			sorted = true;
		}
		for (int j = 0; j < length - gap; j++)
		{
			if (array[j] > array[j + gap]) {
				swap(array + j, array + j + gap);
				sorted = false;
			}
		}
	}
}

void exchange_sort(int* array, int length) {
	for (int i = 0; i < length; i++)
	{
		for (int j = i + 1; j < length; j++)
		{
			if (array[j] < array[i]) {
				swap(array + i, array + j);
			}
		}
	}
}

//d(istributive) sort
void counting_sort(int* array, int length) { //sorted data must be integers in a given range
}
void bucket_sort(int*, int) {

}
void radix_sort(int*, int) {

}


int sorting_test() {
	using namespace std;
	int numbers[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 3, 3, 5, 5, 4, };
	//const int length = 10;
	const int length = 15;

	//simple
	cout << "Ñ¡ÔñÅÅÐò" << endl;
	randomize_array(numbers, length);
	selection_sort(numbers, length);
	output_array(numbers, length);
	cout << endl;

	cout << "²åÈëÅÅÐò" << endl;
	randomize_array(numbers, length);
	insertion_sort(numbers, length);
	output_array(numbers, length);
	cout << endl;

	//efficient
	cout << "ºÏ²¢ÅÅÐò" << endl;
	randomize_array(numbers, length);
	merge_sort(numbers, length);
	output_array(numbers, length);
	cout << endl;


	cout << "¶ÑÅÅÐò" << endl;
	randomize_array(numbers, length);
	heap_sort(numbers, length);
	output_array(numbers, length);
	cout << endl;

	cout << "¿ìËÙÅÅÐò" << endl;
	randomize_array(numbers, length);
	quick_sort(numbers, length);
	output_array(numbers, length);
	cout << endl;

	cout << "¹ê¿ÇÅÅÐò" << endl;
	randomize_array(numbers, length);
	shell_sort(numbers, length);
	output_array(numbers, length);
	cout << endl;

	//bubble
	cout << "Ã°ÅÝÅÅÐò" << endl;
	randomize_array(numbers, length);
	bubble_sort(numbers, length);
	output_array(numbers, length);
	cout << endl;

	cout << "Êá×ÓÅÅÐò" << endl;
	randomize_array(numbers, length);
	comb_sort(numbers, length);
	output_array(numbers, length);
	cout << endl;

	cout << "½»»»ÅÅÐò" << endl;
	randomize_array(numbers, length);
	exchange_sort(numbers, length);
	output_array(numbers, length);
	cout << endl;

	cout << "-----------TODO-----------" << endl;
	cout << "¼ÆÊýÅÅÐò" << endl;
	randomize_array(numbers, length);
	counting_sort(numbers, length);
	output_array(numbers, length);
	cout << endl;

	cout << "Í°ÅÅÐò" << endl;
	randomize_array(numbers, length);
	bucket_sort(numbers, length);
	output_array(numbers, length);
	cout << endl;

	cout << "»ùÊýÅÅÐò" << endl;
	randomize_array(numbers, length);
	radix_sort(numbers, length);
	output_array(numbers, length);
	cout << endl;

	Sleep(10000);
	return 0;
}