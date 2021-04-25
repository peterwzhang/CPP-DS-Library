#ifndef HEAP_CPP
#define HEAP_CPP
#include "CDA.cpp"
template <typename keytype>
class Heap {
   private:
    CDA<keytype> array;
    int size;
    int parent(int i) { return (i - 1) / 2; }
    int left(int i) { return 2 * i + 1; }
    int right(int i) { return 2 * i + 2; }
    void minHeapify(int i);
    void buildMinHeap(keytype A[], int s);
    void heapDecreaseKey(int i, keytype key);

   public:
    Heap();
    Heap(keytype k[], int s);
    Heap(const Heap& heap);
    Heap& operator=(const Heap& heap);
    ~Heap();
    keytype peekKey();
    keytype extractMin();
    void insert(keytype k);
    void printKey();
};

/* Default Constructor. The Heap should be empty
 * O(1) */
template <typename keytype>
Heap<keytype>::Heap() {
    // just use default cda cons
}

/* This constructor builds the heap using the bottom up heap building method
 * from array k.
 * O(s) */
template <typename keytype>
Heap<keytype>::Heap(keytype k[], int s) {
    array = CDA<keytype>(s);
    buildMinHeap(k, s);
}

/* Copy constructor
 * O(n) */
template <typename keytype>
Heap<keytype>::Heap(const Heap& heap) {
    array = heap.array;
}

/* = overload
 * O(n) */
template <typename keytype>
Heap<keytype>& Heap<keytype>::operator=(const Heap<keytype>& heap) {
    if (this != &heap) array = heap.array;
    return *this;
}

/* Destructor for the class.
 * O(1) */
template <typename keytype>
Heap<keytype>::~Heap() {
    // mem managed by cda
    // just a single free to the array
}

/* Returns the minimum key in the heap without modifiying the heap.
 * O(1) */
template <typename keytype>
keytype Heap<keytype>::peekKey() {
    return array[0];
}

/* Removes the minimum key in the heap and returns the key.
 * O(lg n) */
template <typename keytype>
keytype Heap<keytype>::extractMin() {
    // if (array.Length() < 1){
    //     // nothing to extract
    // }
    keytype min = array[0];
    array[0] = array[array.Length() - 1];
    array.DelEnd();
    minHeapify(0);
    return min;
}

/* Inserts the key k into the heap.
 * O(lg n) */
template <typename keytype>
void Heap<keytype>::insert(keytype k) {
    array.AddEnd(k);
    // do we need this line?

    heapDecreaseKey(array.Length() - 1, k);
}

/* Writes the keys stored in the array, starting at the root.
 * O(n) */
template <typename keytype>
void Heap<keytype>::printKey() {
    for (int i = 0; i < array.Length(); i++) {
        if (i == 0)
            std::cout << array[i];
        else
            std::cout << " " << array[i];
    }
    std::cout << std::endl;
}

template <typename keytype>
void Heap<keytype>::minHeapify(int i) {
    int left = Heap::left(i);
    int right = Heap::right(i);
    int smallest = i;  // array[left] >= array[i] or array[right] >= array[i]
    if (left < array.Length() && array[left] < array[smallest]) smallest = left;
    if (right < array.Length() && array[right] < array[smallest])
        smallest = right;
    if (smallest != i) {
        array.Swap(array[i], array[smallest]);
        minHeapify(smallest);
    }
}

template <typename keytype>
void Heap<keytype>::buildMinHeap(keytype A[], int s) {
    for (int i = 0; i < s; i++) {
        array[i] = A[i];
    }
    for (int i = (array.Length() / 2) - 1; i >= 0; i--) {
        minHeapify(i);
    }
}

template <typename keytype>
void Heap<keytype>::heapDecreaseKey(int i, keytype key) {
    if (key > array[i]) {
        return;  // key is greater than current key
    }
    array[i] = key;
    while (i > 0 && array[parent(i)] > array[i]) {
        array.Swap(array[i], array[parent(i)]);
        i = parent(i);
    }
}
#endif