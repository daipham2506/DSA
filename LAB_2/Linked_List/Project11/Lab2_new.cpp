#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
using namespace std;

struct position {
	double latitude;
	double longitude;
	long long int time;
};

struct Position
{
	position data;
	Position* next = NULL;
};

void append(Position* &start, Position* new_position)
{
	if (start == NULL)
	{
		start = new_position;
		return;
	}
	/*Position* temp = start;
	while (temp->next != NULL)
	{
		temp = temp->next;
	}
	temp->next = new_position;*/
	for (Position* p = start; p != NULL; p = p->next)
	{
		if (p->next == NULL)
		{
			p->next = new_position;
			p=new_position;
		}
	}
}

Position* readFromFile(string filename)
{
	fstream file;
	file.open(filename);
	if (!file.is_open())
	{
		cout << "Loi doc file!" << endl;
		return NULL;
	}
	Position* start = NULL;
	while (!file.eof())
	{
		string strLat, strLong, strTime;
		Position* new_position = new Position;
		new_position->next = NULL;
		getline(file, strLat, ',');
		if (strLat == "") break;
		stringstream(strLat) >> new_position->data.latitude;
		getline(file, strLong, ',');
		stringstream(strLong) >> new_position->data.longitude;
		getline(file, strTime, '\n');
		stringstream(strTime) >> new_position->data.time;
		append(start, new_position);
	}
	file.close();
	return start;
}
void xoaCuoi(Position* pHead)
{
	Position*k = new Position;
	for (Position*p = pHead; p != NULL; p = p->next)
	{
		if (p->next == NULL)
		{
			k->next = NULL;
			delete p;
			return;
		}
		k = p;
	}
}
void deleteNth(Position* pHead, int n)
{
	if(n==0)
	{
		Position*p = pHead;
		pHead = pHead->next;
		delete p;
		return ;
	}
	int length = 0;
	for (Position*p = pHead; p != NULL; p = p->next)
	{
		length++;
	}
	if (n > 0 && n<length)
	{
		int i = 0;
		for (Position*p=pHead; p != NULL; p = p->next)
		{
			i++;
			if(i==n)
			{
				Position*g = new Position;
				g = p->next;
				p->next = g->next;
				delete g;
				return ;
			}
		}
	}
}
void inKetQua(Position* pHead)
{
	for (Position* p = pHead; p != NULL; p = p->next)
	{
		cout << "Latitude: " << p->data.latitude << endl;
		cout << "Longitude: " << p->data.longitude << endl;
		cout << "point Time: " << p->data.time << endl << endl;
	}
}
void hoanDoi(Position*&p, Position*&q)
{
	Position* temp = new Position;
	temp = p;
	p = q;
	q = temp;
}
void Sort(Position *&pHead)
{
	if (pHead == NULL || pHead->next == NULL) return;
	for (Position*p = pHead; p != NULL; p = p->next)
	{
		for (Position* k = p->next; k != NULL; k = k->next)
		{
			if (p->data.time > k->data.time)
			{
				hoanDoi(p, k);
			}
		}
	}
}

double lengthTwoPosition(Position* a, Position*b)
{
	double length = pow((a->data.latitude - b->data.latitude), 2) + pow((a->data.longitude - b->data.longitude), 2);
	length = sqrt(length);
	return pow(10, 5)*length;
}

double repetitionLength(Position* pHead)
{
	if (pHead == NULL) return -1;
	if (pHead->next == NULL) return 0;
	double sum = 0;
	for (Position* p = pHead; p->next != NULL; p = p->next)
	{
		sum += lengthTwoPosition(p, p->next);
	}
	return sum;
}

double resursionLength(Position* pHead)
{
	if (pHead == NULL) return -1;
	if (pHead->next == NULL) return 0;
	Position*p = pHead;
	if (p->next != NULL)
	{
		return lengthTwoPosition(p, p->next) + resursionLength(p->next);
	}
}

bool checkMeeting(Position* start1, Position* start2)
{
	for (Position* p = start1; p != NULL; p = p->next)
	{
		for (Position*k = start2; k != NULL; k = k->next)
		{
			if (lengthTwoPosition(p,k) <= 50 && abs((p->data.time - k->data.time) <= 5000))
			return true;
		}
	}
	return false;

}

void giaiPhong(Position* &pHead)
{
	Position* p;
	while (pHead != NULL)
	{
		p = pHead;
		pHead = pHead->next;
		delete p;
	}
}
int main()
{
	Position* pHead = readFromFile("sample.csv");
	//inKetQua(pHead);
	//deleteNth(pHead, 10);
	xoaCuoi(pHead);
	cout << "\n\t\tKET QUA SAU KHI SORT" << endl;
	Sort(pHead);
	inKetQua(pHead);
	double length = repetitionLength(pHead);
	//double length = resursionLength(pHead);
	cout << "sum of length : " << length << "(m)" << endl;
	bool check = checkMeeting(pHead, pHead->next);
	if (check == true) cout << "2 tai xe da gap nhau" << endl;
	else cout << " 2 tai xe khong gap nhau" << endl;
	giaiPhong(pHead);
	system("pause");
}
