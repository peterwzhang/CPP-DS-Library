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
	CDA<int> C(25);
	for (int i=0; i< C.Length();i++) C[i] = i*10;
	for (int i=0; i< C.Length();i++) fp << C[i] << " "; fp << endl;
	C.DelFront();
	C.DelFront();
	for (int i=0; i< C.Length();i++) fp << C[i] << " ";  fp << endl;
	C.DelEnd();
	C.DelEnd();
	for (int i=0; i< C.Length();i++) fp << C[i] << " ";  fp << endl;
	C.AddEnd(1001);
	C.AddEnd(1003);
	for (int i=0; i< C.Length();i++) fp << C[i] << " ";  fp << endl;
	C.AddFront(1004);
	C.AddEnd(1006);
	for (int i=0; i< C.Length();i++) fp << C[i] << " ";  fp << endl;
	C.DelEnd(); C.DelEnd();
	C.AddFront(-105); 
	C.AddFront(-205);
	for (int i=0; i< C.Length();i++) fp << C[i] << " ";  fp << endl;
	fp << "Capacity is " << C.Capacity() << endl;
	
	while(C.Length()){
		C.DelEnd();
	}
	C.Clear();
	fp << "Capacity is " << C.Capacity() << endl;
	if(printWrapper)fp << "-----------------Finished Test----------------------" << endl;
}

void test1(ostream &fp){
	if(printWrapper) fp << "Running test 1" << endl;
	CDA<int> A;
	int temp = 0;
	for(int i=0; i<19;i++){
		A.AddEnd(i*11);
		if(A.Capacity() != temp){
			temp = A.Capacity();
			fp << "Capacity is " << temp << " ";
		}
	}
    fp << endl;
	fp << "Capacity is " << A.Capacity() << endl;
	fp << "Search is " << A.Search(165) << endl;
	fp << "Select is " << A.Select(5) << endl;
	A.Sort();
	A.Reverse();
	A.AddFront(12); 
	fp << "Search is " << A.Search(165) << endl;
	fp << "Select is " << A.Select(5) << endl;
	A.Sort();
	A.AddEnd(-10);
	A.Sort();
	A.DelFront(); A.DelEnd(); A.AddEnd(53);
	for (int i=0; i< A.Length();i++) fp << A[i] << " ";  fp << endl;
	A.Sort();
	CDA<int> B;
	A[0] = -1111;
	B = A;
	A[0] = -1001;
	A[1] = -1003;
	fp << B[0] << endl;
	foo(A);
	for (int i=0; i< B.Length();i++) fp << B[i] << " ";  
	fp << endl;
	CDA<string> testGeneric1(10);
	CDA<wchar_t> testGeneric2(10);
	CDA<long double> testGeneric3(10);
	fp << "Passed Generics Test" << endl;
	if(printWrapper)fp << "-----------------Finished Test----------------------" << endl;
}

void test2(ostream &fp){
	if(printWrapper) fp << "Running test 2" << endl;
	CDA<int> A;
	for(int i = 0; i < 100100; i++) A.AddFront(i);
	fp << "Select is " << A.Select(4000) << endl;
	A.Sort();
	fp << "Search is " << A.Search(40000) << endl;
	fp << "Search is " << A.Search(4000) << endl;
	fp << "Select is " << A.Select(400) << endl;
	fp << "Search is " << A.Search(40) << endl;
	fp << "Search is " << A.Search(4) << endl;
	if(printWrapper) fp << "-----------------Finished Test----------------------" << endl;
}

void test3(ostream &fp){
	if(printWrapper) fp << "Running test 3" << endl;
	CDA<int> A;
	for(int i = 0; i < 1001001; i++)
	{
		A.AddFront(i);
		A.Reverse();
		if (i % 100000 == 0) fp << "Finished number " << i << endl;
	}
	fp << "Search is " << A.Search(4000) << endl;
	fp << "Select is " << A.Select(400) << endl;
	A.Reverse();
	fp << "Search is " << A.Search(4000) << endl;
	fp << "Select is " << A.Select(400) << endl;
	fp << "Test 3 Finished" << endl;
	if(printWrapper) fp << "-----------------Finished Test----------------------" << endl;
}

void test4(ostream &fp){
	if(printWrapper) fp << "Running test 4" << endl;
	CDA<int> A;
	for(int i = 1; i < 100100; i+=2) {A.AddFront(-i*2); A.AddEnd(i*2);}
	for (int i = -50000; i < 100100; i++)
	{
		A.BinSearch(i);
		if (i % 2000 == 0) fp << "BinSearch is " << A.BinSearch(i) << endl;
	}
	if(printWrapper) fp << "-----------------Finished Test----------------------" << endl;
}


