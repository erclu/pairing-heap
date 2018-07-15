
template <class T>
Node<T> *PHeap<T>::merge(Node<T> *n1, Node<T> *n2) {
    if (!n1) return n2;
    if (!n2) return n1;

    // pointers for nodes with smaller and larger _info
    Node<T> *smaller, *larger;

    if (n1->info() <= n2->info()) {
        smaller = n1;
        larger = n2;
    } else {
        smaller = n2;
        larger = n1;
    }

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

template <class T>
Node<T> *PHeap<T>::merge(PHeap<T> *p1, PHeap<T> *p2) {
    return merge(p1->root, p2->root);
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

    root = new Node<T>(*other.root);
    // TODO: parent pointers???
}

template <class T>
PHeap<T> &PHeap<T>::operator=(const PHeap<T> &other) {
    cerr << "operator=(const PHeap<T> &other)" << endl;

    if (this != &other) {
        cerr << "|------" << endl;
        delete root;
        root = new Node<T>(*other.root);
        cerr << "------|" << endl;
    }

    return *this;
}

template <class T>
PHeap<T>::~PHeap() {
    cerr << "~PHeap()" << endl;
    if (!isEmpty()) {
        cerr << "|------" << endl;
        delete root;
        cerr << "------|" << endl;
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
std::string PHeap<T>::toMinifiedLeveledJson() const {
    if (isEmpty())
        throw std::out_of_range("toMinifiedLeveledJson() on empty pheap");
    else
        return root->toMinifiedLeveledJson();
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

// PRE: delta > 0;
template <class T>
void PHeap<T>::decreaseKey(Node<T> *&n, T delta) {
    // TODO: check if decreasekey is correct

    Node<T> *decreased = new Node<T>(n->info() - delta, n->child);
    if (n == root) return;

    n = n->sibling;
    // if (n->hasSibling) { // useless????
    //     n = n->sibling;
    // } else {
    //     Node<T> *previous = n->parent()->child;

    //     if (previous == n) { // if n is the first child..
    //         previous = 0;
    //     } else {
    //         while (previous->sibling != n) previous = previous->sibling;

    //         previous->sibling = n->sibling;
    //     }
    // }

    root = merge(root, decreased);
}