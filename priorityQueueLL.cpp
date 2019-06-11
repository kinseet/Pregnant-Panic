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
#include "priorityQueueLL.hpp"

using namespace std;

QueueList::QueueList()
{
	head = NULL;
}

QueueList::~QueueList(){}

void QueueList::buildQueueList(string patient_name, int prior_time, int treatment_time)
{
	LinkedList* node = new LinkedList(prior_time); // create new node for outter linked list
	LinkedList2* Node = new LinkedList2(patient_name, treatment_time); //create new node for inner linked list
	bool flag = false; 
	if(head == NULL)
	{
		node->head2 = Node;
		head = node;
	}
	else // if head is not null, check prior time 
	{
		LinkedList* temp = head;
		LinkedList* prev;
		while(temp!=NULL) //traverse outter linked list
		{
			if(prior_time < temp->prior) //if new prior time < current prior time, break out the loop
			{
				break;
			}
			else if(prior_time > temp->prior) //else save the current address and move on
			{	
				prev = temp;
				temp = temp->next;
			}
			else if(prior_time == temp->prior) //check the treatment time
			{
				if(temp->head2 == NULL)
				{
					temp->head2 = Node; // if head of inner linked list node is null, set up head
				}
				else // else traverse inner linked list and compare treatment time
				{
					LinkedList2* temp2 = temp->head2;
					LinkedList2* prev2;
					while(temp2!=NULL)
					{
						if(treatment_time < temp2->treatment_time)
						{
							break;
						}
						else
						{
							prev2 = temp2;
							temp2 = temp2->next2;
						}
					}
					if(temp2 == temp->head2)
					{
						Node->next2 = temp->head2;
						temp->head2 = Node;
					}
					else if(prev2->next2 == NULL)
					{
						prev2->next2 = Node;
					}
					else
					{
						Node->next2 = prev2->next2;
						prev2->next2 = Node;
					}
				}
				flag = true; // set flag to true and break
				break;
			}
		}
		if(flag == false) //flag is false when new prior time != current prior time
		{
			node->head2 = Node; // we will connect new node for outter linked list and set up a head for new node's inner linked list 
			//check where we connect the new node with the current node
			if(temp == head)
			{ 
				node->next = head;
				head = node;
			}
			else if(prev->next == NULL)
			{
				prev->next = node;
			}
			else
			{
				node->next = prev->next;
				prev->next = node;
			}
		}
	}
}

bool QueueList::printList()
{
	if(head==NULL)
	{
		cout << "Empty list." << endl;
		return true;
	}
	else
	{
		int j = 0;
		LinkedList* tmp = head;
		while(tmp!=NULL)
		{
			LinkedList2* tmp2 = tmp->head2;
			while(tmp2!=NULL)
			{
				j++;
				cout << j << ":\t";
				cout << tmp2->patient << ",  ";
				cout << tmp->prior << ",  ";
				cout << tmp2->treatment_time << endl;
				tmp2 = tmp2->next2;
			}
			tmp = tmp->next;
		}
		return false;
	}
}

int QueueList::clearLL()
{
	//int i = 0;
	if(head!=NULL)
	{
		LinkedList* tmp = head;
		while(tmp!=NULL)
		{
			LinkedList2* tmp2 = tmp->head2;
			while(tmp2!=NULL)
			{
				LinkedList2* newHead2 = tmp2->next2;
				cout << "Delete: " << tmp2->patient << endl;
				delete tmp2;
				tmp2 = newHead2;
				//i++;
			}
			LinkedList* newHead1 = tmp->next;
			delete head;
			head = newHead1;
			tmp = head;
		}
	}
	else
	{
		return -1;
	}
	
	//cout << "Total patient deleted: " << i << endl;
}

int QueueList::delist()
{
	if(head!=NULL)
	{
		LinkedList2* new_head2 = head->head2->next2; //get head2 from head
		if(head->head2!=NULL)
		{
			//cout << "Delete: " << head->head2->patient << endl;
			delete head->head2;
			head->head2 = new_head2;
			if(head->head2==NULL)
			{
				LinkedList* new_head = head->next;
				delete head;
				head = new_head;
			}
			// if(head!=NULL)
			// {
			// 	cout << "Next patient: " << head->head2->patient << "-----> ";
			// 	cout << "Priority time: " << head->prior << "-----> ";
			// 	cout << "Treatment time: " << head->head2->treatment_time << endl << endl;
			// }
			else if(head==NULL)
			{
				cout << "No more patients" << endl;
				return -1;
			}
		}
	}
	else
	{
		return -1;
	}
}
