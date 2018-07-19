// TODO: reorder methods in file...
template <class T>
Node<T> *&Node<T>::parent() {
    if (!sibling) { // TODO check why it's sometimes called on root nodes...
        cerr << "parent() on a root node, info is " << _info << endl;
        return sibling;
        // it should be able to set the correct parent in an unfinished node..
    }

    // if (!hasSibling) return sibling;
    // return sibling->parent(); // TODO: check if recursive version works...

    Node<T> *n = this;
    while (n->hasSibling) n = n->sibling;
    return n->sibling;
}

template <class T>
bool Node<T>::hasValidChilds() const {
    if (!child) return true;

    if (!child->hasSibling) return child->sibling == this;

    return child->hasValidChilds() && child->sibling->hasValidChilds();
}

template <class T>
Node<T>::Node(T i)
    : _info(i), child(nullptr), sibling(nullptr), hasSibling(false) {
    cerr << "Node(T i), _info is " << _info << endl;
}

template <class T>
Node<T>::~Node() {
    cerr << "~Node()" << endl;
    delete child;

    if (hasSibling) delete sibling;
}

template <class T>
std::ostream &operator<<(std::ostream &os, const Node<T> &n) {
    os << n._info << "(";

    if (n.child)
        os << *(n.child);
    else
        os << "_";

    os << ",";

    if (n.hasSibling)
        os << *(n.sibling);
    else
        os << "_";

    os << ")";
    return os;
}

template <class T>
std::string Node<T>::toJson(unsigned int indent) const {
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
std::string Node<T>::toLeveledJson(unsigned int indent) const {
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
