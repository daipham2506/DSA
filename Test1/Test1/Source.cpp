#include<iostream>
using namespace std;
#include<string>

//cau 1
struct Bus {
	double longitude;
	double latitude;
	string ID;
	Bus* next = NULL;
};

void themDau(Bus* &pHead, Bus* newBus)
{
	if (pHead == NULL)
	{
		pHead = newBus;
		return;
	}
	newBus->next = pHead;
	pHead = newBus;
}

//cau 2
double khoangCachHaiBus(Bus* xe1, Bus* xe2)
{
	double length = 0;
	length = pow(xe1->latitude - xe2->latitude, 2) + pow(xe1->longitude - xe2->longitude, 2);
	length = sqrt(length);
	return pow(10, 5)*length;
}

double khoangCachTramBus(Bus* xe, double kinhdo, double vido)
{
	double length = 0;
	length = pow(xe->latitude - vido, 2) + pow(xe->longitude - kinhdo, 2);
	length = sqrt(length);
	return pow(10, 5)*length;
}

int soLuongBus(Bus* pHead,double kinhdo,double vido)
{
	int sum = 0;
	for (Bus* p = pHead; p != NULL; p = p->next)
	{
		if (khoangCachTramBus(p,kinhdo,vido) <= 1000)
			sum++;
	}
	return sum;
}

void append(Bus* &start, Bus* new_bus)
{
	if (start == NULL)
	{
		start = new_bus;
		return;
	}
	Bus* temp = start;
	while (temp->next != NULL)
	{
		temp = temp->next;
	}
	temp->next = new_bus;
}

Bus* danhSachBus(Bus* pHead, double kinhdo,double vido)
{
	Bus* newListBus = NULL;
	for (Bus* p = pHead; p != NULL; p = p->next)
	{
		if (khoangCachTramBus(p,kinhdo,vido) <= 1000)
		{
			append(newListBus, p);
		}
			
	}
	return newListBus;
}

// cau 3

void hoanDoi(Bus*&p, Bus*&q)
{
	Bus* temp = new Bus();
	temp->latitude = p->latitude;
	temp->longitude = p->longitude;
	temp->ID = p->ID;
	p->latitude = q->latitude;
	p->longitude = q->longitude;
	p->ID = q->ID;
	q->latitude = temp->latitude;
	q->longitude = temp->longitude;
	q->ID = temp->ID;
	
}

void sapXepTangViDo(Bus *&pHead)
{
	if (pHead == NULL || pHead->next == NULL) return;
	for (Bus*p = pHead; p != NULL; p = p->next)
	{
		for (Bus* k = p->next; k != NULL; k = k->next)
		{
			if (p->latitude > k->latitude)
			{
				hoanDoi(p, k);
			}
		}
	}
}

void sapXepGiamKinhDo(Bus* &pHead)
{
	if (pHead == NULL || pHead->next == NULL) return;
	for (Bus*p = pHead; p != NULL; p = p->next)
	{
		for (Bus* k = p->next; k != NULL; k = k->next)
		{
			if (p->longitude < k->longitude)
			{
				hoanDoi(p, k);
			}
		}
	}
}

// caau 4

double resursionLength(Bus* pHead)
{
	if (pHead == NULL) return -1;
	if (pHead->next == NULL) return 0;
	Bus*p = pHead;
	if (p->next != NULL)
	{
		return khoangCachHaiBus(p, p->next) + resursionLength(p->next);
	}
}


// cau 5
Bus* checkMove(Bus* start1, Bus* start2)
{
	Bus* pHead = NULL;
	for (Bus* p = start1; p != NULL; p = p->next)
	{
		for (Bus*k = start2; k != NULL; k = k->next)
		{
			if (p->ID == k->ID)
			{
				if (khoangCachHaiBus(p, k) <= 10)
					append(pHead, p);
			}
		}
	}
	return pHead;
}



