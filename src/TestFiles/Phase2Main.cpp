#include <iostream>
#include <cstdlib>
using namespace std;
#include "RBTree.cpp"

void printErrors(string errors, int numOfErrors){
	if(numOfErrors < 5){
		cout << errors << " PASSED " << endl;
	}else if(numOfErrors < 100){
		cout << errors << " caused " << numOfErrors << " of errors Add+1" << endl;
		cout << errors << " caused " << numOfErrors << " of errors Add+1" << endl;
		cout << errors << " caused " << numOfErrors << " of errors Add+1" << endl;
	}else if (numOfErrors < 1000){
		cout << errors << " caused " << numOfErrors << " of errors Add+1" << endl;
		cout << errors << " caused " << numOfErrors << " of errors Add+1" << endl;
	}else if (numOfErrors < 10000){
		cout << errors << " caused " << numOfErrors << " of errors Add+1" << endl;
	}else{
		cout << errors << " caused " << numOfErrors << " of errors" << endl;
	}
}

void test1();
void test2();
void test3();
void test4();
void test5();
void test6();
void removeIndex(int removeIndex);

int main(int argc, char **argv){
	int testToRun = atoi(argv[1]);
	switch (testToRun){
		case 1:
			test1();
			break;
		case 2:
			test2();
			break;
		case 3:
			test3();
			break;
		case 4:
			test4();
			break;
		case 5:
			test5();
			break;
		case 6:
			test6();
			break;
	}
	return 0;
}


void test1(){
	string K[11] = {"A","B","C","D","E","F","H","I","J","K","L"};
	int V[11] = {10,9,8,7,6,5,4,3,2,1,0};
	
	RBTree<string,int> T1, T2(K,V,11);
	T2.postorder();
	// A C B E H J L K I F D
	
	//Test edge case
	T2.remove("J");
	T2.remove("K");
	
	for(int i=0; i<11; i++) T1.insert(K[i],V[i]);
	// T1 and T2 should be identical trees
	
	T1.postorder();
	// A C B E H J L K I F D
	
	T1.insert("AF",11);
	T1.insert("AE",12);
	T1.insert("AD",13);
	cout << *(T1.search("AF")) << endl;	
	// 11
	
	cout << T1.rank("I") << endl;
	// 
	
	cout << T1.select(5) << endl;
	// B
	
	T1.preorder();
	// D B AE A AD AF C E F I H K J L
	
	T1.inorder();
	// A AD AE AF B C D E F H I J K L
	
	cout << T1.remove("HAHA") << endl;
	// 0
	
	cout << T1.remove("AD") << endl;
	// 1
	
	cout <<T1.rank("K") << endl;
	// 13
	
	T1.inorder();
	// A AE AF B C D E F H I J K L
    
	T1.preorder();
    
	T1.postorder();
    
    T1.printk(5);

	cout << "Finished without failing" << endl << endl;
}

void test2(){
	
	RBTree<int,int> X;
	for (int i=102;i>=0;i--) X.insert(i,102-i);
	
	X.preorder(); 
    
	X.postorder();
    
	X.inorder();
    
    X.printk(50);

	RBTree<int,int> Y = X;
	for (int i=0; i < 50; i++){
		X.rank(i);
		X.remove(i);
	}

    X.preorder();

    X.postorder();

    X.inorder();
	
	Y.preorder();
	
	Y.postorder();
    
	Y.inorder();
    
    Y.printk(50);

    RBTree<int,int> Z;
    for(int i=0; i < 1000200; i++) Z.insert(i, 1000200-i);
    
    Z.printk(100);

	cout << "Finished without failing" << endl << endl;
}

void test3(){
	int rankError = 0;
	int selectError = 0;
	int searchError = 0;
	int treeSize = 100200;
    RBTree<int,int> X;
	for (int i=treeSize;i>=0;i--) X.insert(i,treeSize-i);
	for (int i=1;i<treeSize;i++) {
		if(X.rank(i) != i+1) rankError++; 
		if(X.select(i) != i-1) selectError++; 
		if(*(X.search(i)) != treeSize-i) searchError++; 
	}
	printErrors("Rank",rankError);
	printErrors("Select",selectError);
	printErrors("Search",searchError);
	cout << "Finished without failing" << endl << endl;
}

void test4(){
	removeIndex(11);
}

void test5(){
	removeIndex(17);
}

void test6(){
	RBTree<int,int> X;
	int predErrors = 0;
	int succErrors = 0;
    int size = 11000;
	for (int i=size;i>=0;i--) X.insert(i,size-i);
	for (int i=0; i < X.size(); i++){
		if(i == 0){
            if(X.predecessor(i) != NULL) cout << "Doesn't return NULL for predecessor" << endl;
		}
        else if(*(X.predecessor(i)) != i-1){
            predErrors++;
        }
	}
	printErrors("Pred errors",predErrors);
	
	for (int i=X.size()-1; i >= 0; i--){
		if(i == size){
            if(X.successor(i) != NULL) cout << "Doesn't return NULL for successor" << endl;
		}
        else if(*(X.successor(i)) != i+1){ 
            succErrors++;
        }
	}	
	printErrors("Succ Errors",succErrors);
	
	cout << "Finished without failing" << endl << endl;
}

void removeIndex(int removeIndex){
	int rankError = 0;
	int selectError = 0;
	int searchError = 0;
    RBTree<int,int> X;
	int size = 100200;
    for (int i=size;i>=0;i--) X.insert(i,size-i);
	for (int i=0;i<size;i+=removeIndex) X.remove(i);
	for (int i=1;i<size-size/removeIndex;i++){
        
        int part1Answer = i / removeIndex;
		// Needed for round off error
		int answer = i+(i+(i+(i+(i+(i + i / removeIndex)/removeIndex)/removeIndex)/removeIndex)/removeIndex)/removeIndex;

		//printf("i is %d, Select %d, Rank %d, Search %d\n",i, answer, i-i/removeIndex, size-i);
        
        if(X.select(i) != answer){				
			selectError++;
			//cout << "i is " << i << " Select error after delete " << X.select(i)  << " should be " <<  answer << " or " << part1Answer << endl;
		}
		if (i%removeIndex) {
			//cout << i << " is i" << endl;
			if(X.rank(i) != i-i/removeIndex){
                rankError++; 
                //cout << "Rank error after delete " << X.rank(i) << " should be " << i << " - " << i-i/removeIndex << endl;
			}
            if(*(X.search(i)) != size-i) searchError++;// cout << "Search error after delete" << endl;
            X.remove(i);
			X.insert(i,size-i);
		}
	}
	printErrors("Rank after delete",rankError);
	printErrors("Select after delete",selectError);
	printErrors("Search after delete",searchError);
	cout << "Finished without failing" << endl << endl;
}

