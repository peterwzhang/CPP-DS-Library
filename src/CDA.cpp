#ifndef CDA_CPP
#define CDA_CPP
#include <iostream>
#include <random>
template <typename elmtype>
class CDA {
   private:
    // CDA variables
    int size;
    int capacity;
    int front;
    int back;
    bool reverse;
    elmtype* array;
    elmtype elementtype;

    // CDA methods
    void Merge(elmtype A[], int start, int middle, int end);
    void MergeSort(elmtype A[], int start, int end);
    int Partition(elmtype a[], int p, int r);
    int RandomPivotPartition(elmtype a[], int p, int r);
    elmtype QuickSelect(elmtype a[], int p, int r, int i);
    void AddE(elmtype v);
    void AddF(elmtype v);
    void DelE();
    void DelF();
    // void PrintArray();
   public:
    CDA();
    CDA(int s);
    CDA(const CDA& cda);
    CDA<elmtype>& operator=(const CDA<elmtype>& cda);
    ~CDA();
    elmtype& operator[](int i);
    void AddEnd(elmtype v);
    void AddFront(elmtype v);
    void DelEnd();
    void DelFront();
    int Length();
    int Capacity();
    void Clear();
    void Reverse();
    elmtype Select(int k);
    void Sort();
    int Search(elmtype e);
    int BinSearch(elmtype e);
    void Swap(elmtype& a, elmtype& b);
};

// template <typename elmtype>
// void printarray(elmtype a[], int size)
//{
//	for (int i = 0; i < size; i++)
//		std::cout << a[i] << " ";
//	std::cout << std::endl;
//}

/* Default Constructor. The array should be of capacity 1,  size 0 and ordered
 * is false. O(1) */
template <typename elmtype>
CDA<elmtype>::CDA() {
    size = 0;
    capacity = 1;
    reverse = false;
    array = new elmtype[capacity];
}

/* For this constructor the array should be of capacity and size s.
 * O(1) */
template <typename elmtype>
CDA<elmtype>::CDA(int s) {
    size = s;
    capacity = s;
    front = 0;
    back = capacity - 1;
    reverse = false;
    array = new elmtype[capacity];
}

/* Copy constructor
 * O(n) */
template <typename elmtype>
CDA<elmtype>::CDA(const CDA& cda) {
    size = cda.size;
    capacity = cda.capacity;
    front = cda.front;
    back = cda.back;
    reverse = cda.reverse;
    array = new elmtype[cda.capacity];
    for (int i = 0; i < cda.capacity; i++) {
        array[i] = cda.array[i];
    }
}

/* = operator
 * O(n) */
template <typename elmtype>
CDA<elmtype>& CDA<elmtype>::operator=(const CDA<elmtype>& cda) {
    if (this == &cda) return *this;
    size = cda.size;
    capacity = cda.capacity;
    front = cda.front;
    back = cda.back;
    reverse = cda.reverse;
    delete[] array;
    array = new elmtype[cda.capacity];
    for (int i = 0; i < cda.capacity; i++) {
        array[i] = cda.array[i];
    }

    return *this;
}

/* Destructor for the class.
 * O(n) */
template <typename elmtype>
CDA<elmtype>::~CDA() {
    delete[] array;
}

/* Traditional [] operator. Should print a message if i is  out of bounds
 * (outside 0…size-1) and return a  reference to value of type elmtype stored in
 * the class  for this purpose. O(1) */
template <typename elmtype>
elmtype& CDA<elmtype>::operator[](int i) {
    if (i < 0 || i >= size) {
        std::cout << "Error: index " << i << " is out of bounds." << std::endl;
        return elementtype;
    }
    if (reverse) {
        int temp = back - i;
        if (temp < 0) temp += capacity;
        return array[temp];
    }
    return array[(i + front) % capacity];
}

/* increases the size of the array by 1 and stores v at the  end of the array.
 * Should double the capacity when the  new element doesn't fit. The new element
 * should be  accessed by the user at array[size-1]. O(1) amortized */
template <typename elmtype>
void CDA<elmtype>::AddEnd(elmtype v) {
    if (reverse)
        AddF(v);
    else
        AddE(v);
}

/* increases the size of the array by 1 and stores v at the  beginning of the
 * array. Should double the capacity  when the new element doesn't fit. The new
 * element  should be accessed by the user at array[0]. O(1) amortized */
template <typename elmtype>
void CDA<elmtype>::AddFront(elmtype v) {
    if (reverse)
        AddE(v);
    else
        AddF(v);
}

/* reduces the size of the array by 1 at the end. Should  shrink the capacity
 * when only 25% of the array is in use  after the delete. The capacity should
 * never go below 4. O(1) amortized */
template <typename elmtype>
void CDA<elmtype>::DelEnd() {
    if (reverse)
        DelF();
    else
        DelE();
}

/* reduces the size of the array by 1 at the beginning of  the array. Should
 * shrink the capacity when only 25% of  the array is in use after the delete.
 * The capacity should  never go below 4. O(1) amortized */
template <typename elmtype>
void CDA<elmtype>::DelFront() {
    if (reverse)
        DelE();
    else
        DelF();
}

/* returns the size of the array.
 * O(1) */
template <typename elmtype>
int CDA<elmtype>::Length() {
    return size;
}

/* returns the capacity of the array.
 * O(1) */
template <typename elmtype>
int CDA<elmtype>::Capacity() {
    return capacity;
}

/* Frees any space currently used and starts over with an  array of capacity 4
 * and size 0. O(1) */
template <typename elmtype>
void CDA<elmtype>::Clear() {
    delete[] array;
    size = 0;
    capacity = 4;
    reverse = false;
    array = new elmtype[4];
}

/* Change the logical direction of the array. This should  be accomplished using
 * a Boolean direction flag O(1) */
template <typename elmtype>
void CDA<elmtype>::Reverse() {
    reverse = (reverse) ? false : true;
}

/* Array is not sorted. Perform a quickselect algorithm to  return the kth
 * smallest element. Quickselect should  choose a random partition element.
 * O(size) expected */
template <typename elmtype>
elmtype CDA<elmtype>::Select(int k) {
    // make a copy of the array
    elmtype* temparray = new elmtype[size];
    if (reverse) {
        for (int i = 0; i < size; i++) {
            int temp = back - i;
            if (temp < 0) temp = temp + capacity;
            temparray[i] = array[temp];
        }
    } else {
        for (int i = 0; i < size; i++) {
            temparray[i] = array[(i + front) % capacity];
        }
    }
    elmtype returnval = QuickSelect(temparray, 0, size - 1, k);
    delete[] temparray;
    return returnval;
}

/* Sorts the values in the array using mergesort.
 * O(size lg size) */
template <typename elmtype>
void CDA<elmtype>::Sort() {
    elmtype* temparray = new elmtype[size];
    if (reverse) {
        for (int i = 0; i < size; i++) {
            int temp = back - i;
            if (temp < 0) temp = temp + capacity;
            temparray[i] = array[temp];
        }
    } else {
        for (int i = 0; i < size; i++) {
            temparray[i] = array[(i + front) % capacity];
        }
    }
    MergeSort(temparray, 0, size - 1);
    for (int i = 0; i < size; i++) array[i] = temparray[i];
    delete[] temparray;
    front = 0;
    back = size - 1;
    reverse = false;
}

/* Array is not sorted, perform a linear search of the array  looking for the
 * item e. Returns the index of the item if  found. Otherwise, return -1.
 * O(size) */
template <typename elmtype>
int CDA<elmtype>::Search(elmtype e) {
    for (int i = 0; i < size; i++) {
        if (this->operator[](i) == e) return i;
    }
    return -1;
}
/* Array is sorted, perform a binary search of the array  looking for the item
 * e. Returns the index of the item if  found. Otherwise, return a negative
 * number that is the  bitwise complement of the index of the next element  that
 * is larger than item e or, if there is no larger  element, the bitwise
 * complement of size. O(lg size) */
template <typename elmtype>
int CDA<elmtype>::BinSearch(elmtype e) {
    int start = 0, end = size - 1;
    while (start < end) {
        int m = (start + end) / 2;
        if (this->operator[](m) == e) return m;
        if (this->operator[](m) < e)
            start = m + 1;
        else
            end = m - 1;
    }
    if (this->operator[](start) == e)
        return start;
    else if (this->operator[](start) > e)
        return ~start;
    else if (start + 1 == size)
        return ~size;
    else
        return ~(start + 1);
}

// merge sub-array to start to middle and middle+1 to end
template <typename elmtype>
void CDA<elmtype>::Merge(elmtype A[], int start, int middle, int end) {
    int leftsize = middle - start + 1;
    int rightsize = end - middle;
    elmtype* L = new elmtype[leftsize];
    elmtype* R = new elmtype[rightsize];
    for (int i = 0; i < leftsize; i++) {
        L[i] = A[start + i];
    }
    for (int i = 0; i < rightsize; i++) {
        R[i] = A[middle + 1 + i];
    }
    int i = 0;
    int j = 0;
    int k = start;
    while (i < leftsize && j < rightsize) {
        if (L[i] < R[j]) {
            A[k] = L[i];
            k++;
            i++;
        } else {
            A[k] = R[j];
            k++;
            j++;
        }
    }
    while (i < leftsize) {
        A[k] = L[i];
        k++;
        i++;
    }
    while (j < rightsize) {
        A[k] = R[j];
        k++;
        j++;
    }
    delete[] L;
    delete[] R;
}

template <typename elmtype>
void CDA<elmtype>::MergeSort(elmtype A[], int start, int end) {
    if (start < end) {
        int mid = (start + end) / 2;
        MergeSort(A, start, mid);
        MergeSort(A, mid + 1, end);
        Merge(A, start, mid, end);
    }
}

template <typename elmtype>
int CDA<elmtype>::Partition(elmtype a[], int p, int r) {
    elmtype x = a[r];
    int i = p - 1;
    for (int j = p; j <= r - 1; j++) {
        if (a[j] <= x) {
            i++;
            Swap(a[i], a[j]);
        }
    }
    Swap(a[i + 1], a[r]);
    return i + 1;
}

template <typename elmtype>
int CDA<elmtype>::RandomPivotPartition(elmtype a[], int p, int r) {
    int modval = r - p + 1;
    int pvt = (modval == 0) ? r : p + rand() % (modval);
    swap(a[r], a[pvt]);
    return Partition(a, p, r);
}

template <typename elmtype>
elmtype CDA<elmtype>::QuickSelect(elmtype a[], int p, int r, int i) {
    if (p == r) return a[p];
    int q = RandomPivotPartition(a, p, r);
    int k = q - p + 1;
    if (i == k) return a[q];
    if (i < k) return QuickSelect(a, p, q - 1, i);
    return QuickSelect(a, q + 1, r, i - k);
}

template <typename elmtype>
void CDA<elmtype>::Swap(elmtype& a, elmtype& b) {
    elmtype temp = a;
    a = b;
    b = temp;
}

template <typename elmtype>
void CDA<elmtype>::AddE(elmtype v) {
    if (size == 0) {
        array[0] = v;
        front = 0;
        back = 0;
        size = 1;
    } else if (size == capacity) {
        int newCapacity = capacity * 2;
        elmtype* newArray = new elmtype[newCapacity];
        newArray[size] = v;
        for (int i = 0; i < size; i++) {
            newArray[i] = array[(i + front) % capacity];
        }
        delete[] array;
        array = newArray;
        front = 0;
        back = size;
        size++;
        capacity = newCapacity;
    } else {
        back = (back + 1) % capacity;
        array[back] = v;
        size++;
    }
}

template <typename elmtype>
void CDA<elmtype>::AddF(elmtype v) {
    if (size == 0) {
        array[0] = v;
        front = 0;
        back = 0;
        size = 1;
    } else if (size == capacity) {
        int newCapacity = capacity * 2;
        elmtype* newArray = new elmtype[newCapacity];
        newArray[0] = v;
        for (int i = 0; i < size; i++) {
            newArray[i + 1] = array[(front + i) % capacity];
        }
        delete[] array;
        array = newArray;
        front = 0;
        back = size;
        size++;
        capacity = newCapacity;
    } else {
        if (front == 0)
            front = capacity - 1;
        else
            front--;
        array[front] = v;
        size++;
    }
}

template <typename elmtype>
void CDA<elmtype>::DelE() {
    if (size == 0) {
        // do nothing
    } else {
        if (back == 0)
            back = capacity - 1;
        else
            back = back - 1;
        size--;
        if ((size <= capacity / 4)) {
            int newCapacity = capacity / 2;
            if (newCapacity >= 4) {
                elmtype* newArray = new elmtype[newCapacity];
                for (int i = 0; i < size; i++) {
                    newArray[i] = array[(i + front) % capacity];
                }
                delete[] array;
                array = newArray;
                front = 0;
                back = size - 1;
                capacity = newCapacity;
            }
        }
    }
}

template <typename elmtype>
void CDA<elmtype>::DelF() {
    if (size == 0) {
        // do nothing
    }
    front = (front + 1) % capacity;
    size--;
    if (size <= capacity / 4) {
        int newCapacity = capacity / 2;
        if (newCapacity >= 4) {
            elmtype* newArray = new elmtype[newCapacity];
            for (int i = 0; i < size; i++) {
                newArray[i] = array[(i + front + 1) % capacity];
            }
            delete[] array;
            array = newArray;
            front = 0;
            back = size - 1;
            capacity = newCapacity;
        }
    }
}

#endif