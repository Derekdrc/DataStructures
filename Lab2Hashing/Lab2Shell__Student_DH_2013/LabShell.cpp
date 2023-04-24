
// LabShell.cpp : Defines the entry point for the console application.
//

// PLEASE PUT YOUR NAME HERE
//Derek D'Arcy
// 3/3/23
// Revised Feb 2018

#include "stdafx.h"
using namespace std;
#include <math.h>
#include <time.h>
#include <direct.h>

#include <fstream>
#include <iostream>
void genData(int *, int);
int radixSort(int *, int);

// please do not make permanent changes to this code. 

// written by DJF for students for lab 2 Updated from previous version on 10 17/6/07

void genData(int *dta, int n) 
{// generate numerical equivalents of 5 character strings (examples, "ABCDE" ) 
	
	for(int i=0; i < n; i++)
	{
		int sum = 0;		
		for(int j = 0; j < 5; j++) 
			sum = sum + rand()%26 * (int)pow(26., j); 
		dta[i] = sum;
	}
}

// ***********************
bool isPrime(int x) // you write this function 
{ 
	if (x == 0 || x == 1) {
		return false;
	}

	for (int i = 2; i <= x / 2; ++i) {
		if (x % i == 0) {
			return false;
		}
	}

	return true;
}

int ComputeNearestPrime(int x) 
{  // return the nearest prime number larger than 2 * x + 1
	// don't call this with an even number or if you do, then check the argument and if it's even, add 1 to it.
	if (x <= 1) {
		return 2;
	}

	int prime = x;
	bool found = false;

	while (!found) {
		prime++;
		if (isPrime(prime)) {
			return prime;
		}
	}
	
	// don't return a zero
}
// *************************


void Hash(int *dta, int n, int &counter, int *&HashTable, int &TableSize, int swch)
{
	
	// It is important that you use the arguments as follows since the values get returned to the main program.

	// dta is the numerical data to hash
	// n is the amount of data in dta
	// counterinear is the variable you use for counting probes and stores
	// HashTable is the variable you use as the hash table
	// TableSize is the variable you use for the TableSize
	// swch is either 0 or 1, depending on whether you are doing linear or quadratic probing
	// The shell calls this function twice for every data set. The first time, swch will be zero (linear probing)
	// the second time it will be 1 for quadratic probing. Write your code to handle this.
	
	// compute TableSize (prime number > 2 * n)

	TableSize = ComputeNearestPrime(2*n + 1);  // you write this function - computes nearest prime closest but greater than 2 * n

	try
	{
		HashTable = new int [TableSize];
		if(HashTable == NULL)throw "allocation error";
	}
	catch (...)
	{
			cout << "Table allocation error - out of memory" << endl;
	}
	
	for(int i = 0; i < TableSize; i++)HashTable[i] = -1; // initialize
	counter = 0;
	
	int R;
	if (TableSize / 3 <= 1)R = 1; 
	else R = ComputeNearestPrime(TableSize/3);  // for use in double hashing (this is the for the second hash h(x) = (x%Ts + i * (R - x%R))%Ts
	
	//	you write the code that does the hashing
	// ***********************
	 // YOUR CODE GOES HERE
	
	// ************************	
	switch (swch) {
	case 0:
		for (int i = 0; i < n; i++) {
			int m = 0;
			while (HashTable[((dta[i] % TableSize) + m) % TableSize] != -1) {
				m++; 
				counter++;
			}
			HashTable[((dta[i] % TableSize) + m) % TableSize] = dta[i];
			counter++;
		}
		break;
	case 1:
		for (int i = 0; i < n; i++) {
			int m = 0;
			while (HashTable[((dta[i] % TableSize) + (m*m)) % TableSize] != -1) {
				m++;
				counter++;
			}
			HashTable[((dta[i] % TableSize) + (m * m)) % TableSize] = dta[i];
			counter++;
		}
		break;
	case 2:
		for (int i = 0; i < n; i++) {
			int m = 0;
			while (HashTable[((dta[i] % TableSize) + (m*(R - (dta[i] % R)))) % TableSize] != -1) {
				m++;
				counter++;
			}
			HashTable[((dta[i] % TableSize) + (m * (R - (dta[i] % R)))) % TableSize] = dta[i];
			counter++;
		}
		break;
	}

	return;
}

// please do not make permanent changes to this code. 

// Main program to run the hash function

// This code produces a csv (excel) spread sheet for graphing.
// It also produces a graphng file for SDIAPP.exe if you dont want to use Excel
// Debug files containing the hash tables are also produced. These can be disabled.

#define limit 1000   // increase this if you get zeroes in the timing data

int _tmain(int argc, _TCHAR* argv[])
{
	int *data;// pointer to where data will be stored
	int N = 2;// initial size of the SSN data set.
	int count_linear = 0; // return argument holding value of linear probe count
	int count_quadratic = 0;// return argument holding value of quadratic probe count
	int count_double_hashing = 0;// return argument holding value of double hashing probe count
	
	int tablesize = 0;
	int *hashtable_l = NULL; // holds hash table created by the Hash function (for debug printout ) for linear probing
	int *hashtable_q = NULL; // holds hash table created by the Hash function (for debug printout ) for quadratic probing
	int *hashtable_d = NULL; // holds hash table created by the Hash function (for debug printout ) for double hashing
	int NValues[15]; // holds values of N for creating a data file that can be read by SDIAPP.exe
	int LC[15]; // holds values of linear probe count for creating a data file that can be read by DSWB
	int QC[15]; // holds values of quadratic probe for creating a data file that can be read by DSWB
	int DC[15]; // holds values of double hashing for creating a data file that can be read by DSWB
	double D[16]; // holds times
	double E[16]; // holds times
	double F[16]; // holds times

	_mkdir("data"); // already there, it won't do anything
	
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
				if(data == NULL)throw "allocation failed";  // did we get the memory we requested?
			}
			catch (...)
			{
				cout << "allocation failed";
				exit(0);
			}
			genData(data, N);// generate the numerical equivalents to character strings
			
			int count = 0;
			clock_t start_clock = clock(); // read the clock
			for(int j = 0; j < limit; j++)
			{
				count++;
				Hash(data, N, count_linear, hashtable_l, tablesize, 0); // sort the data and count the operations (linear probing)
				double t = (double)( clock() - start_clock) / CLOCKS_PER_SEC;
				if(t > 0)break;
				if(j < limit-1)delete [] hashtable_l;
			}
			D[i] = (double)( clock() - start_clock) / CLOCKS_PER_SEC;
			D[i] = D[i] / (double)count;


			count = 0;
			start_clock = clock(); // read the clock
			for(int j = 0; j < limit; j++)
			{
				count++;
				Hash(data, N, count_quadratic, hashtable_q, tablesize, 1); // sort the data and count the operations (quadratic probing)
				double t = (double)( clock() - start_clock) / CLOCKS_PER_SEC;
				if(t > 0)break;
				if(j < limit-1)delete [] hashtable_q;
			}
			E[i] = (double)( clock() - start_clock) / CLOCKS_PER_SEC;
			E[i] = E[i] / (double)count;


			count = 0;
			start_clock = clock(); // read the clock
			for(int j = 0; j < limit; j++)
			{
				count++;
				Hash(data, N, count_double_hashing, hashtable_d, tablesize, 2); // sort the data and count the operations (quadratic probing)
				double t = (double)( clock() - start_clock) / CLOCKS_PER_SEC;
				if(t > 0)break;
				if(j < limit-1)delete [] hashtable_d;
			}
			F[i] = (double)( clock() - start_clock) / CLOCKS_PER_SEC;
			F[i] = F[i] / (double)count;
		
			NValues[i] = N;
			LC[i] = count_linear;
			QC[i] = count_quadratic;
			DC[i] = count_double_hashing;
			f << N << "," << count_linear << "," << count_quadratic << "," << count_double_hashing << "," << tablesize << endl;// write the data to the excel file for later graphing
			cout << N << "," << count_linear << "," << count_quadratic << ","  << count_double_hashing << "," << tablesize << endl;// write the data to the excel file for later graphing

#define debug_hash			// comment this line out if you don't want debug files to be generated
#ifdef debug_hash		
			//  *************  (START) for debugging your hash function  ***********************
			//  write sorted data into a file so you can see if your hash is working
			char *s = new char[260];
			sprintf_s(s, 260, "Data//Hash_LinearProbing_%i.txt", N);
			f1.open(s, ios::out);
			if(f1.is_open())
			{
				for(int k = 0; k < tablesize; k++)f1 << hashtable_l[k] << "\n";
				f1.close();
			}
			sprintf_s(s, 260, "Data//Hash_QuadraticProbing_%i.txt", N);
			f1.open(s, ios::out);
			if(f1.is_open())
			{
				for(int k = 0; k < tablesize; k++)f1 << hashtable_q[k] << "\n";
				f1.close();
			}
			sprintf_s(s, 260, "Data//Hash_DoubleHashing_%i.txt", N);
			f1.open(s, ios::out);
			if(f1.is_open())
			{
				for(int k = 0; k < tablesize; k++)f1 << hashtable_d[k] << "\n";
				f1.close();
			}
			delete [] s;
			//  *************  (END) for debugging your hash function  ***********************
#endif

			if(hashtable_l != NULL)delete [] hashtable_l;
			if(hashtable_q != NULL)delete [] hashtable_q;
			if(hashtable_d != NULL)delete [] hashtable_d;
			hashtable_l = NULL; // whenever I delete an array, I set it to NULL - this avoids trouble
			hashtable_q = NULL;
			hashtable_d = NULL;
			N = 2 * N;// double the data size for the next pass
			delete [] data;// free the data array because it will be reallocated next time
		}

// create file for SDIAPP.exe in case you would rather use this than excel

			fstream fpout;	
			fpout.open("edit1.txt", ios::out);
			if(fpout.is_open())
			{
				fpout << 6 << " " << 15 << endl; // number of curves (nc) and number of points/curve (np)
				fpout << "Graph of hashing" << endl; // graph title
				fpout << "Linear|Quadratic|Double|Linear timed|Quadratic timed|Double timed" << endl; // curve labels
				fpout << "Sample Size(N)" << endl; // Horizontal axis title
				fpout << "Operations" << endl;  // Vertical axis title
				fpout << "01234560000" << endl;
				fpout << "01234560000" << endl;
				fpout << "loglog" << endl; // can be loglog, loglinear, linearlog, linearlinear (upper of lower case)
				for(int k = 0; k < 15; k++)	fpout << NValues[k] << " ";
				fpout << endl;
				for(int k = 0; k < 15; k++)	fpout << LC[k] << " ";
				fpout << endl;
				for(int k = 0; k < 15; k++)	fpout << QC[k] << " ";
				fpout << endl;
				for(int k = 0; k < 15; k++)	fpout << DC[k] << " ";
				fpout << endl;
				for(int k = 0; k < 15; k++)	fpout << D[k] << " ";
				fpout << endl;
				for(int k = 0; k < 15; k++)	fpout << E[k] << " ";
				fpout << endl;
				for(int k = 0; k < 15; k++)	fpout << F[k] << " ";
				fpout << endl;
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

