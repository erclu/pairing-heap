#ifndef NODE_H
#define NODE_H

#define JSON_INDENT_SIZE 2

#include <iostream>
#include <sstream>

#include "not_implemented.h"

using std::cerr;
// using std::cin;
using std::cout;
using std::endl;
using std::string;

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

    Node() : _info(), child(0), sibling(0), hasSibling(false) {
        cerr << "Node()" << endl;
    }
    Node(T i) : _info(i), child(0), sibling(0), hasSibling(false) {
        cerr << "Node(T i), i is: " << i << endl;
    }
    Node(T i, Node<T> *c, Node<T> *s = 0);

    ~Node() {
        cerr << "~Node()" << endl;
        delete child;

        if (hasSibling) delete sibling;
    }

    Node(const Node &other);
    Node<T> &operator=(const Node<T> &other);

    friend std::ostream &operator<<<T>(std::ostream &os, const Node<T> &n);

    string toJSON(size_t indent = 0) const;

    const T info() const { return _info; }

    // static Node *buildList(int n = 0);
};

template <class T>
Node<T>::Node(T i, Node<T> *c, Node<T> *s)
    : _info(i), child(c), sibling(s), hasSibling(false) {
    cerr << "Node(T i, Node<T> *c, Node<T> *s), i is " << i << endl;

    if (child) {
        Node<T> *n = child;
        while (n->sibling) {
            // TODO: probably redundant; every node except this->child should
            // have the hasSibling property already up to date
            n->hasSibling = true;
            n = n->sibling;
        }
        n->sibling = this;
    }
}

template <class T>
Node<T>::Node(const Node<T> &other) {
    cerr << "Node(const Node<T> &other)" << endl;
    throw NotImplemented(); // TODO

    // _info = other._info;
    // hasSibling = other.hasSibling;

    // if (other.child)
    //     child = new Node<T>(other.child);
    // else
    //     child = 0;

    // if (other.sibling)
    //     sibling = new Node<T>(other.sibling);
    // else
    //     sibling = 0;
}

template <class T>
Node<T> &Node<T>::operator=(const Node<T> &other) {
    cerr << "operator=(const Node<T> &other)" << endl;
    throw NotImplemented(); // TODO
    // Node<T> *n = new Node<T>(other._info, new Node<T>(other.child),
    //                          new Node<T>(other.sibling));

    // return *n;
}

template <class T>
std::ostream &operator<<(std::ostream &os, const Node<T> &n) {
    os << n._info << "(|";

    if (n.child)
        os << *(n.child);
    else
        os << "_";

    os << ",-";

    if (n.hasSibling)
        os << *(n.sibling);
    else
        os << "_";

    os << ")";
    return os;
}

template <class T>
string Node<T>::toJSON(size_t indent) const {
    std::stringstream ss;

    ss << "{" << endl;
    indent += JSON_INDENT_SIZE;
    // TODO: print all siblings to same level
    ss << string(indent, ' ') << "\"value\": \"" << _info << "\"";
    if (child) {
        ss << "," << endl;
        ss << string(indent, ' ') << "\"child\": " << child->toJSON(indent);
    }
    if (sibling) {
        ss << "," << endl;
        ss << string(indent, ' ') << "\"sibling\": ";
        if (hasSibling)
            ss << sibling->toJSON(indent);
        else
            ss << "\"to parent\"";
    }
    ss << endl;
    indent -= JSON_INDENT_SIZE;

    ss << string(indent, ' ') << "}";
    return ss.str();
}

#endif