#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <sstream>

#include "not_implemented.h"

#define JSON_INDENT_SIZE 2

using std::cerr;
// using std::cin;
using std::cout;
using std::endl;

// template <class T = int>
// class PHeap;

template <class T = int>
class Node;

template <class T>
std::ostream &operator<<(std::ostream &os, const Node<T> &n);

template <class T>
class Node {
   private:
    T _info;

   public:
    Node *child, *sibling;
    // sibling is the null pointer if and only if that node is a root;
    bool hasSibling;

    Node(T i = T(), Node<T> *c = 0, Node<T> *s = 0);

    Node(const Node &other);
    Node<T> &operator=(const Node<T> &other);

    ~Node();

    const T info() const { return _info; }
    Node<T> *parent();

    friend std::ostream &operator<<<T>(std::ostream &os, const Node<T> &n);

    std::string toJson(size_t indent = 0) const;
    std::string toLeveledJson(size_t indent = 0) const;
    std::string toMinifiedLeveledJson() const;
};

#include "node.tcc"

#endif