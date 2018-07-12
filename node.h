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

    Node();
    Node(T i);
    Node(T i, Node<T> *c, Node<T> *s = 0);

    Node(const Node &other);
    Node<T> &operator=(const Node<T> &other);

    ~Node();

    friend std::ostream &operator<<<T>(std::ostream &os, const Node<T> &n);

    std::string toJson(size_t indent = 0) const;
    std::string toLeveledJson(size_t indent = 0) const;
    std::string toMinifiedLeveledJson() const;

    const T info() const { return _info; }

    // static Node *buildList(int n = 0);
};

template <class T>
Node<T>::Node() : _info(), child(0), sibling(0), hasSibling(false) {
    cerr << "Node()" << endl;
}

template <class T>
Node<T>::Node(T i) : _info(i), child(0), sibling(0), hasSibling(false) {
    cerr << "Node(T i), i is: " << i << endl;
}

template <class T>
Node<T>::~Node() {
    cerr << "~Node()" << endl;
    delete child;

    if (hasSibling) delete sibling;
}

template <class T>
Node<T>::Node(T i, Node<T> *c, Node<T> *s) : _info(i), child(c), sibling(s) {
    cerr << "Node(T i, Node<T> *c, Node<T> *s), i is " << i << endl;

    if (sibling)
        hasSibling = true;
    else
        hasSibling = false;

    if (child) {
        Node<T> *n = child;
        while (n->hasSibling) n = n->sibling;
        n->sibling = this;
    }
}

template <class T>
Node<T>::Node(const Node<T> &other)
    : _info(other._info), child(0), sibling(0), hasSibling(other.hasSibling) {
    cerr << "Node(const Node<T> &other)" << endl;

    if (other.child) child = new Node<T>(other.child);
    if (other.sibling) sibling = new Node<T>(other.sibling);
} // TODO: check if copy constructor & assignment work

template <class T>
Node<T> &Node<T>::operator=(const Node<T> &other) {
    cerr << "operator=(const Node<T> &other)" << endl;

    if (this == &other) return *this;

    Node<T> *n = new Node<T>(other);
    return *n;
} // TODO: check if copy constructor & assignment work

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
std::string Node<T>::toJson(size_t indent) const {
    std::stringstream ss;

    ss << std::string(indent, ' ') << "{" << endl;
    indent += JSON_INDENT_SIZE;
    ss << std::string(indent, ' ') << "\"value\": \"" << _info << "\"";
    if (child) {
        ss << "," << endl;
        ss << std::string(indent, ' ')
           << "\"child\": " << child->toJson(indent);
    }
    if (sibling) {
        ss << "," << endl;
        ss << std::string(indent, ' ') << "\"sibling\": ";
        if (hasSibling)
            ss << sibling->toJson(indent);
        else
            ss << "\"to parent\"";
    }
    ss << endl;
    indent -= JSON_INDENT_SIZE;
    ss << std::string(indent, ' ') << "}";

    return ss.str();
}

template <class T>
std::string Node<T>::toLeveledJson(size_t indent) const {
    std::stringstream ss;

    ss << std::string(indent, ' ') << "{" << endl;
    indent += JSON_INDENT_SIZE;
    ss << std::string(indent, ' ') << "\"value\": \"" << _info << "\"";
    if (child) {
        ss << "," << endl;
        ss << std::string(indent, ' ') << "\"children\": [" << endl;
        indent += JSON_INDENT_SIZE;
        ss << child->toLeveledJson(indent);
        indent -= JSON_INDENT_SIZE;
        ss << endl << std::string(indent, ' ') << "]";
    }
    ss << endl;
    indent -= JSON_INDENT_SIZE;
    ss << std::string(indent, ' ') << "}";

    if (hasSibling) {
        ss << "," << endl;
        ss << sibling->toLeveledJson(indent);
    }

    return ss.str();
}

template <class T>
std::string Node<T>::toMinifiedLeveledJson() const {
    std::stringstream ss;

    ss << "{"
       << "\"value\":\"" << _info << "\"";
    if (child)
        ss << ","
           << "\"children\":[" << child->toMinifiedLeveledJson() << "]";

    ss << "}";
    if (hasSibling) ss << "," << sibling->toMinifiedLeveledJson();

    return ss.str();
}

#endif