// LL.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string.h>
#include <iostream>

using namespace std;


class node
{
public:
	char data;
	node* next;
	node* prev;
	node();
};

node::node()
{

}

int _tmain(int argc, _TCHAR* argv[])
{
	char s[] = "abcdefghijklmnopqrstuvwxyz";

	node* head;
	node* tail;
	node* temp;
	node* prior;
	node* current;

	head = new node;          // create the head of the linked list
	head->data = s[0];
	head->next = NULL;
	head->prev = NULL;
	temp = head;   // get ready for the loop - save the head in temp - you are going to change temp in the loop

	for (size_t i = 1; i < strlen(s); i++)      // create the rest of the linked list
	{
		current = new node;    // make a new node

		current->data = s[i];  // set it's data member
		current->next = NULL;
		temp->next = current;  // point to the new node
		current->prev = temp;
		temp = current;   // make temp point to current node (for next time through)
	
	}

	tail = current;

	node* ptr = head;    // set a ptr to head, then you are going to "increment" the pointer

	while (ptr != NULL)
	{
		cout << ptr->data; // print out the linked list
		ptr = ptr->next;   // increment the linked list
	}
	cout << endl;


	ptr = tail;
	while (ptr != NULL)
	{
		cout << ptr->data; // print out the linked list
		ptr = ptr->prev;   // increment the linked list
	}

	cout << endl;
	system("pause");
	return 0;
}

