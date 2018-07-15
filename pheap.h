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
    static Node<T> *merge(PHeap<T> *p1, PHeap<T> *p2);
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

    void decreaseKey(Node<T> *&n, T delta);
    /* decrease key (optional): remove the subtree rooted at the key to be
     * decreased, replace the key with a smaller key, then merge the result
     * back into the heap.
     * o(log(n)) amortized */
};

#include "pheap.tcc"

#endif