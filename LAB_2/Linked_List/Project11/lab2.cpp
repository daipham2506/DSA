//#include<iostream>
//#include<fstream>
//#include<string>
//#include<sstream>
//using namespace std;
//
//struct position {
//	double latitude;
//	double longitude;
//	long long int time;
//};
//
//struct Position
//{
//	position data;
//	Position* next = NULL;
//};
//
//void append(Position* &start, Position* new_position)
//{
//	if (start == NULL)
//	{
//		start = new_position;
//		return;
//	}
//	for (Position* p = start; p != NULL; p = p->next)
//	{
//		if (p->next == NULL)
//		{
//			p->next = new_position;
//			p = new_position;
//		}
//	}
//}
//void XoaCuoi(Position* &pHead)
//{
//	Position* k=new Position;  //k la Node nam trươc Node cuoi
//	for (Position *p = pHead; p != NULL; p = p->next)
//	{
//		
//		if (p->next==NULL)
//		{
//			k->next = NULL;
//			delete p;
//			return;
//		}
//		k=p;
//	}
//}
//void xoaDau(Position* &pHead)
//{
//	Position*p = pHead;
//	pHead = pHead->next;
//	delete p;
//}
//
////xoa node nam sau node q
//void xoaSauMotNode(Position* &pHead, Position* q)
//{
//	Position* g = new Position; //node g nam sau q
//	for (Position *p = pHead; p != NULL; p = p->next)
//	{
//		//tìm q
//			if (p->data.latitude == q->data.latitude) // q bây giờ chính là k nè
//			{
//				g = p->next;
//				p->next = g->next;
//				delete g;
//				return;
//			}
//	}
//}
//
//void XoaNodeKhoaBatKy(Position* &pHead, double data)
//{
//	if(pHead->data.latitude == data)
//	{
//		xoaDau(pHead);
//		return;
//	}
//
//	for (Position*p = pHead; p != NULL; p = p->next)
//	{
//		if (p->next == NULL && p->data.latitude == data)
//			XoaCuoi(pHead);
//	}
//
//	Position *q=new Position;
//	 //Nếu Node cần xóa không phải đầu hoặc cuối
//	 //Tìm ra Node nằm trước Node có khóa cần xóa => gọi hàm xóa Node sau cái Node vừa tìm thấy
//	for(Position *g = pHead; g != NULL; g = g ->next)
//	{
//		if(g ->data.latitude == data)
//		{
//			xoaSauMotNode(pHead, q);
//			return;
//		}
//		q = g;
//	}
//	
//}
//
// //Thêm Node p vào đầu danh sách
//void AddHead(Position* &pHead, Position *p)
//{
//	if(pHead == NULL) // Tức là danh sách bị rỗng
//	{
//		pHead = p;
//		return;
//	}
//	else
//	{
//		p ->next = pHead; // p quăng dây để tham gia vào danh sách
//		pHead = p; // p chính thức đã đứng dầu danh sách
//	}
//}
//
// //Thêm Node p vào cuối danh sách
//void AddTail(Position* &pHead, Position *p)
//{
//	if (pHead == NULL) // Tức là danh sách bị rỗng
//	{
//		pHead = p;
//	}
//	else
//	{
//		for (Position* k = pHead; k != NULL; k = k->next)
//		{
//			if (k->next == NULL)
//			{
//				k->next = p;
//				k = p;
//			}
//		}
//	}
//}
//
//
//
//void GiaiPhong(Position *&pHead)
//{
//	Position *p; // Khai báo Node p.
//	while(pHead != NULL)
//	{
//		p = pHead; // Cho p trỏ tới Head
//		pHead = pHead ->next; // Head trốn sang thằng bên cạnh
//		delete p; // giải phóng p (cũng chính là giải phóng Head ban đầu)
//	}
//}
//
//
//Position* readFromFile(string filename)
//{
//	fstream file;
//	file.open(filename);
//	if (!file.is_open())
//	{
//		cout << "Loi doc file!" << endl;
//		return NULL;
//	}
//	Position* start = NULL;
//	while (!file.eof())
//	{
//		string strLat,strLong,strTime;
//		Position* new_position = new Position;
//		new_position->next = NULL;
//		getline(file, strLat, ',');
//		if (strLat== "") break;
//		stringstream(strLat) >> new_position->data.latitude;
//		getline(file, strLong, ',');
//		stringstream(strLong) >> new_position->data.longitude;
//		getline(file, strTime , '\n');
//		stringstream(strTime) >> new_position->data.time;
//		append(start, new_position);
//	}
//	file.close();
//	return start;
//}
//
//void inKetQua(Position* pHead)
//{
//	for (Position* p = pHead; p != NULL; p = p->next)
//	{
//		cout << "Latitude: " << p->data.latitude << endl;
//		cout << "Longitude: " << p->data.longitude << endl;
//		cout << "point Time: " << p->data.time << endl << endl;
//	}
//}
//void hoanDoi(Position*&p, Position*&q)
//{
//	Position* temp = new Position;
//	temp = p;
//	p = q;
//	q = temp;	
//}
//void Sort(Position *&pHead)
//{
//	if (pHead == NULL || pHead->next == NULL) return;
//	for (Position*p = pHead; p != NULL; p = p->next)
//	{
//		for (Position* k = p->next; k != NULL; k = k->next)
//		{
//			if (p->data.time > k->data.time)
//			{
//				hoanDoi(p, k);
//			}
//		}
//	}
//}
//
//double lengthTwoPosition(Position* a, Position*b)
//{
//	double length = pow((a->data.latitude - b->data.latitude), 2) + pow((a->data.longitude - b->data.longitude), 2);
//	length= sqrt(length);
//	return pow(10, 5)*length;
//}
//
//double repetitionLength(Position* pHead)
//{
//	if (pHead == NULL) return -1;
//	if (pHead->next == NULL) return 0;
//	double sum = 0;
//	for (Position* p = pHead; p->next != NULL; p = p->next)
//	{
//		sum += lengthTwoPosition(p, p->next);
//	}
//	return sum;
//}
//
//double resursionLength(Position* pHead)
//{
//	if (pHead == NULL) return -1;
//	if (pHead->next == NULL) return 0;
//	double sum = 0;
//	Position*p = pHead;
//	if (p->next != NULL)
//	{
//		return lengthTwoPosition(p, p->next) + resursionLength(p->next);
//	}
//}
//
//bool checkMeeting(Position* start1, Position* start2)
//{
//	if (lengthTwoPosition(start1, start2) <= 50 && (start2->data.time - start1->data.time) <= 5000)
//		return true;
//	else return false;
//}
//int main()
//{
//	Position* pHead = readFromFile("sample.csv");
//	//inKetQua(pHead);
//	//xoaDau(pHead);
//	//XoaCuoi(pHead);
//	cout << "\n\t\tKET QUA SAU KHI SORT" << endl;
//	Sort(pHead);
//	inKetQua(pHead);
//	double length = repetitionLength(pHead);
//	//double length = resursionLength(pHead);
//	cout << "sum of length : "<<length <<"(m)"<< endl;
//	for (Position* p = pHead; p->next != NULL; p = p->next)
//	{
//		bool check = checkMeeting(p,p->next);
//		if (check == true)
//		cout << "2 xe da gap nhau" << endl;
//		else
//		cout << "2 xe chua gap nhau" << endl;
//	}
//	system("pause");
//}
