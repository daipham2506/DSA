#include<iostream>
#include<string>
#include<fstream>
#include<sstream>
#include<iomanip>
using namespace std;


struct Category {
	string ID;
	string name;
	Category* next = NULL;
};

struct product {
	string ID;
	string name;
	int sellingPrice;
	int importingPrice;
	double quantity;
	Category *C;
	product* next = NULL;
};

void appendCategory(Category *&start, Category* new_position)
{
	if (start == NULL) 
		start = new_position;
	else
	{
		Category * pTemp = start;
		while (pTemp->next != NULL)
			pTemp = pTemp->next;
		pTemp->next = new_position;
	}
}

void appendProduct(product* &start, product* new_position)
{
	if (start == NULL)
		start = new_position;
	else
	{
		product * pTemp = start;
		while (pTemp->next != NULL)
			pTemp = pTemp->next;
		pTemp->next = new_position;
	}
}

int quantityCategory(product *pHead)
{
	int count = 0;
	for (product*p = pHead; p != NULL; p = p->next)
	{
		int i = 0;
		if (p->C == NULL) continue;
		for (product*p1 = pHead; p1 != p; p1 = p1->next)
		{
			if (p1->C == NULL) continue;
			else
			{
				if (p1->C->ID == p->C->ID)
					i++;
			}
		}
		if (i == 0) count++;
	}
	return count;
}
void printCategory(product *pHead)
{
	cout << quantityCategory(pHead) << " categories" << endl;
	for (product*p = pHead; p != NULL; p = p->next)
	{
		int i = 0;
		if (p->C == NULL) continue;
		for (product*p1 = pHead; p1 != p; p1 = p1->next)
		{
			if (p1->C == NULL) continue;
			else
			{
				if (p1->C->ID == p->C->ID)
					i++;
			}	
		}
		if (i == 0)
		{
			cout << "-----------------------" << endl;
			cout << "ID: " << p->C->ID << endl;
			cout << "Name: " << p->C->name << endl;
		}
		
	}
}


bool deleteProducts(product* &pHead, double quantity)
{
	int test = 0;
	if (pHead == NULL) return false;
	//xoa dau
	if (pHead->quantity < quantity)
	{
		product*p = pHead;
		pHead = pHead->next;
		delete p;
	}
	//xoa sau node p;
	for (product* p = pHead; p != NULL; p = p->next)
	{	
		if (p->next!=NULL || p->next->quantity < quantity)
		{
			product*g = new product;
			g = p->next;
			p->next = g->next;
			delete g;
			test++;
		}
	}
	return test;
}

double sellingFromFile(product*&pHead, string filename)
{
	double sumPrice = 0;
	ifstream fin;
	fin.open(filename);
	string ID, strSellingQuantity;
	double sellQuantity;
	while (!fin.eof())
	{
		getline(fin, ID, ',');
		getline(fin, strSellingQuantity, '\n');
		stringstream(strSellingQuantity) >> sellQuantity;
		if (ID == "") break;
		for (product*p = pHead; p != NULL; p = p->next)
		{
			if (p->ID == ID)
			{
				p->quantity -= floor(sellQuantity);		
				sumPrice += floor(sellQuantity)*p->sellingPrice;
			}			
		}
	}
	return sumPrice;
}

Category* enterCategory()
{
	Category* start = NULL;
	int n;
	cout << "Nhap so luong Category can nhap : ";
	cin >> n;
	cin.ignore();
	for (int i = 0; i < n; i++)
	{
		Category* new_position = new Category;
		cout << "Enter ID : ";
		getline(cin, new_position->ID);
		cout << "Enter category name : ";
		getline(cin, new_position->name);
		appendCategory(start, new_position);
	}
	return start;
}
product* enterProduct(Category*Cate)
{
	string id;
	product* start = NULL;
	int n;
	cout << "Nhap so luong san pham can nhap : ";
	cin >> n;
	cin.ignore();
	for (int i = 0; i < n; i++)
	{
		product* new_position = new product;
		cout << "\nEnter ID product : ";
		getline(cin, new_position->ID);
		cout << "Enter product name : ";
		getline(cin, new_position->name);
		cout << "Enter selling price : ";
		cin >> new_position->sellingPrice;
		cout << "Enter importing price : ";
		cin >> new_position->importingPrice;
		cout << "Enter quantity : ";
		cin >> new_position->quantity;
		cout << "\nCategory product :" << endl;
		for (Category*c = Cate; c != NULL; c = c->next)
		{
			cout << "ID : " << c->ID << endl;
			cout << "Name : " << c->name << endl;
			cout << "------------------" << endl;
		}
		cin.ignore();
		cout << "Enter ID Category product :";
		getline(cin, id);
		for (Category*c = Cate; c != NULL; c = c->next)
		{
			if (c->ID==id)
			{
				new_position->C = c;
				break;
			}
			new_position->C = NULL;
		}
		appendProduct(start, new_position);
	}
	return start;
}

void printProduct(product*pHead)
{
	cout << "\n\n\t\t==============PRODUCT==============" << endl;
	cout << setw(2) << "ID" << setw(10) << "Name" << setw(10) << "selling price" << setw(10) << "importing price" << setw(10) << "quantity" << setw(10) << "ID pointer Category" << endl;
	for (product*p = pHead; p != NULL; p = p->next)
	{
		cout << setw(2) << p->ID << setw(10) << p->name << setw(10) << p->sellingPrice << setw(10) << p->importingPrice << setw(10) << p->quantity << setw(10);
		if (p->C == NULL)
			cout << "NULL" << endl;
		else
			cout << p->C->ID;
	}
}

int main()
{
	Category* C=enterCategory();
	system("cls");
	product* P=enterProduct(C);
	system("cls");
	printCategory(P);
	printProduct(P);
	system("pause");
	return 0;

}


