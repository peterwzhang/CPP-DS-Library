#ifndef RBTree_CPP
#define RBTree_CPP
#include <iostream>
template <typename keytype, typename valuetype>
class RBTNode {
   public:
    keytype key;
    valuetype value;
    RBTNode *parent;
    RBTNode *left;
    RBTNode *right;
    unsigned char color;  // 0 = red, 1 = black
    unsigned int size;    // size of subtree
    RBTNode() {           // nil default constructor
        parent = nullptr;
        left = nullptr;
        right = nullptr;
        color = 1;
        size = 0;
    }
    RBTNode(keytype k, valuetype v, RBTNode<keytype, valuetype> *p,
            RBTNode<keytype, valuetype> *l, RBTNode<keytype, valuetype> *r,
            unsigned char c, unsigned int s)
        : key(k), value(v), parent(p), left(l), right(r), color(c), size(s) {}
};

template <typename keytype, typename valuetype>
class RBTree {
   public:
    RBTree();
    RBTree(keytype k[], valuetype V[], int s);
    RBTree(const RBTree &rhs);
    RBTree &operator=(const RBTree &rhs);
    ~RBTree();
    valuetype *search(keytype k);
    void insert(keytype k, valuetype v);
    int remove(keytype k);
    int rank(keytype k);
    keytype select(int pos);
    keytype *successor(keytype k);
    keytype *predecessor(keytype k);
    int size();
    void preorder();
    void inorder();
    void postorder();
    void printk(int k);

   private:
    RBTNode<keytype, valuetype> *root;
    RBTNode<keytype, valuetype>
        *nil;  // should be a sentinel value with arbitrary values except color
               // must be black (1)
    int num_nodes;
    // helper functions below this line
    void leftRotate(RBTNode<keytype, valuetype> *x);
    void rightRotate(RBTNode<keytype, valuetype> *x);
    void insertFixup(RBTNode<keytype, valuetype> *z);
    void deleteFixup(RBTNode<keytype, valuetype> *x);
    void transplant(RBTNode<keytype, valuetype> *u,
                    RBTNode<keytype, valuetype> *v);
    RBTNode<keytype, valuetype> *searchNode(keytype k);
    RBTNode<keytype, valuetype> *treeMin(RBTNode<keytype, valuetype> *r);
    RBTNode<keytype, valuetype> *treeMax(RBTNode<keytype, valuetype> *r);
    RBTNode<keytype, valuetype> *selectNode(RBTNode<keytype, valuetype> *x,
                                            int i);
    RBTNode<keytype, valuetype> *findNext(RBTNode<keytype, valuetype> *r);
    RBTNode<keytype, valuetype> *findPrev(RBTNode<keytype, valuetype> *r);
    void printPreorder(RBTNode<keytype, valuetype> *r);
    void printInorder(RBTNode<keytype, valuetype> *r);
    void printPostorder(RBTNode<keytype, valuetype> *r);
    RBTNode<keytype, valuetype> *copyNodes(RBTNode<keytype, valuetype> *s,
                                           RBTNode<keytype, valuetype> *p,
                                           RBTNode<keytype, valuetype> *p_nil);
    void clearNodes(RBTNode<keytype, valuetype> *r);
    int rankSubtree(RBTNode<keytype, valuetype> *r, keytype k);
};

template <typename keytype, typename valuetype>
void RBTree<keytype, valuetype>::leftRotate(RBTNode<keytype, valuetype> *x) {
    auto *y = x->right;  // set y
    x->right = y->left;  // turn y's left subtree into x's right subtree
    if (y->left != nil) y->left->parent = x;
    y->parent = x->parent;  // link x's parent to y
    if (x->parent == nil)
        root = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;
    y->left = x;  // put x on y's left
    x->parent = y;
    y->size = x->size;  // maintain size here
    x->size = x->left->size + x->right->size + 1;
}

template <typename keytype, typename valuetype>
void RBTree<keytype, valuetype>::rightRotate(RBTNode<keytype, valuetype> *x) {
    auto *y = x->left;   // set y
    x->left = y->right;  // turn y's right subtree into x's left subtree
    if (y->right != nil) y->right->parent = x;
    y->parent = x->parent;  // link x's parent to y
    if (x->parent == nil)
        root = y;
    else if (x == x->parent->right)
        x->parent->right = y;
    else
        x->parent->left = y;
    y->right = x;  // put x on y's right
    x->parent = y;
    y->size = x->size;  // maintain size here
    x->size = x->left->size + x->right->size + 1;
}

template <typename keytype, typename valuetype>
void RBTree<keytype, valuetype>::insertFixup(RBTNode<keytype, valuetype> *z) {
    while (z->parent->color == 0) {
        if (z->parent == z->parent->parent->left) {
            auto *y = z->parent->parent->right;
            if (y->color == 0) {  // case 1a
                z->parent->color = 1;
                y->color = 1;
                z->parent->parent->color = 0;
                z = z->parent->parent;
            } else {
                if (z == z->parent->right) {  // case 2a
                    z = z->parent;
                    leftRotate(z);
                }
                z->parent->color = 1;  // case 3a
                z->parent->parent->color = 0;
                rightRotate(z->parent->parent);
            }
        } else {
            auto *y = z->parent->parent->left;
            if (y->color == 0) {  // case 1b
                z->parent->color = 1;
                y->color = 1;
                z->parent->parent->color = 0;
                z = z->parent->parent;
            } else {
                if (z == z->parent->left) {  // case 2b
                    z = z->parent;
                    rightRotate(z);
                }
                z->parent->color = 1;  // case 3b
                z->parent->parent->color = 0;
                leftRotate(z->parent->parent);
            }
        }
    }
    root->color = 1;
}

template <typename keytype, typename valuetype>
void RBTree<keytype, valuetype>::deleteFixup(RBTNode<keytype, valuetype> *x) {
    while (x != root && x->color == 1) {
        if (x == x->parent->left) {
            auto *w = x->parent->right;
            if (w->color == 0) {  // case 1a
                w->color = 1;
                x->parent->color = 0;
                leftRotate(x->parent);
                w = x->parent->right;
            }
            if (w->left->color == 1 && w->right->color == 1) {  // case 2a
                w->color = 0;
                x = x->parent;
            } else {
                if (w->right->color == 1) {  // case 3a
                    w->left->color = 1;
                    w->color = 0;
                    rightRotate(w);
                    w = x->parent->right;
                }
                w->color = x->parent->color;  // case 4a
                x->parent->color = 1;
                w->right->color = 1;
                leftRotate(x->parent);
                x = root;
            }
        } else {  // symmetric case
            auto w = x->parent->left;
            if (w->color == 0) {  // case 1b
                w->color = 1;
                x->parent->color = 0;
                rightRotate(x->parent);
                w = x->parent->left;
            }
            if (w->left->color == 1 && w->right->color == 1) {  // case 2b
                w->color = 0;
                x = x->parent;
            } else {
                if (w->left->color == 1) {  // case 3b
                    w->right->color = 1;
                    w->color = 0;
                    leftRotate(w);
                    w = x->parent->left;
                }
                w->color = x->parent->color;  // case 4b
                x->parent->color = 1;
                w->left->color = 1;
                rightRotate(x->parent);
                x = root;
            }
        }
    }
    x->color = 1;
}

template <typename keytype, typename valuetype>
void RBTree<keytype, valuetype>::transplant(RBTNode<keytype, valuetype> *u,
                                            RBTNode<keytype, valuetype> *v) {
    if (u->parent == nil)
        root = v;
    else if (u == u->parent->left)
        u->parent->left = v;
    else
        u->parent->right = v;
    v->parent = u->parent;
}

template <typename keytype, typename valuetype>
RBTNode<keytype, valuetype> *RBTree<keytype, valuetype>::searchNode(keytype k) {
    auto *cur = root;
    while (cur != nil) {
        if (k == cur->key) return cur;
        if (cur->key <= k)
            cur = cur->right;
        else
            cur = cur->left;
    }
    return nil;
}

template <typename keytype, typename valuetype>
RBTNode<keytype, valuetype> *RBTree<keytype, valuetype>::treeMin(
    RBTNode<keytype, valuetype> *r) {
    auto *cur = r;
    while (cur->left != nil) cur = cur->left;
    return cur;
}

template <typename keytype, typename valuetype>
RBTNode<keytype, valuetype> *RBTree<keytype, valuetype>::treeMax(
    RBTNode<keytype, valuetype> *r) {
    auto *cur = r;
    while (cur->right != nil) cur = cur->right;
    return cur;
}

template <typename keytype, typename valuetype>
RBTNode<keytype, valuetype> *RBTree<keytype, valuetype>::selectNode(
    RBTNode<keytype, valuetype> *x, int i) {
    int r = x->left->size + 1;
    if (i == r)
        return x;
    else if (i < r)
        return selectNode(x->left, i);
    else
        return selectNode(x->right, i - r);
}

template <typename keytype, typename valuetype>
RBTNode<keytype, valuetype> *RBTree<keytype, valuetype>::findNext(
    RBTNode<keytype, valuetype> *n) {
    if (n->right != nil)
        return treeMin(n->right);
    else {
        auto *cur = n;
        auto *p = n->parent;
        while (p != nil && cur == p->right) {
            cur = p;
            p = p->parent;
        }
        return p;
    }
}

template <typename keytype, typename valuetype>
RBTNode<keytype, valuetype> *RBTree<keytype, valuetype>::findPrev(
    RBTNode<keytype, valuetype> *n) {
    if (n->left != nil)
        return treeMax(n->left);
    else {
        auto *cur = n;
        auto *p = n->parent;
        while (p != nil && cur == p->left) {
            cur = p;
            p = p->parent;
        }
        return p;
    }
}

template <typename keytype, typename valuetype>
void RBTree<keytype, valuetype>::printPreorder(RBTNode<keytype, valuetype> *r) {
    if (r != nil) {
        std::cout << r->key;
        // color visual
        // if (r->color == 0)
        //     std::cout << "\x1B[31m" << r->key << "\033[0m ";
        // else
        //     std::cout << r->key << " ";
        if (r->left != nil) {
            std::cout << " ";
            printPreorder(r->left);
        }
        if (r->right != nil) {
            std::cout << " ";
            printPreorder(r->right);
        }
    }
}

template <typename keytype, typename valuetype>
void RBTree<keytype, valuetype>::printInorder(RBTNode<keytype, valuetype> *r) {
    if (r != nil) {
        printInorder(r->left);
        if (r->left != nil) std::cout << " ";
        std::cout << r->key;
        // color visual
        // if (r->color == 0)
        //     std::cout << "\x1B[31m" << r->key << "\033[0m ";
        // else
        //     std::cout << r->key << " ";
        if (r->right != nil) std::cout << " ";
        printInorder(r->right);
    }
}

template <typename keytype, typename valuetype>
void RBTree<keytype, valuetype>::printPostorder(
    RBTNode<keytype, valuetype> *r) {
    if (r != nil) {
        if (r->left != nil) {
            printPostorder(r->left);
            std::cout << " ";
        }
        if (r->right != nil) {
            printPostorder(r->right);
            std::cout << " ";
        }
        std::cout << r->key;
        // color visual
        // if (r->color == 0)
        //     std::cout << "\x1B[31m" << r->key << "\033[0m ";
        // else
        //     std::cout << r->key << " ";
    }
}

template <typename keytype, typename valuetype>
RBTNode<keytype, valuetype> *RBTree<keytype, valuetype>::copyNodes(
    RBTNode<keytype, valuetype> *s, RBTNode<keytype, valuetype> *p,
    RBTNode<keytype, valuetype> *p_nil) {
    if (s == p_nil) return nil;
    RBTNode<keytype, valuetype> *newNode = new RBTNode<keytype, valuetype>;
    newNode->key = s->key;
    newNode->value = s->value;
    newNode->parent = p;
    newNode->color = s->color;
    newNode->size = s->size;
    newNode->left = copyNodes(s->left, newNode, p_nil);
    newNode->right = copyNodes(s->right, newNode, p_nil);
    return newNode;
}

template <typename keytype, typename valuetype>
void RBTree<keytype, valuetype>::clearNodes(
    RBTNode<keytype, valuetype> *r) {  // clear all nodes but nil
    if (r != nil) {
        auto *nextLeft = r->left;
        auto *nextRight = r->right;
        delete r;
        clearNodes(nextLeft);
        clearNodes(nextRight);
    }
}

template <typename keytype, typename valuetype>
int RBTree<keytype, valuetype>::rankSubtree(RBTNode<keytype, valuetype> *r,
                                            keytype k) {
    // assume k exists
    if (k == r->key) {
        return (r->left == nil) ? 1 : 1 + r->left->size;
    } else if (k > r->key) {
        return ((r->left == nil) ? 1 : 1 + r->left->size) +
               rankSubtree(r->right, k);
    } else {  // k < r->key
        return rankSubtree(r->left, k);
    }
}

/*<============Public Functions============>*/
/* Default Constructor. The tree should be empty
 * O(1) */
template <typename keytype, typename valuetype>
RBTree<keytype, valuetype>::RBTree() {
    nil = new RBTNode<keytype, valuetype>;
    root = nil;
    num_nodes = 0;
}

/* For this constructor the tree should be built using  the arrays K and V
 * containing s items of keytype and valuetype. O(s lg s) */
template <typename keytype, typename valuetype>
RBTree<keytype, valuetype>::RBTree(keytype k[], valuetype v[], int s) {
    nil = new RBTNode<keytype, valuetype>;
    root = nil;
    num_nodes = 0;
    for (int i = 0; i < s; i++) {
        insert(k[i], v[i]);
    }
}

/* Copy constructor
 * O(1) */
template <typename keytype, typename valuetype>
RBTree<keytype, valuetype>::RBTree(const RBTree &rhs) {
    nil = new RBTNode<keytype, valuetype>;
    root = copyNodes(rhs.root, nil, rhs.nil);
    num_nodes = rhs.num_nodes;
}

/* = operator
 * O(n) */
template <typename keytype, typename valuetype>
RBTree<keytype, valuetype> &RBTree<keytype, valuetype>::operator=(
    const RBTree &rhs) {
    if (this == &rhs) return *this;
    clearNodes(root);
    delete nil;
    nil = new RBTNode<keytype, valuetype>;
    root = copyNodes(rhs.root, nil, rhs.nil);
    num_nodes = rhs.num_nodes;
    return *this;
}

/* Destructor for the class.
 * O(n) */
template <typename keytype, typename valuetype>
RBTree<keytype, valuetype>::~RBTree() {
    clearNodes(root);
    delete nil;
}

/* Traditional search. Should return a pointer to the  valuetype stored with the
 * key. If the key is not  stored in the tree then the function should return
 * NULL. O(lg n) */
template <typename keytype, typename valuetype>
valuetype *RBTree<keytype, valuetype>::search(keytype k) {
    RBTNode<keytype, valuetype> *node = searchNode(k);
    if (node == nil) return NULL;
    return &node->value;
}

/* Inserts the node with key k and value v into the  tree.
 * O(lg n) */
template <typename keytype, typename valuetype>
void RBTree<keytype, valuetype>::insert(keytype k, valuetype v) {
    auto *z = new RBTNode<keytype, valuetype>(k, v, nil, nil, nil, 0, 1);
    auto *y = nil;
    auto *x = root;
    // to maintain size, increase path to new node
    while (x != nil) {
        x->size++;
        y = x;
        if (z->key < x->key)
            x = x->left;
        else
            x = x->right;
    }
    z->parent = y;
    if (y == nil)
        root = z;
    else if (z->key < y->key)
        y->left = z;
    else
        y->right = z;
    insertFixup(z);
    num_nodes++;
}

/* Removes the node with key k and returns 1. If  key k is not found then remove
 * should return 0. If  the node with key k is not a leaf then replace k by  its
 * predecessor. O(lg n) */
template <typename keytype, typename valuetype>
int RBTree<keytype, valuetype>::remove(keytype k) {
    auto *z = searchNode(k);  // z is node to delete
    if (z == nil)             // node not found
        return 0;
    // maintain size, path from found node to root
    if (z != root) {
        auto *cur = z->parent;
        while (cur != root) {
            cur->size--;
            cur = cur->parent;
        }
        root->size--;
    }
    RBTNode<keytype, valuetype> *x;
    auto *y = z;
    char y_orig_color = y->color;
    if (z->left == nil) {
        x = z->right;
        transplant(z, z->right);
    } else if (z->right == nil) {
        x = z->left;
        transplant(z, z->left);
    } else {
        y = treeMax(z->left);  // this is predecessor
        y_orig_color = y->color;
        x = y->left;
        if (y->parent == z)
            x->parent = y;
        else {
            transplant(y, y->left);
            y->left = z->left;
            y->left->parent = y;
            // if we need to transplant here we need to update sizes from
            // predecessor to node to delete
            auto *cur = x->parent;
            while (cur != y) {
                cur->size--;
                cur = cur->parent;
            }
        }
        transplant(z, y);
        y->right = z->right;
        y->right->parent = y;
        y->color = z->color;
        // update predecessor with new subtree sizes
        y->size = y->left->size + y->right->size + 1;
    }
    if (y_orig_color == 1) deleteFixup(x);
    num_nodes--;
    delete z;
    return 1;
}

/* Returns the rank of the key k in the tree. Returns  0 if the key k is not
 * found. The smallest item in  the tree is rank 1. O(lg n) */
template <typename keytype, typename valuetype>
int RBTree<keytype, valuetype>::rank(keytype k) {
    auto *x = searchNode(k);
    if (x == nil) return 0;
    return rankSubtree(root, k);
}

/* Order Statistics. Returns the key of the node at  position pos in the tree.
 * Calling with pos = 1  should return the smallest key in the tree, pos = n
 * should return the largest. O(lg n) */
template <typename keytype, typename valuetype>
keytype RBTree<keytype, valuetype>::select(int pos) {
    return selectNode(root, pos)->key;
}

/* Returns a pointer to the key after k in the tree.  Should return NULL if no
 * successor exists. O(lg n) */
template <typename keytype, typename valuetype>
keytype *RBTree<keytype, valuetype>::successor(keytype k) {
    auto *node = searchNode(k);
    if (node == nil) return NULL;
    auto *next = findNext(node);
    if (next == nil) {
        return NULL;
    }
    return &next->key;
}

/* Returns a pointer to the key before k in the tree.  Should return NULL if no
 * predecessor exists. O(lg n) */
template <typename keytype, typename valuetype>
keytype *RBTree<keytype, valuetype>::predecessor(keytype k) {
    auto *node = searchNode(k);
    if (node == nil) return NULL;
    auto *prev = findPrev(node);
    if (prev == nil) {
        return NULL;
    }
    return &prev->key;
}

/* returns the number of nodes in the tree.
 * O(1) */
template <typename keytype, typename valuetype>
int RBTree<keytype, valuetype>::size() {
    return num_nodes;
}

/* Prints the keys of the tree in a preorder traversal. The list of keys are
 * separated by a single space  and terminated with a newline. O(n) */
template <typename keytype, typename valuetype>
void RBTree<keytype, valuetype>::preorder() {
    printPreorder(root);
    std::cout << std::endl;
}

/* Prints the keys of the tree in a inorder traversal. The list of keys are
 * separated by a single space  and terminated with a newline. O(n) */
template <typename keytype, typename valuetype>
void RBTree<keytype, valuetype>::inorder() {
    printInorder(root);
    std::cout << std::endl;
}

/* Prints the keys of the tree in a postorder traversal. The list of keys are
 * separated by a single space  and terminated with a newline. O(n) */
template <typename keytype, typename valuetype>
void RBTree<keytype, valuetype>::postorder() {
    printPostorder(root);
    std::cout << std::endl;
}

/* Prints the smallest k keys in the tree. The list of  keys are separated by a
 * single space and  terminated with a newline. O(k + lg n) */
template <typename keytype, typename valuetype>
void RBTree<keytype, valuetype>::printk(int k) {
    if (k > 0) {
        auto *first = treeMin(root);
        std::cout << first->key;
        auto *cur = first;
        for (int i = 0; i < k - 1; i++) {
            auto *next = findNext(cur);
            std::cout << " " << next->key;
            cur = next;
        }
    }
    std::cout << std::endl;
}
#endif