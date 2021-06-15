#include <iostream>
#include <fstream>
#include <cstdlib>
using namespace std;
#include "CDA.cpp"

void test0(ostream &fp);
void test1(ostream &fp);
void test2(ostream &fp);
void test3(ostream &fp);
void test4(ostream &fp);
void test5(ostream &fp);
void test6(ostream &fp);

void foo(CDA<int> x) {
	for (int i=0; i<x.Length()/2; i++){
		int temp = x[i];
		x[i] = x[x.Length()/2+i];
		x[x.Length()/2+i] = temp;
	}
}

int printWrapper = 0;

int main(int argc, char **argv){
	int testToRun = atoi(argv[1]);
	switch (testToRun){
		case 0:
			test0(cout);
			break;
		case 1:
			test1(cout);
			break;
		case 2:
			test2(cout);
			break;
		case 3:
			test3(cout);
			break;
		case 4:
			test4(cout);
			break;
	}
}

void test0(ostream &fp){
	if(printWrapper) fp << "Running test 0" << endl;
	CDA<int> C(15);
	for (int i=0; i< C.Length();i++) C[i] = i*10;
	for (int i=0; i< C.Length();i++) fp << C[i] << " "; fp << endl;
	// 0 10 20 30 40 50 60 70 80 90 100 110 120 130 140
	C.DelFront();
	// 10 20 30 40 50 60 70 80 90 100 110 120 130 140
	C.DelFront();
	// 20 30 40 50 60 70 80 90 100 110 120 130 140
	for (int i=0; i< C.Length();i++) fp << C[i] << " ";  fp << endl;
	C.DelEnd();
	// 20 30 40 50 60 70 80 90 100 110 120 130
	C.DelEnd();
	// 20 30 40 50 60 70 80 90 100 110 120
	for (int i=0; i< C.Length();i++) fp << C[i] << " ";  fp << endl;
	// 20 30 40 50 60 70 80 90 100 110 120
	C.AddEnd(1001);
	// 20 30 40 50 60 70 80 90 100 110 120 1001
	C.AddEnd(1003);
	// 20 30 40 50 60 70 80 90 100 110 120 1001 1003
	for (int i=0; i< C.Length();i++) fp << C[i] << " ";  fp << endl;
	// 20 30 40 50 60 70 80 90 100 110 120 1001 1003
	C.AddFront(1004);
	// 1004 20 30 40 50 60 70 80 90 100 110 120 1001 1003
	C.AddEnd(1006);
	// 1004 20 30 40 50 60 70 80 90 100 110 120 1001 1003 1006
	for (int i=0; i< C.Length();i++) fp << C[i] << " ";  fp << endl;
	// 1004 20 30 40 50 60 70 80 90 100 110 120 1001 1003 1006
	C.DelEnd(); C.DelEnd();
	// 1004 20 30 40 50 60 70 80 90 100 110 120 1001
	C.AddFront(-105); 
	C.AddFront(-205);
	// -205 -105 1004 20 30 40 50 60 70 80 90 100 110 120 1001
	for (int i=0; i< C.Length();i++) fp << C[i] << " ";  fp << endl;
	fp << "Capacity is " << C.Capacity() << endl;
	// 15
	while(C.Length()){
		C.DelEnd();
	}
	
	C.Clear();
	fp << "Capacity is " << C.Capacity() << endl;
	// 4
	if(printWrapper)fp << "-----------------Finished Test----------------------" << endl;
}

void test1(ostream &fp){
	if(printWrapper) fp << "Running test 1" << endl;
	CDA<int> A;
	int temp = 0;
	for(int i=0; i<20;i++){
		A.AddEnd(i);
		if(A.Capacity() != temp){
			temp = A.Capacity();
			fp << "Capacity is " << temp << " ";
		}
	}
	// 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19
    fp << endl;
	fp << "Capacity is " << A.Capacity() << endl;
	// 32
	fp << "Search is " << A.Search(14) << endl;
	// 14
	fp << "Select is " << A.Select(5) << endl;
	// 4
	A.Sort();
	// 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19
	A.Reverse();
	// 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0
	A.AddFront(-12); 
	// -12 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0
	fp << "Search is " << A.Search(19) << endl;
	// 19
	fp << "Select is " << A.Select(5) << endl;
	// 15
	A.Sort();
	// -12 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19
	A.AddEnd(-10);
	// -12 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 -10
	A.Sort();
	// -12 -10 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19
	A.DelFront(); A.DelEnd(); A.AddEnd(53); A[4] = 63;
	// -10 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 53
	for (int i=0; i< A.Length();i++) fp << A[i] << " ";  fp << endl;
	A.Sort();
	// -10 0 1 2 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 53 63
	CDA<int> B;
	A[0] = -1111;
	// -1111 0 1 2 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 53 63
	B = A;
	// -1111 0 1 2 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 53 63
	A[0] = -1001;
	// -1001 0 1 2 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 53 63
	A[1] = -1003;
	// -1001 -1003 1 2 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 53 63
	fp << B[0] << endl;
	// -1111
	foo(A);
	for (int i=0; i< B.Length();i++) fp << B[i] << " "; fp << endl;
	// -1111 0 1 2 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 53 63
	CDA<string> testGeneric1(10);
	CDA<wchar_t> testGeneric2(10);
	CDA<long double> testGeneric3(10);
	fp << "Passed Generics Test" << endl;
	if(printWrapper)fp << "-----------------Finished Test----------------------" << endl;
}

void test2(ostream &fp){
	if(printWrapper) fp << "Running test 2" << endl;
	CDA<int> A;
	for(int i = 0; i < 1002000; i++) A.AddFront(i);
	fp << "Select is " << A.Select(2000) << endl;
	A.Sort();
	fp << "Search is " << A.Search(20000) << endl;
	fp << "Search is " << A.Search(2000) << endl;
	fp << "Search is " << A.Search(200) << endl;
	fp << "Search is " << A.Search(20) << endl;
	fp << "Search is " << A.Search(2) << endl;
	if(printWrapper) fp << "-----------------Finished Test----------------------" << endl;
}

void test3(ostream &fp){
	if(printWrapper) fp << "Running test 3" << endl;
	CDA<int> A;
	for(int i = 0; i < 1002001; i++)
	{
		A.AddFront(i);
		A.Reverse();
		if (i % 100001 == 0) fp << "Finished number " << i << endl;
	}
	fp << "Search is " << A.Search(2001) << endl;
	fp << "Search is " << A.Search(20000) << endl;
	A.Sort();
	A.Reverse();
	fp << "Search is " << A.Search(4000) << endl;
	A.Sort();
	fp << "Search is " << A.Search(2001) << endl;
	fp << "Select is " << A.Select(2000) << endl;
	fp << "Test 3 Finished" << endl;
	if(printWrapper) fp << "-----------------Finished Test----------------------" << endl;
}

void test4(ostream &fp){
	if(printWrapper) fp << "Running test 4" << endl;
	CDA<int> A;
	for(int i = 1; i < 100200; i+=2) {A.AddFront(-i*2); A.AddEnd(i*2);}
	for (int i = -50000; i < 100200; i++)
	{
		A.BinSearch(i);
		if (i % 16000 == 0) fp << "BinSearch is " << A.BinSearch(i) << endl;
	}
	if(printWrapper) fp << "-----------------Finished Test----------------------" << endl;
}


