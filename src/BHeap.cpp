#ifndef BHEAP_CPP
#define BHEAP_CPP
#include <iostream>
template <typename keytype>
class BNode {
   public:
    keytype key;
    int degree;
    BNode *parent, *child, *sibling;
    BNode(keytype key) {
        this->key = key;
        degree = 0;
        parent = nullptr;
        child = nullptr;
        sibling = nullptr;
    }
};

template <typename keytype>
class BHeap {
   private:
    BNode<keytype> *root;  // head of our root list; should also be the smallest
                           // degree node of the root list
    BNode<keytype> *min;   // smallest value of our root list
    // helper functions
    void link(BNode<keytype> *y, BNode<keytype> *z);
    BNode<keytype> *heapUnion(BNode<keytype> *H1, BNode<keytype> *H2);
    BNode<keytype> *heapMerge(BNode<keytype> *H1, BNode<keytype> *H2);
    void printHelper(BNode<keytype> *root);
    void updateMin();
    BNode<keytype> *reverse(BNode<keytype> *root);
    void cleanupNodes(BNode<keytype> *root);
    BNode<keytype> *copyNodes(BNode<keytype> *root);

   public:
    BHeap();
    BHeap(keytype k[], int s);
    BHeap(const BHeap &heap);
    BHeap &operator=(const BHeap &heap);
    ~BHeap();
    keytype peekKey();
    keytype extractMin();
    void insert(keytype k);
    void merge(BHeap<keytype> &H2);
    void printKey();
};

// y will become the child of z
template <typename keytype>
void BHeap<keytype>::link(BNode<keytype> *y, BNode<keytype> *z) {
    y->parent = z;
    y->sibling = z->child;
    z->child = y;
    z->degree++;
}
// merge two root lists, then sort in monotonically inceasing order
template <typename keytype>
BNode<keytype> *BHeap<keytype>::heapMerge(BNode<keytype> *H1,
                                          BNode<keytype> *H2) {
    // this procedure "destroys" the root list of H1, H2 by combining them into
    // H
    BNode<keytype> *H;          // our new root for our new heap
    BNode<keytype> **cur = &H;  // current location in our new root list
    while (H1 != nullptr && H2 != nullptr) {
        if (H1->degree < H2->degree) {
            *cur = H1;
            H1 = H1->sibling;
        } else {
            *cur = H2;
            H2 = H2->sibling;
        }
        cur = &(*cur)->sibling;
    }
    if (H1 != nullptr) {
        *cur = H1;
    } else {  // H2 != nullptr
        *cur = H2;
    }
    return H;
}

template <typename keytype>
BNode<keytype> *BHeap<keytype>::heapUnion(BNode<keytype> *H1,
                                          BNode<keytype> *H2) {
    BNode<keytype> *H, *prev_x, *next_x, *x;
    H = heapMerge(H1, H2);
    // free H1, H2 is unneeded since I still use them in the new H
    if (H == nullptr) return nullptr;
    prev_x = nullptr;
    x = H;
    next_x = H->sibling;
    while (next_x != nullptr) {
        if (x->degree != next_x->degree ||
            (next_x->sibling != nullptr &&
             next_x->sibling->degree == x->degree)) {
            prev_x = x;
            x = next_x;
        } else {
            if (x->key <= next_x->key) {
                x->sibling = next_x->sibling;
                link(next_x, x);

            } else {
                if (prev_x == nullptr) {
                    H = next_x;
                } else {
                    prev_x->sibling = next_x;
                }
                link(x, next_x);
                x = next_x;
            }
        }
        next_x = x->sibling;
    }
    return H;
}

template <typename keytype>
void BHeap<keytype>::printHelper(BNode<keytype> *root) {
    if (root == nullptr) return;
    std::cout << root->key;
    for (auto *cur = root->child; cur != nullptr; cur = cur->sibling) {
        std::cout << " ";
        printHelper(cur);
    }
}

// since there can only be floor(logn) + 1 nodes maximum in the root
// this will just be an O(logn) added onto other O(logn) operations
template <typename keytype>
void BHeap<keytype>::updateMin() {
    if (min == nullptr) {
        // if min is nullptr then set min to first element, then check for
        // update
        min = root;
    }
    for (auto *cur = root; cur != nullptr; cur = cur->sibling)
        if (cur->key < min->key) min = cur;
}

template <typename keytype>
BNode<keytype> *BHeap<keytype>::reverse(BNode<keytype> *root) {
    // given a root to a list, reverse it
    BNode<keytype> *next;
    BNode<keytype> *tail = nullptr;
    if (root == nullptr) return root;
    root->parent = nullptr;
    while (root->sibling != nullptr) {
        next = root->sibling;
        root->sibling = tail;
        tail = root;
        root = next;
        root->parent = nullptr;
    }
    root->sibling = tail;
    return root;
}

template <typename keytype>
void BHeap<keytype>::cleanupNodes(BNode<keytype> *root) {
    if (root == nullptr) return;
    BNode<keytype> *cur = root->child;
    while (cur) {
        BNode<keytype> *nodeToDel = cur;
        cur = cur->sibling;
        cleanupNodes(nodeToDel);
    }
    delete root;
}

template <typename keytype>
BNode<keytype> *BHeap<keytype>::copyNodes(BNode<keytype> *root) {
    if (root == nullptr) return nullptr;
    BNode<keytype> *newNode = new BNode<keytype>(root->key);
    newNode->degree = root->degree;
    newNode->child = copyNodes(root->child);
    newNode->sibling = copyNodes(root->sibling);
    if (newNode->child != nullptr) newNode->child->parent = newNode;
    if (newNode->sibling != nullptr) newNode->sibling->parent = newNode->parent;
    return newNode;
}

// start pub func

/* Default Constructor. The Heap should be empty
 * O(1) */
template <typename keytype>
BHeap<keytype>::BHeap() {
    root = nullptr;
    min = nullptr;
}
/* This constructor builds the heap using repeated insertion with values from
 * array k.
 * O(s) */
template <typename keytype>
BHeap<keytype>::BHeap(keytype k[], int s) {
    root = nullptr;
    min = nullptr;
    for (int i = 0; i < s; i++) {
        insert(k[i]);
    }
}
/* Copy Constructor
 * O(n) */
template <typename keytype>
BHeap<keytype>::BHeap(const BHeap &heap) {
    root = nullptr;
    min = nullptr;
    root = copyNodes(heap.root);
    updateMin();
}
/* = overload
 * O(n) */
template <typename keytype>
BHeap<keytype> &BHeap<keytype>::operator=(const BHeap &heap) {
    if (this != &heap) {
        if (root != nullptr) {
            for (auto *cur = root; cur != nullptr; cur = cur->sibling) {
                cleanupNodes(cur);
            }
        }
        root = nullptr;
        min = nullptr;
        root = copyNodes(heap.root);
        updateMin();
    }
    return *this;
}
/* Destructor for the class.
 * O(n) */
template <typename keytype>
BHeap<keytype>::~BHeap() {
    BNode<keytype> *cur = root;
    while (cur) {
        BNode<keytype> *nodeToDel = cur;
        cur = cur->sibling;
        cleanupNodes(nodeToDel);
    }
}

/* Returns the minimum key in the heap without modifiying the heap.
 * O(1) */
template <typename keytype>
keytype BHeap<keytype>::peekKey() {
    return min->key;
}

/* Removes the minimum key in the heap and returns the key.
 * O(lg n) */
template <typename keytype>
keytype BHeap<keytype>::extractMin() {
    if (root == nullptr) {
        keytype defReturn{};
        return defReturn;
    }
    keytype returnKey = min->key;
    if (root == min)
        // easy case
        root = root->sibling;
    else {
        // find previous of min, then cut out min
        for (auto *cur = root; cur != nullptr; cur = cur->sibling) {
            if (cur->sibling == min) cur->sibling = min->sibling;
        }
    }
    BNode<keytype> *newHeap = reverse(min->child);
    root = heapUnion(root, newHeap);
    delete min;
    min = nullptr;
    updateMin();
    return returnKey;
}

/* Inserts the key k into the heap.
 * O(lg n) */
template <typename keytype>
void BHeap<keytype>::insert(keytype k) {
    BNode<keytype> *newHeap =
        new BNode<keytype>(k);  // new "heap" that contains a single b0
    if (root == nullptr)  // if the tree is empty, set min to the first node
        min = newHeap;
    root = heapUnion(root, newHeap);
    updateMin();
}

/* Merges the heap H2 into the current heap. Consumes H2.
 * O(lg n) */
template <typename keytype>
void BHeap<keytype>::merge(BHeap<keytype> &H2) {
    // assuming both heaps will be valid non null heaps
    root = heapUnion(root, H2.root);
    updateMin();
    H2.root = nullptr;
}

/* Writes the keys stored in the heap, printing the smallest binomial tree
 * first. This uses a modified preorder.
 * O(n) */
template <typename keytype>
void BHeap<keytype>::printKey() {
    for (auto *cur = root; cur != nullptr; cur = cur->sibling) {
        std::cout << "B" << cur->degree << std::endl;
        printHelper(cur);
        if (cur->sibling == nullptr)
            std::cout << std::endl;
        else
            std::cout << std::endl << std::endl;
    }
}
#endif