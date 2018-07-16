template <class T>
Node<T>::Node(T i, Node<T> *c, Node<T> *s) : _info(i), child(c), sibling(s) {
    cerr << "Node(T i, Node<T> *c, Node<T> *s), i is " << i << endl;

    if (child) child->parent() = this;

    if (sibling)
        hasSibling = true;
    else
        hasSibling = false;
}

template <class T>
Node<T>::Node(const Node<T> &other)
    : _info(other._info),
      child(nullptr),
      sibling(nullptr),
      hasSibling(other.hasSibling) {
    cerr << "Node(const Node<T> &other)" << endl;

    if (other.child) {
        child = new Node<T>(*other.child);
        child->parent() = this;
    }

    if (other.sibling && hasSibling) sibling = new Node<T>(*other.sibling);
}

template <class T>
Node<T> &Node<T>::operator=(const Node<T> &other) {
    cerr << "operator=(const Node<T> &other)" << endl;

    if (this != &other) {
        cerr << "|------" << endl;
        _info = other._info;

        delete child;
        if (other.child) child = new Node<T>(*other.child);
        child->parent() = this;

        if (hasSibling) delete sibling;
        hasSibling = other.hasSibling;
        if (other.hasSibling) sibling = new Node<T>(*other.sibling);

        cerr << "------|" << endl;
    }
    return *this;
}

template <class T>
Node<T>::~Node() {
    cerr << "~Node()" << endl;
    delete child;

    if (hasSibling) delete sibling;
}

template <class T>
bool Node<T>::hasValidParent() const {
    // TODO is this necessary?
    if (!sibling) return false;

    Node<T> *n = this->parent()->child; // go to the first sibling

    while (n != this && hasSibling) n = n->sibling;

    return n == this;
}

template <class T>
bool Node<T>::hasValidChilds() const {
    if (!child) return true;

    if (!child->hasSibling) return child->sibling == this;

    return child->hasValidChilds() && child->sibling->hasValidChilds();
}

template <class T>
Node<T> *&Node<T>::parent() {
    // "this" must point to a valid object???
    if (!sibling) { // TODO: what happens if this has no sibling?
        cerr << "parent() on a root node" << endl;
        return sibling;
    }

    Node<T> *n = this;
    while (n->hasSibling) n = n->sibling;
    return n->sibling;
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
std::string Node<T>::toJson(size_t indent) const {
    std::stringstream ss;

    ss << std::string(indent, ' ') << "{" << endl;
    indent += JSON_INDENT_SIZE;
    ss << std::string(indent, ' ') << "\"info\": \"" << _info << "\"";
    if (child) {
        ss << "," << endl;
        ss << std::string(indent, ' ')
           << "\"child\": " << child->toJson(indent);
    }
    if (hasSibling) {
        ss << "," << endl;
        ss << std::string(indent, ' ')
           << "\"sibling\": " << sibling->toJson(indent);
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
    ss << std::string(indent, ' ') << "\"info\": \"" << _info << "\"";
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

    ss << "{\"info\":\"" << _info << "\"";
    if (child)
        ss << ","
           << "\"children\":[" << child->toMinifiedLeveledJson() << "]";

    ss << "}";
    if (hasSibling) ss << "," << sibling->toMinifiedLeveledJson();

    return ss.str();
}
