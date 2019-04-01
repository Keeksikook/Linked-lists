/*1  Write a function which, given a pointer to the head of the list and an integer,
inserts the integer into the list, keeping it in sorted order (ascending).*/

#include <iostream>
#include <cstdlib>
using namespace std;

struct Node {
	int data;
	Node * next;
};
// function prototypes
Node * createNode(int n);
Node * insertAtHead(Node * top, int n);
int size(Node * top);
void printList(Node * top);
int sumList(Node * top);
bool isSorted(Node *top);
Node* insertInOrder(Node * top, int key);
Node* reverse(Node* top);
Node* sort(Node* top);
Node& itemAt(Node* top, unsigned n);
bool inRange(int n, int min, int max);
void reverseConnection(Node* a, Node* b);
Node* insertAt(Node* top, unsigned index, int data); //This could be void, but programmers return items they create so they can do "Node* ptr = insertAt(.., .., ..)" and they would get 1 node, and 1 ptr to it


int main() {

	int num;

	//int nodeSize;  /* Make things once you need them, you will get a warning otherwise */                //these i just made in case i wanted to sort the  list and needed its size or whatever
	Node *myList = nullptr;
	cout << "Enter numbers for a linked list.\nEnter -1 to terminate\n";
	while (cin >> num && num != -1)
		myList = insertInOrder(myList, num);
	cout << "List = ";
	printList(myList);
	cout << ", n = ";
	cout << size(myList) << ", sum = " << sumList(myList);
	cout << ((isSorted(myList)) ? "\nThis list is sorted\n" : "\nThis list is not sorted\n");
	cout << "Sorted list = ";
	printList(sort(myList));
	cout << ", n = ";
	cout << size(myList) << ", sum = " << sumList(myList);
	//cout << "\nYour reversed list = "; /*reverse() IS BROKEN*/
	//printList(reverse(myList));
	//cout << ", n = ";
	//cout << size(myList) << ", sum = " << sumList(myList);
	cout << "\nPlease enter an index to any member of the reversed list: \n";
	cin >> num;
	if (inRange(num, 0, size(myList) - 1))
		cout << "You have accessed <" << itemAt(myList, num).data << ">.\n";
	else
		cout << "Error: <index-out-bounds>\n";
	cout << "<<Emplacing item <" << num << "> at index <" << num << ">>\n";
	cout << "New array: ";
	insertAt(myList, num, num);
	printList(myList);
	cout << "\n";
	system("PAUSE");
}


Node * createNode(int n) {
	Node * newNode;

	newNode = (Node *)malloc(sizeof(Node));      //my lecturer insists on this shit
	newNode->data = n;
	newNode->next = NULL;
	return newNode;
}

void printList(Node* top)
{
	if (top == NULL)
	{
		cout << "[<empty-list>]";
		return;
	}
	Node *temp = top;
	cout << "[ ";
	while (temp != NULL)
	{
		cout << temp->data << " ";
		temp = temp->next;
	}
	cout << "]";
}

Node * insertAtHead(Node * top, int n) {
	Node * newNode;

	newNode = createNode(n);
	newNode->next = top; // this works even if the list isempty (i.e., top = NULL)
	top = newNode;
	return top; // return pointer to new head of list
}

int size(Node * top) {
	Node * curr;
	int numNodes = 0;

	curr = top;
	while (curr != NULL) {
		numNodes = numNodes + 1;
		curr = curr->next;
	}
	return numNodes;
}


int sumList(Node * top) {
	Node * curr = top; // again, on one line...
	int count = 0;
	if (top == NULL) {
		cout << "Error: [<empty-list>]";
		return 0;
	}
	while (curr != NULL) {
		// cout << curr -> data << "\t";
		count = count + curr->data; // or count += curr->data; btw, on your line the brackets are not needed
		curr = curr->next;
	}
	return count;
}

bool isSorted(Node *top) {
	if (top == NULL) // This is good
		return 0;
	for (Node *t = top; t->next != NULL; t = t->next)
	{
		if (t->data > t->next->data)
			return false; //if at least one is not sorted, return false...
	}
	return true; // ...otherwise true
}

// Write a function which, given a pointer to the head of the list and an integer, 
//inserts the integer into the list, keeping it in sorted order (ascending).*/

Node* insertInOrder(Node * top, int num) // keep the var names the same
{
	Node* ptr = top;
	Node* newNode = createNode(num);
	if (ptr)
	{
		for (int i = 0; i < size(top) - 1; i++)
			ptr = ptr->next;
		ptr->next = newNode;

		return top;
	}
	else
		return insertAtHead(top, num);
}

Node* reverse(Node* head)
{
	if (!head || !head->next)
		return head;
	Node* current = head->next, *storePtr = nullptr, *previous = head;
	previous->next = nullptr;
	while (current)
	{
		storePtr = current->next;
		current->next = previous;
		previous = current;
		current = storePtr;
	}
	return previous;
}

Node* sort(Node * top)
{
	while (!isSorted(top))
	{		
		for (Node* ptr = top; ptr != NULL; ptr = ptr->next)
			if (ptr->next != NULL)
				if (ptr->data > ptr->next->data)
					swap(ptr->data, ptr->next->data);
	}
	return top;
}

Node& itemAt(Node* top, unsigned n)
{
	Node* ptr = top;
	for (int i = 0; i < n; i++)
		ptr = ptr->next;    //Move the pointer to the right location
	return *ptr;			// Return dereferenced pointer as reference, to allow modification
}

bool inRange(int n, int min, int max)
{
	return (n >= min && n <= max); //Inclusive
}

void reverseConnection(Node * a, Node * b)
{
	Node* aa = a;
	a->next = b->next;
	b->next = aa;
}

Node* insertAt(Node * top, unsigned index, int data)
{
	if (index == 0)
	{
		Node* newNode = createNode(data); //Why does this function only work when used with '=': myList = insertAt(<gtrthanmax>);
		newNode->next = top;
		return top;
	}

	Node* ptr = top;
	Node* prev = top;
	Node* newNode = createNode(data);
	if (!inRange(index, 0, size(top) - 1))
	{
		for (int i = 0; i < size(top) - 1; i++)
		{
			ptr = ptr->next; // Move the ptr to the right place
		}
		newNode->next = nullptr;
		ptr->next = newNode;
		return top;
	}
	for (int i = 0; i < index; i++)
	{
		if (i == index - 1)
			prev = ptr; // Take the previous node, so we can set its .next correct
		ptr = ptr->next; // Move the ptr to the right place
	}
	newNode->next = ptr;
	prev->next = newNode;
	return top;
}
