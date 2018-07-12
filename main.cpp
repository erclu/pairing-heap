#include <iostream>

#include "pheap.h"

using std::cin;
using std::cout;
using std::endl;

// todo: smart pointers for nodes..
// TODO: check if copy constructor & assignment work

int main(int argc, char *argv[]) {
    PHeap<> heap;
    int n, temp;
    cin >> n;

    cout << "{" << endl
         << "  \"n\": " << n << "," << endl
         << "  \"steps\": [" << endl;

    while (n-- > 0) {
        cin >> temp;
        heap.insert(temp);
        cout << heap.toLeveledJson(4);
        if (n > 0) cout << ",";
        cout << endl;
    }

    cout << "  ]," << endl << "  \"extraction steps\": [ ";

    while (!heap.isEmpty()) {
        cout << "{" << endl
             << "      \"pheap\": " << endl
             << heap.toLeveledJson(6) << "," << endl;
        cout << "      \"extracted\": \"" << heap.extractMin() << "\"" << endl
             << "}";
        if (!heap.isEmpty()) cout << ",";
        cout << endl;
    }
    cout << "  ]" << endl << "}";
    return 0;
}