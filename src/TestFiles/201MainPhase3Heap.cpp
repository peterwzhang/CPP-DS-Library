#include <iostream>
using namespace std;
#include "Heap.cpp"

void printErrors(string errors, int numOfErrors){
	if(numOfErrors < 5){
		cout << errors << " passed  (Key:imejki)" << endl;
	}else if(numOfErrors < 100){
		cout << errors << " caused " << numOfErrors << " of errors ADD+1(Key:kdjouk)" << endl;
		cout << errors << " caused " << numOfErrors << " of errors ADD+1(Key:kdjouk)" << endl;
		cout << errors << " caused " << numOfErrors << " of errors ADD+1(Key:kdjouk)" << endl;
	}else if (numOfErrors < 1000){
		cout << errors << " caused " << numOfErrors << " of errors ADD+1(Key:kdjouk)" << endl;
		cout << errors << " caused " << numOfErrors << " of errors ADD+1(Key:kdjouk)" << endl;
	}else if (numOfErrors < 10000){
		cout << errors << " caused " << numOfErrors << " of errors ADD+1(Key:kdjouk)" << endl;
	}else{
		cout << errors << " caused " << numOfErrors << " of errors" << endl;
	}
}

int main(){
	string A[25] = {"AD","AB","V","AA","A","B","U","C","D","E","W","F","H","I","J","X","K","L","M","O","Q","Y","R","S","T"};
	
	Heap<string> T1, T2(A,25);
	
	T2.printKey();
	
	for(int i=0; i<25; i++) T1.insert(A[i]);
	
	T1.printKey();
	
	cout << T2.peekKey() << endl;
	cout << T2.extractMin() << endl;
	
	cout << T1.peekKey() << endl;
	cout << T1.extractMin() << endl;
	cout << T1.extractMin() << endl;
	cout << T1.extractMin() << endl;
	cout << T1.extractMin() << endl;
	
	T1.printKey();

	Heap<int> X;
	for(int i = 0; i < 100000; i++){
		X.insert((i-50000));
	}
	X.printKey();
	int peakKey=0;
	int extractMin=0;
	for(int i = 0; i < 99999; i++){
		if(X.peekKey() != (i-50000)) peakKey++;
		if(X.extractMin() != (i-50000)) extractMin++;
	}
	printErrors("peakKey",peakKey);
	printErrors("extractMin",extractMin);
	return 0;
}
