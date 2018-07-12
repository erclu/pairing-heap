#ifndef PHEAP_H
#define PHEAP_H

#include <iostream>
#include <stdexcept>

#include "Node.h"
#include "not_implemented.h"

using std::cerr;
// using std::cin;
using std::cout;
using std::endl;

template <class T = int>
class PHeap;

template <class T>
std::ostream &operator<<(std::ostream &os, const PHeap<T> &n);

template <class T>
class PHeap {
   private:
    Node<T> *root;

    static Node<T> *merge(Node<T> *n1, Node<T> *n2);
    /* merge: compare the two root elements, the smaller remains the root of
     * the result, the larger element and its subtree is appended as a child of
     * this root.
     * theta(1) */
    static Node<T> *mergePairs(Node<T> *first);
    /* auxiliary function for extracting min */

   public:
    PHeap() : root(NULL) { cerr << "PHeap()" << endl; }
    PHeap(T i);
    PHeap(Node<T> *r);
    PHeap(const PHeap<T> &other);
    PHeap<T> &operator=(const PHeap<T> &other);

    ~PHeap();

    friend std::ostream &operator<<<T>(std::ostream &os, const PHeap<T> &n);
    std::string toJson(size_t indent = 0) const;
    std::string toLeveledJson(size_t indent = 0) const;

    bool isEmpty() const { return root == NULL; }

    T findMin() const;
    /* find min: return the top element of the heap.
     * theta(1) */

    void insert(T i);
    /* insert: create a new heap for the inserted element and merge into the
     * original heap.
     * theta(1) */

    T extractMin();
    /* extract min: remove the root and merge its subtrees. Various strategies
     * are employed.
     * O(log(n)) amortized */

    void decreaseKey(Node<T> *n, T delta);
    /* decrease key (optional): remove the subtree rooted at the key to be
     * decreased, replace the key with a smaller key, then merge the result
     * back into the heap.
     * o(log(n)) amortized */
};

template <class T>
Node<T> *PHeap<T>::merge(Node<T> *n1, Node<T> *n2) {
    if (!n1) return n2;
    if (!n2) return n1;

    // pointers for nodes with smaller and larger value
    Node<T> *smaller, *larger;

    if (n1->info() <= n2->info()) {
        smaller = n1;
        larger = n2;
    } else {
        smaller = n2;
        larger = n1;
    }

    // pheap root nodes never have siblings ????
    larger->sibling = smaller->child;
    if (larger->sibling) {
        larger->hasSibling = true;
    } else {
        larger->hasSibling = false;
        larger->sibling = smaller;
    }
    smaller->child = larger;
    larger = 0; // empty other heap; ??????
    return smaller;
}

// PRE: first è un nodo ben formato e non nullo;
template <class T>
Node<T> *PHeap<T>::mergePairs(Node<T> *first) {
    if (!first) return 0;
    if (!first->hasSibling) return first;

    Node<T> *second = first->sibling;
    first->sibling = 0;
    first->hasSibling = false;

    Node<T> *remaining = 0;
    if (second->hasSibling) {
        remaining = second->sibling;
        second->sibling = 0;
        second->hasSibling = false;
    }
    Node<T> *pair = merge(first, second);

    return merge(pair, mergePairs(remaining));
}

// ------------------- PUBLIC -------------------

template <class T>
PHeap<T>::PHeap(T i) {
    cerr << "PHeap(T i) + ";
    root = new Node<T>(i);
}

template <class T>
PHeap<T>::PHeap(Node<T> *r) : root(r) {
    // should act as converter from Node<T> to PHeap<T>
    cerr << "PHeap(Node<T> *r)" << endl;
    // TODO: check if it works without this
    root->hasSibling = false; // lazily forget siblings of root...
}

template <class T>
PHeap<T>::PHeap(const PHeap<T> &other) {
    cerr << "PHeap(const PHeap<T> &other)" << endl;

    root = new Node<T>(other.root);
}

template <class T>
PHeap<T> &PHeap<T>::operator=(const PHeap<T> &other) {
    cerr << "operator=(const PHeap<T> &other)" << endl;

    if (this == &other) return *this;

    PHeap<T> *n = new PHeap(other);
    return *n;
}

template <class T>
PHeap<T>::~PHeap() {
    cerr << "~PHeap()";
    if (isEmpty()) {
        cerr << endl;
    } else {
        cerr << " + ";
        delete root;
    }
}

template <class T>
std::ostream &operator<<(std::ostream &os, const PHeap<T> &n) {
    os << n.root;
    return os;
}

template <class T>
std::string PHeap<T>::toJson(size_t indent) const {
    if (isEmpty())
        throw std::out_of_range("toJson() on empty pheap");
    else
        return root->toJson(indent);
}

template <class T>
std::string PHeap<T>::toLeveledJson(size_t indent) const {
    if (isEmpty())
        throw std::out_of_range("toLeveledJson() on empty pheap");
    else
        return root->toLeveledJson(indent);
}

template <class T>
T PHeap<T>::findMin() const {
    if (isEmpty())
        throw std::out_of_range("findMin() on empty pheap");
    else
        return root->info();
}

template <class T>
void PHeap<T>::insert(T i) {
    Node<T> *other = new Node<T>(i);

    root = merge(root, other);
}

template <class T>
T PHeap<T>::extractMin() {
    if (isEmpty()) throw std::out_of_range("extractMin() on empty heap");

    T min = findMin();

    Node<T> *tmp = root->child;
    root->child = 0;
    delete root;

    root = mergePairs(tmp);

    return min;
}

template <class T>
void PHeap<T>::decreaseKey(Node<T> *n, T delta) {
    throw NotImplemented(); // TODO
}

#endif