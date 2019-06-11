// CSCI 2270 Data Structures and Algorithms
// Student name: Kin Seet
// Spring 2018
// Instructor: Dr. Hoenigman
// TA: Shayon Gupta
// Project
// Command line: g++ -std=c++11 priorityQueueHeap.cpp priorityQueueLL.cpp FinalProject.cpp -o FinalProject
// Run: .\FinalProject patientData2270.csv

#ifndef PRIORITYQUEUEHEAP_H
#define PRIORITYQUEUEHEAP_H

#include<iostream>

using namespace std;

struct binaryHeap
{
	binaryHeap(){};
	string name;
	int priorTime;
	int treatmentTime;
};


class heapQueue
{
public:
    heapQueue();
    ~heapQueue();
    bool printQueueHeap();
    void buildQueueHeap(string, int, int);
    int deheap();
    void minHeapify(int);
    
protected:
private:
	int currentSize;
	binaryHeap heapArray[881];
};

#endif 