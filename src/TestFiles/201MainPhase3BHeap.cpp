#include <iostream>
using namespace std;
#include "BHeap.cpp"

void printErrors(string errors, int numOfErrors){
	if(numOfErrors < 5){
		cout << errors << " passed (Key:imeidj)" << endl;
	}else if(numOfErrors < 100){
		cout << errors << " caused " << numOfErrors << " of errors ADD+1(Key:kdjoum)" << endl;
		cout << errors << " caused " << numOfErrors << " of errors ADD+1(Key:kdjoum)" << endl;
		cout << errors << " caused " << numOfErrors << " of errors ADD+1(Key:kdjoum)" << endl;
	}else if (numOfErrors < 1000){
		cout << errors << " caused " << numOfErrors << " of errors ADD+1(Key:kdjoum)" << endl;
		cout << errors << " caused " << numOfErrors << " of errors ADD+1(Key:kdjoum)" << endl;
	}else if (numOfErrors < 10000){
		cout << errors << " caused " << numOfErrors << " of errors ADD+1(Key:kdjoum)" << endl;
	}else{
		cout << errors << " caused " << numOfErrors << " of errors " << endl;
	}
}

int main(){
	string A[25] = {"Z","AD","AB","AA","A","Y","B","C","D","E","X","F","H","I","J","W","K","L","M","O","U","Q","R","S","T"};
	
	BHeap<string> Z(A,25), Y;

	Z.printKey();

	cout << endl << Z.extractMin() << endl;
	
	Z.printKey();
	
	Y.insert("P"); 
	Y.insert("h");
	Y.insert("a");
	Y.insert("s");
	Y.insert("e");
	Y.insert("3*3-6");
	
	Y.printKey();
	
	Y.merge(Z);
	cout << endl << Y.peekKey() << endl;
	
	Y.printKey();
	
	BHeap<int> X;
	for(int i = 1; i < 100001; i++){
		X.insert(-i);
	}
	int peakKey=0;
	int extractMin=0;
	for(int i = 100000; i > 0; i--){
		if(X.peekKey() != -i) peakKey++;
		if(X.extractMin() != -i) extractMin++;
	}
	printErrors("peakKey",peakKey);
	printErrors("extractMin",extractMin);		
	
	BHeap<int> C,D;
	for(int i = 1; i < 100001; i++){
		C.insert(-i);
		D.insert(i);
	}
	C.merge(D);
	peakKey=0;
	extractMin=0;
	for(int i = 100000; i > 0; i--){
		if(C.peekKey() != -i) peakKey++;
		if(C.extractMin() != -i) extractMin++;
	}
	for(int i = 1; i < 100001; i++){
		if(C.peekKey() != i) peakKey++;
		if(C.extractMin() != i) extractMin++;
	}
	printErrors("peakKey",peakKey);
	printErrors("extractMin",extractMin);
	return 0;
}
