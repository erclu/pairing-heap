#ifndef NODE_H
#define NODE_H

#include <iostream> //necessary?
#include <sstream>

#include "not_implemented.h"

#define JSON_INDENT_SIZE 2

using std::cerr;
// using std::cin;
using std::cout;
using std::endl;

template <class T = int>
class PHeap;

template <class T = int>
class Node;

template <class T>
std::ostream &operator<<(std::ostream &os, const Node<T> &n);

template <class T>
class Node {
    friend class PHeap<T>;

   private:
    T _info;
    Node *child, *sibling;
    // sibling is the null pointer if and only if that node is a root;
    bool hasSibling;

    Node<T> *&parent();

    bool hasValidChilds() const;

   public:
    // TODO: new constructor with only basic stuff
    Node(T i = T(), Node<T> *c = nullptr, Node<T> *s = nullptr);
    ~Node();

    friend std::ostream &operator<<<T>(std::ostream &os, const Node<T> &n);
    std::string toJson(unsigned int indent = 0) const;
    std::string toLeveledJson(unsigned int indent = 0) const;
    std::string toMinifiedLeveledJson() const;

    const T info() const { return _info; }
};

#include "node.tcc"

#endif