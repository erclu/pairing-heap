#include <iostream>

#include "pheap.hpp"
// TODO: have i removed non essentials?
// TODO!! convert everything to LF
using std::cin;
using std::cout;
using std::endl;

void decreaseSomeKeys();
void trackFillAndEmptyMinified();

// todo: smart pointers for nodes?
int main(int argc, char *argv[]) {
    // decreaseSomeKeys();

    trackFillAndEmptyMinified();

    return 0;
}

void trackFillAndEmptyMinified() {
    int n;
    cin >> n;
    PHeap<> heap;
    int temp;

    cout << "{\"n\":" << n << ",\"steps\":[" << endl;

    while (n-- > 0) {
        cin >> temp;
        heap.insert(temp);
        cout << heap.toMinifiedLeveledJson();
        if (n > 0) cout << ",";
        cout << endl;
    }

    cout << "],\"extraction steps\":[";

    while (!heap.isEmpty()) {
        if (!heap.isValid()) throw std::logic_error("lost a parent pointer");

        cout << "{\"pheap\":" << heap.toMinifiedLeveledJson() << ",";
        cout << "\"extracted\":\"" << heap.removeMin() << "\"}";
        if (!heap.isEmpty()) cout << ",";
        cout << endl;
    }
    cout << "]}";
}

void decreaseSomeKeys() {}