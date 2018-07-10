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
using std::string;

template <class T = int>
class PHeap;

template <class T>
std::ostream &operator<<(std::ostream &os, const PHeap<T> &n);

template <class T>
class PHeap {
   private:
    Node<T> *root;

    void merge(PHeap<T> *other);
    /* merge: compare the two root elements, the smaller remains the root of
     * the result, the larger element and its subtree is appended as a child of
     * this root.
     * theta(1) */
    static Node<T> *mergePairs(Node<T> *f);
    /* auxiliary function for extracting min */

   public:
    PHeap() : root(NULL) { cerr << "PHeap()" << endl; }
    PHeap(T i) {
        cerr << "PHeap(T i) + ";
        root = new Node<T>(i);
    }
    PHeap(Node<T> *r) : root(r) {
        // should act as converter from Node<T> to PHeap<T>
        cerr << "PHeap(Node<T> *r)" << endl;
        root->hasSibling = false; // lazily forget siblings of root...
    }

    PHeap(const PHeap<T> &other) {
        cerr << "PHeap(const PHeap<T> &other)" << endl;
        throw NotImplemented(); // TODO
    }
    PHeap<T> &operator=(const PHeap<T> &other) {
        cerr << "operator=(const PHeap<T> &other)" << endl;
        throw NotImplemented(); // TODO
    }

    ~PHeap() {
        cerr << "~PHeap() + ";
        delete root;
    }

    bool isEmpty() const { return root == NULL; }
    string toJSON() const { return root->toJSON(); }

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

    friend std::ostream &operator<<<T>(std::ostream &os, const PHeap<T> &n);
};

template <class T>
T PHeap<T>::findMin() const {
    if (isEmpty())
        throw std::out_of_range("findMin() on empty pheap");
    else
        return root->info();
}

// friend this?
template <class T>
void PHeap<T>::merge(PHeap<T> *other) {
    if (other->isEmpty()) return;

    if (isEmpty()) {
        root = other->root;
        other->root = 0; // empty other heap;
    } else {
        // pointers for heap with smaller and larger root value
        Node<T> *smaller, *larger;

        if (root->info() <= other->root->info()) {
            smaller = root;
            larger = other->root;
        } else {
            smaller = other->root;
            larger = root;
        }

        // pheap root nodes never have siblings!!
        larger->sibling = smaller->child;
        if (larger->sibling) {
            larger->hasSibling = true;
        } else {
            larger->hasSibling = false;
            larger->sibling = smaller;
        }
        smaller->child = larger;
        larger = 0; // empty other heap; ??????

        if (root != smaller) root = smaller;
    }
}

template <class T>
void PHeap<T>::insert(T i) {
    PHeap<T> *other = new PHeap<T>(i);

    merge(other);
}

template <class T>
T PHeap<T>::extractMin() {
    cerr << "TODO" << endl;
    throw NotImplemented();

    if (isEmpty()) throw std::out_of_range("extractMin() on empty heap");
}

template <class T>
void PHeap<T>::decreaseKey(Node<T> *n, T delta) {
    throw NotImplemented(); // TODO
}

template <class T>
std::ostream &operator<<(std::ostream &os, const PHeap<T> &n) {
    os << n.root;
    return os;
}

#endif