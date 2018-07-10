#include <iostream>

#include "pheap.h"

using std::cin;
using std::cout;
using std::endl;

int main(int argc, char *argv[]) {
    // cout << "------------------" << endl;

    // // clang-format off
    // Node<> *n = new Node<>(1,                    \
    //             new Node<>(2, 0, new Node<>(3,   \
    //                              new Node<>(4))));
    // // clang-format on
    // cout << n->toJSON() << endl;

    PHeap<> heap;

    int n, temp;
    cin >> n;

    // cout << "{" << endl
    //      << "\"n\": " << n << ", " << endl
    //      << "\"steps\": [" << endl;

    while (n-- > 0) {
        cin >> temp;
        heap.insert(temp);
        // cout << heap.toJSON();
        // if (n > 0) cout << ",";
        // cout << endl;
    }
    // cout << "]" << endl << "}";

    // cout << heap.toJSON() << endl;

    cout << heap.extractMin() << endl;
    cout << heap.extractMin() << endl;
    // while (!heap.isEmpty()) cout << heap.extractMin() << " " << endl;

    return 0;
}