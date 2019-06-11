// CSCI 2270 Data Structures and Algorithms
// Student name: Kin Seet
// Spring 2018
// Instructor: Dr. Hoenigman
// TA: Shayon Gupta
// Project
// Command line: g++ -std=c++11 priorityQueueHeap.cpp priorityQueueLL.cpp FinalProject.cpp -o FinalProject
// Run: .\FinalProject patientData2270.csv

#ifndef PRIORITYQUEUELL_H
#define PRIORITYQUEUELL_H

#include<iostream>

using namespace std;

struct LinkedList2 //inner linked list
{
	string patient;
	int treatment_time;
	LinkedList2* next2;
	LinkedList2(){};
	LinkedList2(string pa, int t)
	{
		patient = pa;
		treatment_time = t;
		next2 = NULL;
	};
};

struct LinkedList // outter linked list
{
	int prior;
	LinkedList2* head2;
	LinkedList* next;
	LinkedList(){};
	LinkedList(int p)
	{
		prior = p;
		head2 = NULL;
		next = NULL;
	};
};

class QueueList
{
public:
    QueueList();
    ~QueueList();
    void buildQueueList(string, int, int);
    int delist();
    bool printList();
    int clearLL();
   
private:
	LinkedList* head; //head for outter linked list

};

#endif 