// CSCI 2270 Data Structures and Algorithms
// Student name: Kin Seet
// Spring 2018
// Instructor: Dr. Hoenigman
// TA: Shayon Gupta
// Project
// Command line: g++ -std=c++11 priorityQueueHeap.cpp priorityQueueLL.cpp FinalProject.cpp -o FinalProject
// Run: .\FinalProject patientData2270.csv
// gdb command: g++ -std=c++11 -g project.cpp projectmain.cpp -o projectmain.out
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <queue>
#include <vector>
#include <algorithm>
#include <chrono>
#include <time.h>
#include <ratio>
#include "priorityQueueLL.hpp"
#include "priorityQueueHeap.hpp"

using namespace std::chrono;

void menu()
{
	cout << "======Main Menu======" << endl;
	cout << "1. Print LL priority queue" << endl;
	cout << "2. Print heap priority queue" << endl;
	cout << "3. Print STL priority queue" << endl;
	cout << "4. Dequeue LL priority queue" << endl;
	cout << "5. Dequeue heap priority queue" << endl;
	cout << "6. Dequeue STL priority queue" << endl;
	cout << "7. Dequeue all LL priority queue" << endl;
	cout << "8. Dequeue all heap priority queue" << endl;
	cout << "9. Dequeue all STL priority queue" << endl;
	cout << "0. Quit" << endl;
}

void LLqueue(QueueList* qlist, char* filename, int num) //Linked List
{
	string file = "patientData2270.csv";
	string file_test = "test.csv";
	ifstream read;
	string header, store, name, priority, treatment;
	read.open(filename);
	int k = 0;
	if(read.is_open())
	{
		read >> header; // get rid of the header
		//const auto begin = high_resolution_clock::now();


		//steady_clock::time_point t1 = steady_clock::now();
		while(read >> store)
		{
			stringstream ss(store);
			
			getline(ss, name, ',');

			getline(ss, priority, ',');

			getline(ss, treatment);

			qlist->buildQueueList(name, stoi(priority), stoi(treatment)); // process data
			k++; //count the number of desired row
			if(k==num) // if reach the number of row, stop reading
			{
				break;
			}
		}
		//auto time = high_resolution_clock::now() - begin;
		//cout << "Run time for adding data to linked list: " << duration<float, micro>(time).count() << " milliseconds." << endl;
		

		// steady_clock::time_point t2 = steady_clock::now();
		// duration<double> time_span = duration_cast<duration<double>>(t2-t1);
		// cout << "Run time for adding data to linked list: " << time_span.count() << " seconds." << endl;
	}
	else
	{
		cout << "Failed to open!!!" << endl;
	}
	read.close();
}

void HeapQueue(heapQueue* qArray, char* filename, int num) //Min Heap
{
	string file = "patientData2270.csv";
	string file_test = "test.csv";
	ifstream read;
	string header, store, name, priority, treatment;
	read.open(filename);
	int i = 0;
	if(read.is_open())
	{
		read >> header;
		//const auto begin = high_resolution_clock::now();

		//steady_clock::time_point t1 = steady_clock::now();
		while(read >> store)
		{
			stringstream ss(store);
			
			getline(ss, name, ',');

			getline(ss, priority, ',');

			getline(ss, treatment);

			qArray->buildQueueHeap(name, stoi(priority), stoi(treatment));
			i++;
			if(i==num)
			{
				break;
			}
		}
		// auto time = high_resolution_clock::now() - begin;
		// cout << "Run time for adding data to array heap: " << duration<double, milli>(time).count() << " milliseconds." << endl;
		

		// steady_clock::time_point t2 = steady_clock::now();
		// duration<double> time_span = duration_cast<duration<double>>(t2-t1);
		// cout << "Run time for adding data to array heap: " << time_span.count() << " seconds." << endl;
	}
	else
	{
		cout << "Failed to open!!!" << endl;
	}
	read.close();
}

//C++ priority queue from Standard Template Library
struct Qlist
{
	string patient;
	int prior;
	int treat;
};
class comparator
{
public:
	bool operator()(const Qlist& a, const Qlist& b)
	{
		if(a.patient < b.patient && a.prior == b.prior && a.treat == b.treat)
		{
			return false;
		}
		else if(a.prior < b.prior)
		{
			return false;
		}
		else if(a.prior == b.prior && a.treat < b.treat)
		{
			return false;
		}
	}
};
priority_queue<Qlist, vector<Qlist>, comparator> pq;
void queueList(char* filename, int num) //STL
{
	bool flag = false;
	Qlist arr[881];
	int p = 0;
	ifstream read;
	string header, store, name, priority, treatment;
	read.open(filename);
	if(read.is_open())
	{
		read >> header;
		//const auto begin = high_resolution_clock::now();
		
		//steady_clock::time_point t1 = steady_clock::now();
		while(read >> store)
		{
			stringstream ss(store);
			
			getline(ss, name, ',');

			getline(ss, priority, ',');

			getline(ss, treatment);

			arr[p].patient = name;
			arr[p].prior = stoi(priority);
			arr[p].treat = stoi(treatment);
			pq.push(arr[p]);
			p++;
			if(p == num)
			{
				break;
			}
		}
		// auto time = high_resolution_clock::now() - begin;
		// cout << "Run time for adding data to STL priority queue: " << duration<double, milli>(time).count() << " milliseconds." << endl;
		

		// steady_clock::time_point t2 = steady_clock::now();
		// duration<double> time_span = duration_cast<duration<double>>(t2-t1);
		// cout << "Run time for adding data to STL priority queue: " << time_span.count() << " seconds." << endl;
	}
	else
	{
		cout << "Failed to open!!!" << endl;
	}
	read.close();
}

bool deSTL()
{
	if(pq.empty())
	{
		return true;
	}
	else
	{
		pq.pop();
	}
}

bool printSTL()
{
	int c = 0;
	if(pq.empty())
	{
		cout << "List is empty" << endl;
		return true;
	}
	else
	{
		while(!pq.empty())
		{
			c++;
			cout << c << ":\t";
			cout << pq.top().patient << ",  ";
			cout << pq.top().prior << ",  ";
			cout << pq.top().treat << endl;
			pq.pop();
		}
	}
}

int main(int argc, char *argv[])
{
	QueueList list;
	heapQueue heap;

	//Enqueue and Deque
	/*
	double tot1;
	double tot2;
	double tot3;
	ofstream write;
	write.open("Runtime report.csv");
	write << "Numbers of rows,QueueLL(milliseconds),Heap(milliseconds),STL(milliseconds),\n";
	int size = 8;
	int num = 110;
	string name[size] = {"110 rows", "220 rows", "330 rows", "440 rows", "550 rows", "660 rows", "770 rows", "880 rows"};
	for(int j = 0 ; j < size ; j++)
	{
		tot1 = 0.0;
		tot2 = 0.0;
		tot3 = 0.0;
		for(int k = 0 ; k < 500 ; k++)
		{
			const auto begin1 = high_resolution_clock::now();
			LLqueue(&list, argv[1], num);
			list.clearLL();
			auto time1 = high_resolution_clock::now() - begin1;
			tot1 += duration<double, milli>(time1).count();

			int q = 0;
			const auto begin2 = high_resolution_clock::now();
			HeapQueue(&heap, argv[1], num);
			while(q!=-1)
			{
				q = heap.deheap();
			}
			auto time2 = high_resolution_clock::now() - begin2;
			tot2 += duration<double, milli>(time2).count();
			
			const auto begin3 = high_resolution_clock::now();
			queueList(argv[1], num);
			while(!deSTL())
			{
				deSTL();
			}
			auto time3 = high_resolution_clock::now() - begin3;
			tot3 += duration<double, milli>(time3).count();
		}
		num+=110;
		write << name[j] + ",";
		write << to_string(tot1/500.0) + ",";
		write << to_string(tot2/500.0) + ",";
		write << to_string(tot3/500.0) + ",";
		write << "\n";
	}
	write.close();
	*/

	//Enqueue
	/*
	double tot1;
	double tot2;
	double tot3;
	ofstream write;
	write.open("Runtime report for build.csv");
	write << "Numbers of rows,QueueLL(milliseconds),Heap(milliseconds),STL(milliseconds),\n";
	int size = 8;
	int num = 110;
	int q = 0;
	string name[size] = {"110 rows", "220 rows", "330 rows", "440 rows", "550 rows", "660 rows", "770 rows", "880 rows"};
	for(int j = 0 ; j < size ; j++)
	{
		tot1 = 0.0;
		tot2 = 0.0;
		tot3 = 0.0;
		for(int k = 0 ; k < 500 ; k++)
		{
			const auto begin1 = high_resolution_clock::now();
			LLqueue(&list, argv[1], num);
			auto time1 = high_resolution_clock::now() - begin1;
			tot1 += duration<double, milli>(time1).count();

			const auto begin2 = high_resolution_clock::now();
			HeapQueue(&heap, argv[1], num);
			auto time2 = high_resolution_clock::now() - begin2;
			tot2 += duration<double, milli>(time2).count();

			const auto begin3 = high_resolution_clock::now();
			queueList(argv[1], num);
			auto time3 = high_resolution_clock::now() - begin3;
			tot3 += duration<double, milli>(time3).count();

			list.clearLL();
			q = 0;
			while(q!=-1)
			{
				q = heap.deheap();
			}
			while(!deSTL())
			{
				deSTL();
			}
		}
		num+=110;
		write << name[j] + ",";
		write << to_string(tot1/500) + ",";
		write << to_string(tot2/500) + ",";
		write << to_string(tot3/500) + ",";
		write << "\n";
	}
	write.close();
	*/

	//Deque
	/*
	double tot1;
	double tot2;
	double tot3;
	ofstream write;
	write.open("Runtime report for deque.csv");
	write << "Numbers of rows,QueueLL(milliseconds),Heap(milliseconds),STL(milliseconds),\n";
	int size = 8;
	int num = 110;
	int q = 0;
	string name[size] = {"110 rows", "220 rows", "330 rows", "440 rows", "550 rows", "660 rows", "770 rows", "880 rows"};
	for(int j = 0 ; j < size ; j++)
	{
		tot1 = 0.0;
		tot2 = 0.0;
		tot3 = 0.0;
		for(int k = 0 ; k < 500 ; k++)
		{
			LLqueue(&list, argv[1], num);
			const auto begin1 = high_resolution_clock::now();
			list.clearLL();
			auto time1 = high_resolution_clock::now() - begin1;
			tot1 += duration<double, milli>(time1).count();

			HeapQueue(&heap, argv[1], num);
			q = 0;
			const auto begin2 = high_resolution_clock::now();
			while(q!=-1)
			{
				q = heap.deheap();
			}
			auto time2 = high_resolution_clock::now() - begin2;
			tot2 += duration<double, milli>(time2).count();

			queueList(argv[1], num);
			const auto begin3 = high_resolution_clock::now();
			while(!deSTL())
			{
				deSTL();
			}
			auto time3 = high_resolution_clock::now() - begin3;
			tot3 += duration<double, milli>(time3).count();
		}
		num+=110;
		write << name[j] + ",";
		write << to_string(tot1/500.0) + ",";
		write << to_string(tot2/500.0) + ",";
		write << to_string(tot3/500.0) + ",";
		write << "\n";
	}
	write.close();
	*/

	string option = "";
	while(option != "0")
	{
		bool empty = false;
		menu();
		getline(cin, option);
		string response = "";
		if(option=="1") // print LL
		{
			const auto begin = high_resolution_clock::now();
			//steady_clock::time_point t1 = steady_clock::now();
			empty = list.printList();
			// steady_clock::time_point t2 = steady_clock::now();
			// duration<double> time_span = duration_cast<duration<double>>(t2-t1);
			// cout << "Run time for printing from linked list: " << time_span.count() << " seconds." << endl;
			if(empty)
			{
				while(response!="Y" && response!="y" && response!="N" && response!="n")
				{
					cout << "Would you like to create a list? " << "Y/N" << endl;
					getline(cin, response);
					if(response == "Y" || response == "y")
					{
						LLqueue(&list, argv[1],0);
					}
					else if(response == "N" || response == "n")
					{
						cout << "Go back to menu" << endl;
					}
					else
					{
						cout << "Invalid input" << endl;
					}
				}
			}
			else
			{
				auto time = high_resolution_clock::now() - begin;
				cout << "Run time for printing from linked list: " << duration<double, milli>(time).count() << " milliseconds." << endl;
			}
		}
		else if(option=="2") //print heap
		{
			string ans = "";
			const auto begin = high_resolution_clock::now();
			//steady_clock::time_point t1 = steady_clock::now();
			empty = heap.printQueueHeap();
			if(empty)
			{
				while(ans!="Y" && ans!="y" && ans!="N" && ans!="n")
				{
					cout << "Would you like to create a list? " << "Y/N" << endl;
					getline(cin, ans);
					if(ans == "Y" || ans == "y")
					{
						HeapQueue(&heap, argv[1],0);
					}
					else if(ans == "N" || ans == "n")
					{
						cout << "Go back to menu" << endl;
						break;
					}
					else
					{
						cout << "Invalid input" << endl;
					}
				}
			}
			else
			{
				auto time = high_resolution_clock::now() - begin;
				cout << "Run time for printing from heap: " << duration<double, milli>(time).count() << " milliseconds." << endl;
				// steady_clock::time_point t2 = steady_clock::now();
				// duration<double> time_span = duration_cast<duration<double>>(t2-t1);
				// cout << "Run time for printing from heap: " << time_span.count() << " seconds." << endl;
			}
		}
		else if(option=="3") // print STL
		{
			string res = "";
			const auto begin = high_resolution_clock::now();
			//steady_clock::time_point t1 = steady_clock::now();
			empty = printSTL();
			if(empty)
			{
				while(res!="Y" && res!="y" && res!="N" && res!="n")
				{
					cout << "Would you like to create a list? " << "Y/N" << endl;
					getline(cin, res);
					if(res == "Y" || res == "y")
					{
						queueList(argv[1],0);
					}
					else if(res == "N" || res == "n")
					{
						cout << "Go back to menu" << endl;
						break;
					}
					else
					{
						cout << "Invalid input" << endl;
					}
				}
			}
			else
			{
				auto time = high_resolution_clock::now() - begin;
				cout << "Run time for printing data from STL priority queue: " << duration<double, milli>(time).count() << " milliseconds." << endl;
				// steady_clock::time_point t2 = steady_clock::now();
				// duration<double> time_span = duration_cast<duration<double>>(t2-t1);
				// cout << "Run time for printing data from STL priority queue: " << time_span.count() << " seconds." << endl;
			}
		}
		else if(option=="4") //deque LL
		{
			const auto begin = high_resolution_clock::now();
			//steady_clock::time_point t1 = steady_clock::now();
			list.delist();
			auto time = high_resolution_clock::now() - begin;
			cout << "Run time for deque from linked list: " << duration<double, milli>(time).count() << " milliseconds." << endl;
			// steady_clock::time_point t2 = steady_clock::now();
			// duration<double> time_span = duration_cast<duration<double>>(t2-t1);
			// cout << "Run time for deque from linked list: " << time_span.count() << " seconds." << endl;
		}
		else if(option=="5") //deque heap
		{
			const auto begin = high_resolution_clock::now();
			steady_clock::time_point t1 = steady_clock::now();
			heap.deheap();
			auto time = high_resolution_clock::now() - begin;
			cout << "Run time for deque from heap: " << duration<double, milli>(time).count() << " milliseconds." << endl;
			// steady_clock::time_point t2 = steady_clock::now();
			// duration<double> time_span = duration_cast<duration<double>>(t2-t1);
			// cout << "Run time for deque from heap: " << time_span.count() << " seconds." << endl;
		}
		else if(option=="6") // deque STL
		{
			const auto begin = high_resolution_clock::now();
			steady_clock::time_point t1 = steady_clock::now();
			deSTL();
			auto time = high_resolution_clock::now() - begin;
			cout << "Run time for deque from STL: " << duration<double, milli>(time).count() << " milliseconds." << endl;
			// steady_clock::time_point t2 = steady_clock::now();
			// duration<double> time_span = duration_cast<duration<double>>(t2-t1);
			// cout << "Run time for deque from STL: " << time_span.count() << " seconds." << endl;
		}
		else if(option=="7") // deque all LL
		{
			if(list.clearLL()!=-1)
			{
				const auto begin = high_resolution_clock::now();
				steady_clock::time_point t1 = steady_clock::now();
				while(list.clearLL()!=-1)
				{
					list.clearLL();
				}
				auto time = high_resolution_clock::now() - begin;
				cout << "Run time for deque all linked list: " << duration<double, milli>(time).count() << " milliseconds." << endl;
				// steady_clock::time_point t2 = steady_clock::now();
				// duration<double> time_span = duration_cast<duration<double>>(t2-t1);
				// cout << "Run time for deque all linked list: " << time_span.count() << " seconds." << endl;
			}
			else
			{
				cout << "No more pregnant women" << endl;
			}
		}
		else if(option=="8") // deque all heap
		{
			if(heap.deheap()!=-1)
			{
				const auto begin = high_resolution_clock::now();
				steady_clock::time_point t1 = steady_clock::now();
				while(heap.deheap()!=-1)
				{
					heap.deheap();
				}
				auto time = high_resolution_clock::now() - begin;
				cout << "Run time for deque from heap: " << duration<double, milli>(time).count() << " milliseconds." << endl;
				// steady_clock::time_point t2 = steady_clock::now();
				// duration<double> time_span = duration_cast<duration<double>>(t2-t1);
				// cout << "Run time for deque all linked list: " << time_span.count() << " seconds." << endl;
			}
			else
			{
				cout << "No more pregnant women" << endl;
			}
		}
		else if(option=="9") // deque all STL
		{
			if(!deSTL())
			{
				const auto begin = high_resolution_clock::now();
				//steady_clock::time_point t1 = steady_clock::now();
				while(!deSTL())
				{
					deSTL();
				}
				auto time = high_resolution_clock::now() - begin;
				cout << "Run time for deque all STL: " << duration<double, milli>(time).count() << " milliseconds." << endl;
				// steady_clock::time_point t2 = steady_clock::now();
				// duration<double> time_span = duration_cast<duration<double>>(t2-t1);
				// cout << "Run time for deque all linked list: " << time_span.count() << " seconds." << endl;
			}
			else
			{
				cout << "No more pregnant women" << endl;
			}
		}
		else if(option=="0") // terminate program
		{
			cout << "Thank you and goodbye" << endl;
		}
	}
	return 0;
}
