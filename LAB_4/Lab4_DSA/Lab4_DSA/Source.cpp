#include<iostream>
#define max 100
using namespace std;


class Node {
public:
	int data;
	Node* next;
	Node() {
		this->next = NULL;
	}
	Node(int data) {
		this->data = data;
		this->next = NULL;
	}

};

class Stack {
private:
	Node * pHead;
	int size = max;
	int count;
public:
	void Create()
	{
		pHead = NULL;
		count = 0;
	}
	void Push(int value)
	{
		if (count < size)
		{
			Node* s = new Node(value);
			if (pHead == NULL)
				pHead = s;
			else
			{
				s->next = pHead;
				pHead = s;
			}
			count++;
		}
		else
		{
			cout << "Stack full" << endl;
			return;
		}
		
	}
	int Pop() {
		if (pHead == NULL)
		{
			cout << "Empty Stack" << endl;
			return -1;
		}
		else
		{
			int x = pHead->data;
			Node*p = pHead;
			pHead = pHead->next;
			delete p;
			return x;
		}
	}
	int Top()
	{
		if (pHead == NULL)
			return -1;
		else
			return pHead->data;
	}
	bool isEmpty()
	{
		return (count == 0);
	}
	bool isFull()
	{
		return (count == size);
	}
	void Clear()
	{
		Node*p = new Node();
		while (pHead != NULL)
		{
			p = pHead;
			pHead = pHead->next;
			delete p;
		}
	}
	int Size() {
		return count;
	}
};

class Queue {
private:
	Node * pHead;
	int size = max;
	int count;
public:
	void Create() {
		pHead = NULL;
		count = 0;
	}
	void EnQueue(int data)
	{
		if (count < size)
		{
			Node* q = new Node(data);
			if (pHead == NULL)
				pHead = q;
			else
			{
				Node* pTemp = pHead;
				while (pTemp->next != NULL)
					pTemp = pTemp->next;
				pTemp->next = q;
			}
		}
		else
			return;
	}
	int DeQueue() {
		Node*p = new Node();
		if (pHead == NULL)
			return -1;
		else
		{
			int x = pHead->data;
			p = pHead;
			pHead = pHead->next;
			delete p;
			return x;
		}
	}
	int QueueFront()
	{
		if (pHead == NULL)
			return -1;
		else
			return pHead->data;
	}
	int QueueFrontAndChangepHead()
	{
		if (pHead == NULL)
			return -1;
		else
		{
			int x = pHead->data;
			pHead = pHead->next;
			return x;
		}
			
	}
	int QueueRear()
	{
		if (pHead == NULL)
			return -1;
		else
		{
			Node* pTemp = pHead;
			while (pTemp->next != NULL)
				pTemp = pTemp->next;
			return pTemp->data;
		}
	}
	bool isEmpty()
	{
		return (count == 0);
	}
	void Clear()
	{
		Node *p = new Node();
		while (pHead != NULL)
		{
			p = pHead;
			pHead = pHead->next;
			delete p;
		}
	}
	int Size()
	{
		return count;
	}
};

Queue stackToQueue(Stack &s)
{
	Queue q;
	q.Create();
	while (!s.isEmpty())
	{
		int x = s.Pop();
		q.EnQueue(x);
	}
	return q;
}

Stack queueToStack(Queue q)
{
	Stack s; s.Create();
	Stack sTemp; sTemp.Create();
	Queue temp; temp.Create();
	for (int i = 0; i < q.Size(); i++)
	{
		int x = q.QueueFrontAndChangepHead();
		temp.EnQueue(x);
	}
	while (!temp.isEmpty())
	{
		int x=temp.DeQueue();
		sTemp.Push(x);
	}
	while (!s.isEmpty())
	{
		int x = sTemp.Pop();
		s.Push(x);
	}
	return s;
}