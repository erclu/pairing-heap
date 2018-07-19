#ifndef PHEAP_H
#define PHEAP_H

#include <iostream> //necessary?
#include <stdexcept>

#include "Node.h"
#include "not_implemented.h"

using std::cerr;
// using std::cin;
using std::cout;
using std::endl;

template <class T>
class PHeap;

template <class T>
std::ostream &operator<<(std::ostream &os, const PHeap<T> &n);

template <class T>
class PHeap {
   private:
    Node<T> *root;

    /* merge: compare the two root elements, the smaller remains the root of
     * the result, the larger element and its subtree is appended as a child of
     * this root.
     * theta(1) */
    static Node<T> *merge(Node<T> *n1, Node<T> *n2);
    static Node<T> *merge(PHeap<T> *p1, PHeap<T> *p2);

    /* auxiliary function for extracting min */
    static Node<T> *mergePairs(Node<T> *first);

   public:
    PHeap() : root(NULL) { cerr << "PHeap()" << endl; }
    PHeap(Node<T> *r);
    ~PHeap();

    bool isEmpty() const { return root == NULL; }
    bool isValid() const;

    /* find min: return the top element of the heap.
     * theta(1) */
    T findMin() const;

    /* insert: create a new heap for the inserted element and merge into the
     * original heap.
     * theta(1) */
    void insert(T i);

    /* extract min: remove the root and merge its subtrees. Various strategies
     * are employed.
     * O(log(n)) amortized */
    T removeMin();

    /* find key: find node with info==value, returns reference to it.
     * ?? less than O(n): not exploring sub heaps with root bigger than key */
    Node<T> *&findKey(T value);

    /* decrease key: remove the subtree rooted at the key to be decreased,
     * replace the key with a smaller key, then merge the result back into
     * the heap.
     * lower bound omega(log(log(n))), upper O(2^(2*sqrt(log(log(n)))))
     * o(log(n)) amortized */
    void decreaseKey(Node<T> *&n, T delta);
    void decreaseKey(T value, T delta);

    friend std::ostream &operator<<<T>(std::ostream &os, const PHeap<T> &n);
    std::string toJson(unsigned int indent = 0) const;
    std::string toLeveledJson(unsigned int indent = 0) const;
    std::string toMinifiedLeveledJson() const;
};

#include "pheap.tcc"

#endif