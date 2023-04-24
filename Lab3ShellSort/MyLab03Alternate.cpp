#include "stdafx.h"
using namespace std;
#include <stdlib.h>
#include <math.h>
#include <fstream>

void quicksort(int [], int , int, int& );
void swap(int &, int &);
int insertionSort(int [], int, int);

// *** FOR ONLINE DATA STRUCTURES COURSE **** 11/19/11

// *******  STUDENTS -- GO TO THE mymain FUNCTION AND READ THE COMMENTS. DO NOT MODIFY ANY CODE OTHER THAN THE TWO FUNCTIONS YOU HAVE TO WRITE  *******


int insertion_style_sort(int data[], int len, int a[], int limit)
{
	// general insertion sort which uses increments you supply
	// can be used to perform Sedgewick, Hibbard, 531 and Shell sorts (or with any increments)

	// data[]	this is the data to sort
	// len		number of elements in data to sort
	// a[]		increments to use for sorting (highest first, last increment is always 1).
	// limit	number of increments


	int counter=0, gap, i, j, temp;

	for(int k = limit; k >= 0; k--)
   {
			gap = a[k];
			for( i = gap; i < len; i++)
			{
				temp = data[i];
				counter++;
				for( j = i; j >=gap && temp < data[j - gap]; j-=gap)
				{
					data[j] = data[ j - gap];
					counter++;
				}
				data[j] = temp;
			}
			if(gap == 1)break;
		}
	return counter;   // return the number of operations performed
}


int insertionSort(int data[], int start, int stop)
{
 int count;
 int a[2];

	a[0] = 1;// create the increments (which are just 1)
	a[1] = 1;
	count = insertion_style_sort(data, stop - start, a, 1);
	return count;
}

int insertion_style_sort_descending(int data[], int len, int a[], int limit)
{
	// general insertion sort which uses increments you supply
	// can be used to perform Sedgewick, Hibbard, 531 and Shell sorts (or with any increments)
	// data[]	this is the data to sort
	// len		number of elements in data to sort
	// a[]		increments to use for sorting (highest first, last increment is always 1).
	// limit	number of increments
	int counter = 0, gap, i, j, temp;
	for (int k = limit; k >= 0; k--)
	{
		gap = a[k];
		for (i = gap; i < len; i++)
		{
			temp = data[i];
			counter++;
			for (j = i; j >= gap && temp > data[j - gap]; j -= gap)
			{
				data[j] = data[j - gap];
				counter++;
			}
			data[j] = temp;
		}
		if (gap == 1)break;
	}
	return counter;   // return the number of operations performed
}

int insertionSortDescending(int data[], int start, int stop)
{
	int count;
	int a[2];
	a[0] = 1;// create the increments (which are just 1)
	a[1] = 1;
	count = insertion_style_sort_descending(data, stop - start, a, 1);
	return count;
}

int shellsort_Shellincrements(int data[], int len)
{// this code is taken from the Weiss text

	int j=0, limit, temp, counter=0;

	int *a = new int[len/2];

	limit = j = log10((double)len)/log10(2.);

     // create Shell's increments
	for(int gap = len/2; gap > 0; gap /= 2)
	{
		a[j--] = gap;
	}

	counter = insertion_style_sort(data, len, a, limit);
	return counter;
}

int shellsort_531increments(int data[], int len)
{// this code is taken from the Weiss text and demonstrates the example on p 257 using this set of increments

	int a[]={1, 1, 3, 5}; // this was wrong in the code on the Bb
	int counter = insertion_style_sort(data, len, a, 3);
	return counter;
}


int shellsort_Hibbardsincrements(int data[], int len)
{// this code is taken from the Weiss text and demonstrates the example on p 257 using this set of increments
        int *a;
		double x = len;
		x = log10(x)/log10(2.);
		int ix = (int)x;
            // create the increments for Hibbard
                a = new int[ix+1];
		for(int k = ix; k >= 1; k--)
	                 a[k] = (int)pow(2., (double)k) - 1;
                a[0]= 1;
		int counter = insertion_style_sort(data, len, a, ix);
                delete [] a;
                return counter;
}

int shellsort_Sedgewicksincrements(int data[], int len)
{// this code is taken from the Weiss text and demonstrates the example on p 257 using this set of increments
 // I added the code to create the increments
	int i, j, temp, gap, counter=1;// don't return zero
	double x, y;

	i = 0;

//Compute the increment sequence for this size sample (len)
	while(true)  // solve for i, 9 * 4^i - 9 * 2^i + 1 = len
	{
		if( (j=(9*(int)pow(4., i) - 9*(int)pow(2., i) + 1)) > len)break;
		i++;
	}

	x = i;

	i = 0;
	while( true) // solve for i, 4^i - 3 * 2^i + 1 = len
	{

		if( (j=((int)pow(4., i) - 3*(int)pow(2., i) + 1)) > len)break;
		i++;
	}

	y = i;

	if(y > x)x = y; // take the larger of the two
	int ix = (int)x;

        int *a = new int[2*ix+2];// create an array to hold the increments
        for(i = 0; i < ix; i++)
        {   // create the increments
                a[2*i] = (int)(9*(pow(4., (double)i) - pow(2., (double)i)) + 1);
                a[2*i+1] = (int)(pow(4., (double)i) - 3.*pow(2., (double)i) + 1);
                if(a[2*i+1] < 1)a[2*i+1] = 1;
        }

	insertionSortDescending(a, 0, 2 * ix); // sort the increments in descending order so you can remove duplicate 1s 
	int limit = 2 * ix;
	int lim = limit;
	for (int j = limit; j >= 0; j--)
	{
		if (a[j-1] == 1)lim--; // decrement lenth of a if it's a 1
		else break; // since sorted, if you didn't find a 1, you are not going to
	}
	lim++; // keep the last 1
	insertionSort(a, 0, lim);// sort the increments in ascending order
	
// perform the insertion style sort on the data with these increments
	counter = insertion_style_sort(data, len, a, lim-1); // this starts at the last element in a and goes down
	return counter;
}

// ***************** EXAMPLE FUNCTION  - use this to see how to write the two functions below, but use your own increment strategy ***********************************************************
int shellsort_Rootsincrements(int data[], int len)
{  // made up by DJF to show how to create and test your own algorithm
        // for this strategy, use 5 increments consisting of the following roots of len, 1/2, 1/3, 1/4, 1/5

        int *a;
		int ix = 5;
        int j=2;// start at the square root (it is the largest increment)
		a = new int[ix+1];
        a[0] = 1; // last increment must always be 1 else you won't get a complete sort
		// increments must be in descending order (largest to smallest, with 1 being the last increment)
		for(int k = ix; k >= 1; k--)
	        a[k] = (int)pow((double)len, (double)1/(double)(j++));

		int counter = insertion_style_sort(data, len, a, ix);  // leave this code in place
        delete [] a;
        return counter;
}

// ****************************************************************************

// ***************** YOUR FUNCTION  - YOU WRITE THIS (this is a copy of the shellsort_Hibbardsincrements that you can modify ***********************************************************
int shellsort_yyyincrements(int data[], int len)
{  
	int* a;
	double x = len;
	x = log10(x) / log10(2.);
	int ix = (int)x;
	// create the increments for Hibbard
	a = new int[ix + 1];
	for (int k = ix; k >= 1; k--)
		a[k] = (int)pow(2., (double)k) - 1; // replace this with the algorithm to generate your increment set
	a[0] = 1;
	int counter = insertion_style_sort(data, len, a, ix);
	delete[] a;
	return counter;
}

// ****************************************************************************

// ***************** YOUR FUNCTION  - YOU WRITE THIS (this is a copy of the shellsort_Hibbardsincrements that you can modify ***********************************************************
int shellsort_zzzincrements(int data[], int len)
{  
	int* a;
	double x = len;
	x = log10(x) / log10(2.);
	int ix = (int)x;
	// create the increments for Hibbard
	a = new int[ix + 1];
	for (int k = ix; k >= 1; k--)
		a[k] = (int)pow(2., (double)k) - 1; // replace this with the algorithm to generate your increment set
	a[0] = 1;
	int counter = insertion_style_sort(data, len, a, ix);
	delete[] a;
	return counter;
}

// ****************************************************************************



void mycopy(int source[], int dest[], int n)
{
 for(int i=0; i < n; i++)dest[i] = source[i];
}

void gendata(int array[], int length, int modulus, int base)
{
        for(int i=0; i < length; i++)
                array[i] = rand()%modulus + base;
}

int mymain()  // don't modify this code
{

// **************************************************************
// file format for exporting graphs to DSWB
//Number of curves (int) (blank) Number of points in a curve (must be 15)
//Graph Title  (char string)
//Curve Labels (char string with | delimiter)
//X axis label (char string)
//Y axis label (char string)
// Showcurves (char string)
// Scalecurves (char string)
// Graph style (char string -> loglog, loglinear, linearlog, linearlinear)
// X points (one line, 15 points)
// Y points for curve #1   (one line, 15 points)
// Y points for curve #2
// Y points for curve #3
//....
//....
// Y points for curve 11
//  ****************************************************************

 int *data, *save; // arrays to hold data to be sorted, and also to back it up
 int counts [10] [15]; // results of sorts (counts) saved for graphing

 ofstream fpout;  // file stream for data file to be read by sdiapp.exe
// ofstream fpout1;  // file stream for sorted output to be used while debugging the code

 fpout.open("edit1.txt");// name this file so sdiapp.exe will open without you having to type name
 if(fpout.fail()) // did the file open?
 {
  cout << "Data file (data) did not open";
  system("pause");
  exit(0);
 }
 //   uncomment this code if you want to write output sorted data
 //fpout1.open("output.txt");
 //if(fpout1.fail())
 //{
 // cout << "Data file (output) did not open";
 // system("pause");
 // exit(0);
 //}

 int nc = 8;   // This is the number of curves including your 3.
 int np = 15;  // This stays at 15 to be compatible with the DSWB

 fpout << nc << " " << np << endl; // number of curves (nc) and number of points/curve (np)
 fpout << "Sort Increments" << endl; // graph title
 fpout << "Shell|Hibbard|Sedgewick|Roots|My2|My3|531|Increment|" << endl; // curve labels
 fpout << "Sample Size(N)" << endl; // Horizontal axis title
 fpout << "Operations" << endl;  // Vertical axis title
 fpout << "01234567890" << endl;// you don't need to change this
 fpout << "01234567890" << endl;// you don't need to change this
 fpout << "loglog" << endl; // can be loglog, loglinear, linearlog, linearlinear (upper of lower case)

 int samples[15] = {8, 16, 32, 48, 64, 96, 128, 256, 512, 1024, 2048, 3072, 4096, 8192, 16384};

 for(int i = 0; i < 10; i++) // set the counts arrays to 1 (because your routines are not written yet)
    for(int j=0; j < 15; j++)
        counts[i][j] = 1; // use 1 instead of zero because log plots won't work with a zero

//   generate 15 data points for each curve
 int N;
 for(int i = 0; i < 15; i++)
 {
  N = samples[i];  // get the sample size
  data = new int[N]; // allocate storage
  save = new int[N];
  gendata(data, N, RAND_MAX, 0); // generate the data
  mycopy(data, save, N); // save the dat for restore, else you will be sorting data already sorted

  counts[0][i] = shellsort_Shellincrements(data, N);// call each routine and capture it's count
  mycopy(save, data, N);// restore to the unsorted state for the next routine
  counts[1][i] = shellsort_Hibbardsincrements(data, N);
  mycopy(save, data, N);
  counts[2][i] = shellsort_Sedgewicksincrements(data, N);
  mycopy(save, data, N);

  counts[3][i] = shellsort_Rootsincrements(data, N); // here is an an example, I an using the roots of N
  mycopy(save, data, N);
  counts[4][i] = shellsort_yyyincrements(data, N);  
  mycopy(save, data, N);
  counts[5][i] = shellsort_zzzincrements(data, N);  
  mycopy(save, data, N);

 
  // other reference curves -
  counts[6][i] = shellsort_531increments(data, N);
  mycopy(save, data, N);
  counts[7][i] = insertionSort(data, 0, N-1);
  mycopy(save, data, N);

  delete [] data;
 }

 for(int i = 0; i < 15; i++)
 {    // write independent data on the first line
   fpout << samples[i] << " ";
  }

  fpout << endl;
  for(int i=0; i < nc; i++)
  {
        for(int k = 0; k < 15; k++)
        {
          fpout << counts[i][k] << " ";
        }
        fpout << endl;
  }

 fpout.close();
// fpout1.close(); // uncomment if you use fpout1
 return 0;
}
