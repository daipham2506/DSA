

#include "stdafx.h"
#include <string>
#include <iostream>

using namespace std;

//function 1
bool isLeapYear(int n) {
	return (n % 400 == 0) || (n % 4 == 0 && n % 100 != 0);
}

//function 2.1(static)
void multiMat(double** mat1, double** mat2, double** matKq, const int a, const int b, const int c) {
	for (int i = 0; i < a; i++) {
		for (int j = 0; j < c; j++) {
			matKq[i][j] = 0;
			for (int k = 0; k < b; k++) {
				matKq[i][j] += mat1[i][k] * mat2[k][j];
			}
		}
	}
}

//function 2.2(dynamic)
double** multiMat(double** mat1, double** mat2, int a, int b, int c) {
	double** matKq = new double*[a];
	for (int i = 0; i < a; i++) {
		matKq[i] = new double[c];
	}
	for (int i = 0; i < a; i++) {
		for (int j = 0; j < c; j++) {
			matKq[i][j] = 0;
			for (int k = 0; k < b; k++) {
				matKq[i][j] += mat1[i][k] * mat2[k][j];
			}
		}
	}
	return matKq;
}

//function 3.1
long intPower1(int n, int exp) {
	long s = 1;
	for (int i = 0; i < exp; i++) {
		s = s * n;
	}
	return s;
}

//function 3.2
long intPower2(int n, int exp) {
	if (exp == 0) return 1;
	return n * intPower2(n, exp - 1);
}

//function 4a
int stringsCompare(string a, string b) {
	int n = (a.length() < b.length()) ? a.length() : b.length();
	for (int i = 0; i < n; i++) {
		if (a[i] != b[i]) return abs((int)a[i] - (int)b[i]);
	}
	if (a.length() == b.length()) return 0;
	else return -1;
}

//function 4b
char* find(string &str, const char ch) {
	for (unsigned int i = 0; i < str.length(); i++) {
		if (str[i] == ch) return &str[i];
	}
	return 0;
}

//function 4c
char* findString(string &s1, string &s2) {
	if (s2.find(s1) != string::npos) {
		return &s2[s2.find(s1)];
	}
	else return 0;
}

//function 5
class candidate {
private:
	double math, physics, chemistry;
public:
	const int id;
	const char* name;
	candidate(const int i, const char* ch, double a, double b, double c) :id(i), math(a), physics(b), chemistry(c) {
		name = ch;
	}
	~candidate() {}
	double totalGrade() {
		return math + physics  + chemistry;
	}
};

int main()
{
	return 0;
}

