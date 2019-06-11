// CSCI 2270 Data Structures and Algorithms
// Student name: Kin Seet
// Spring 2018
// Instructor: Dr. Hoenigman
// TA: Shayon Gupta
// Project
// Command line: g++ -std=c++11 priorityQueueHeap.cpp priorityQueueLL.cpp FinalProject.cpp -o FinalProject
// Run: .\FinalProject patientData2270.csv

#include<iostream>
#include<fstream>
#include<sstream>
#include <algorithm>
#include <iomanip>
#include "priorityQueueHeap.hpp"

using namespace std;

heapQueue::heapQueue()
{
	currentSize = 0;
}
heapQueue::~heapQueue(){}

void heapQueue::minHeapify(int i)
{
	int left = 2*i;
	int right = (2*i)+1;
	int smallest = i;
	if(left <= currentSize && heapArray[left].priorTime <= heapArray[i].priorTime)
	{
		if(heapArray[left].priorTime < heapArray[i].priorTime)
		{
			smallest = left;
		}
		else if(heapArray[left].priorTime == heapArray[i].priorTime)
		{
			if(heapArray[left].treatmentTime < heapArray[i].treatmentTime)
			{
				smallest = left;
			}
			else if(heapArray[left].name < heapArray[i].name && heapArray[left].treatmentTime == heapArray[i].treatmentTime)
			{
				smallest = left;
			}
		}
	}
	if(right <= currentSize && heapArray[right].priorTime <= heapArray[smallest].priorTime)
	{
		if(heapArray[right].priorTime < heapArray[smallest].priorTime)
		{
			smallest = right;
		}
		else if(heapArray[right].priorTime == heapArray[smallest].priorTime)
		{
			if(heapArray[right].treatmentTime < heapArray[smallest].treatmentTime)
			{
				smallest = right;
			}
			else if(heapArray[right].name < heapArray[smallest].name && heapArray[right].treatmentTime == heapArray[smallest].treatmentTime)
			{
				smallest = right;
			}
		}
	}
	if(smallest!=i)
	{
		swap(heapArray[i], heapArray[smallest]);
		minHeapify(smallest);
	}
}

int heapQueue::deheap()
{
	if(currentSize==0)
	{
		return -1;
	}
	if(currentSize==1)
	{
		currentSize--;
		return heapArray[1].priorTime;
	}
	heapArray[1] = heapArray[currentSize]; //move element at last index to root position
	currentSize--;
	minHeapify(1); //move new root into its correct position
}

bool heapQueue::printQueueHeap()
{
	int k = 0;
	if(currentSize==0)
	{
		cout << "List is empty" << endl;
		return true;
	}
	else
	{
		while(currentSize!=0)
		{
			k++;
			cout << k << ":\t";
			cout << heapArray[1].name << ",  ";
			cout << heapArray[1].priorTime << ",  ";
			cout << heapArray[1].treatmentTime << endl;
			deheap();
		}
		return false;
	}
}

void heapQueue::buildQueueHeap(string n, int p, int t)
{
	currentSize++;
	int i = currentSize;
	heapArray[i].name = n;
	heapArray[i].priorTime = p;
	heapArray[i].treatmentTime = t;
	while(i > 1 && heapArray[i/2].priorTime >= heapArray[i].priorTime) //check if the parent is greater than its child
	{
		if(heapArray[i/2].priorTime == heapArray[i].priorTime)
		{
			if(heapArray[i/2].treatmentTime > heapArray[i].treatmentTime)
			{
				swap(heapArray[i], heapArray[i/2]);
			}
		}
		else if(heapArray[i/2].priorTime > heapArray[i].priorTime)
		{
			swap(heapArray[i], heapArray[i/2]);
		}
		i = i/2;
	}
}
