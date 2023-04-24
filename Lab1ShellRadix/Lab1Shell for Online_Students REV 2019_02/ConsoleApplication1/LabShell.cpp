
// LabShell.cpp : Defines the entry point for the console application.
// Feb 2019.

//Derek D'Arcy
//2/23/23
//DATA STRUCTURES

#include "stdafx.h"
using namespace std;
#include <time.h>
#include <fstream>
#include <iostream>
#include <direct.h>

void genData(int *, int);
int radixSort(int *dta, int n, int *out);

class node
{ // The basic node class. You do not have to do anything to this class.
	public:
		node(int n, node *p){data=n;next=p;}
		int data;
		node *next;
};


void genData(int *dta, int n) 
{// This function generates social security numbers that do not contain zeroes (111 111 111 - 999 999 999). You do not have to do anything to this function
	
	for(int i=0; i < n; i++)// generate the social security numbers at random
		dta[i] =  rand()%889 + 111 + 1000*(rand()%889 + 111) + 1000000*(rand()%889 + 111);
}

// *****************************************************************************************************
// you have to write this function - I put pseudo code in to help you ********************************

int radixSort(int *dta, int n, int *out)
{ 
	// the dta array contains the data to be sorted.
	// n is the number of data items in the array
	// out is the array to put the sorted data
	
	node *bucket[1000]; // declare an array of 1000 linked lists (head pointers)
	int count = 0; // you will use this to count the instructions to graph the big-o
	for(int i = 0; i < n; i++)out[i] = dta[i]; // first copy dta into out for use by the shell. Use out from now on in this function

// *********************8 psuedo code follows: **********************

//	for (pass = 0, 1, 2)  // this is the outer loop
//	{
	for (int p = 0; p < 3; p++) {
		// for(j) 0 ->  < 1000, set bucket[] to all zeroes (NULL) for each pass// note we are not deleting the old nodes, this is not good programming because we create a memory leak
		//			if you want to delete the old nodes, go ahead, but it is not necessary for your grade in this lab. The leaked memory goes away once the program ends.
		for (int j = 0; j < 1000; j++) {
			bucket[j] = NULL;
		}

		for (int i = 0; i < n; i++) {
			//  for(i 0,  < n) // inner loop  - walk through the out array (which contains the data to be sorted
		//		{
			int index = 0;
			switch (p) {
			case 0:
				index = out[i] % 1000;  // last three digits
				break;
			case 1:
				index = out[i] % 1000000 / 1000;  //middle 3 digits
				break;
			case 2:
				index = out[i] / 1000000; //first 3 digits
				break;
			};
		//			int index; // where in the bucket do we want to store this data
		//			switch(pass) // refer to the Powerpoint to see how to parse the digits
		//			{// refer to the Powerpoint to see how to parse the digits
		//				case 0:
						// set index to the last 3 digits
		//				break;
		//				case 1;
							// set index to the middle 3 digits
		//				break;
		//				case 2:
						// set index to the first 3 digits
		//				break;
		//			};
			if (bucket[index] == NULL) {
				bucket[index] = new node(out[i], NULL);
				count++;
			}
			else {
				node* newNode = new node(out[i], NULL);
				node* current = bucket[index];
				count++;
				while (current->next != NULL) {
					current = current->next;
					count++;
				}
				current->next = newNode;
			}
		//			if(bucket[index] == NULL)			
		//			{  // nothing is stored here so 
						// bucket[index] = new node(out[i], NULL); // create a new head node and store this data
		//			}
		//			else
		//			{
						// something is already here so make a new node, store the out[i] in the new node
						// walk the linked list from the head (bucket[index] to find the last node (tail).
						// make tail point to the new node you just created.
		//			}

		//		} // end of the inner (i) loop
		}
		int idx = 0;
		for (int i = 0; i < 1000; i++) {
			if (bucket[i] == NULL) {
				continue;
			}
				out[idx++] = bucket[i]->data;
				node* current = bucket[i];
				while (current->next != NULL) {
					out[idx++] = current->next->data;
					current = current->next;
				}
		}
//		int idx = 0; // you need this to load the out array
//		for(i) 0 ->  < 1000  // walk through the bucket
//		{
//			if(bucket[i] == NULL)continue;  nothing was stored here so skip to the next item

			// something is stored here, so put it into the out array starting at the beginning (idx)
			//out[idx++] = bucket[i]->data[i];
			// now see if there are more nodes in the linked list that starts at bucket[i]. If there are, put their data into out[idx++]
//		}
		//	at this point, idx must equal n (use this as a check)
		cout << idx << " should equal " << n << endl;
	}
//	}// end of the outer loop pass). The output (out) from this pass becomes the input for the next pass

	return count; 
}
// ***********end of function you have to write ******************************************************************************************////

////      main program to run the radix sort and create the graphs. You do not have to modify this code 

//int _tmain(int argc, _TCHAR* argv[])
int run()
{
	int *data;// pointer to where input unsorted SSNs will be stored
	int *out;// pointer to where output sorted SSNs will be stored
	int N = 2;// initial size of the SSN data set.
	int NValues[16];  // holds sample sizes from each run
	int C[16];  // holds counts from each run
	double D[16]; // holds times
	double E[16]; // holds times
	_mkdir("data");
	ofstream f;
	ofstream f1;
	f.open("output.csv", ios::out);// open the output excel file
	if(f.is_open())// if it opened, proceed, else issue error and quit
	{
		for(int i = 0; i < 15; i++)
		{// generate 15 sets of data the first of size 2, the next of size 4, until you get to 32768 (2 ^ 15)
			try
			{
				data = new int [N];// allocate memory to hold the data generated by genData
				if(data == NULL)throw "data allocation failed";  // did we get the memory we requested?
				out = new int [N];// allocate memory to hold the data generated by genData
				if(out == NULL)throw "out allocation failed";  // did we get the memory we requested?
			}
			catch (...)
			{
				cout << "... allocation failed";
				exit(0);
			}
			genData(data, N);// generate the SSNs and output them in the array
	
			int k = 0;
			D[i] = 0;
			clock_t start_clock = clock(); // read the clock
			double d = 0;
			int loopcount = 0;
			//for(int j = 0; j < limit; j++)
			while (d == 0)
			{
				k = radixSort(data, N, out); // you write this function to sort the data and count the operations
				d = ( clock() - start_clock) / CLOCKS_PER_SEC;
				loopcount++;
				if(d > 0)break;
			}
			//D[i] = (double)( clock() - start_clock) / CLOCKS_PER_SEC;
			D[i] = d / (double)loopcount;			
			C[i] = k; // store this count for output into the SDI file
			E[i] = D[i] / (double)N;
			NValues[i] = N;  // store this sample size for output in the SDI file
			f << N << "," << k << "," << double(k)/(double)N << endl;// write the data pairs to the excel file for later graphing
			cout << N << "," << k <<  "," << double(k)/(double)N << endl;// write the data pairs to the screen also 

#define debug_radix_sort			// comment this line out if you don't want debug files to be generated
#ifdef debug_radix_sort		
			//  *************  (START) for debugging your radix sort  ***********************
			//  write sorted data into a file so you can see if your sort is working
			char *s = new char[260];
			char *s1 = new char[260];
			sprintf_s(s, 260, "Data//sorted_data_set_%i.txt", N);
			sprintf_s(s1, 260, "Data//unsorted_data_set_%i.txt", N);
			f1.open(s, ios::out);
			if(f1.is_open())
			{// write out sorted data
				for(int k = 0; k < N; k++)f1 << k << "  " << out[k] << "\n";
				f1.close();
			}
			f1.open(s1, ios::out);
			if(f1.is_open())
			{// write out unsorted data
				for(int k = 0; k < N; k++)f1 << k << "  " << data[k] << "\n";
				f1.close();
			}
			delete [] s;
			delete [] s1;
			//  *************  (END) for debugging your radix sort  ***********************
#endif

			N = 2 * N;// double the data size for the next pass
			delete [] data;// free the data array because it will be reallocated next time
		}
		f.close();// close the file
		fstream fpout;	
		fpout.open("edit1.txt", ios::out);
		if(fpout.is_open())
		{
			if(D[0] > 0)fpout << 3 << " " << 15 << endl; // number of curves (nc) and number of points/curve (np)
			else fpout << 1 << " " << 15 << endl; // number of curves (nc) and number of points/curve (np)
			fpout << "Graph of Radix Sorting performance" << endl; // graph title
			fpout << "Big Oh _ counted|Big Oh - timed|count/N" << endl; // curve labels
			fpout << "Sample Size(N)" << endl; // Horizontal axis title
			fpout << "Operations" << endl;  // Vertical axis title
			fpout << "01000000000" << endl;
			fpout << "01000000000" << endl;
			fpout << "loglog" << endl; // can be loglog, loglinear, linearlog, linearlinear (upper of lower case)
			for(int k = 0; k < 15; k++)	fpout << NValues[k] << " ";
			fpout << endl;
			for(int k = 0; k < 15; k++)	fpout << C[k] << " ";
			fpout << endl;
			if(D[0] > 0)
			{
				for(int k = 0; k < 15; k++)	fpout << D[k]  * C[0]/D[0] << " ";
				fpout << endl;
				for(int k = 0; k < 15; k++)	fpout << C[k]/NValues[k] << " ";
				fpout << endl;
				for(int k = 0; k < 15; k++)	fpout << E[k] << " ";
				fpout << endl;
			}
			fpout.close();
		}
	}
	else
	{// file did not open, so alert user and exit
		cout << "csv output file did not open" << endl;
		system("pause");
	}
	system("pause");
	return 0;
}

