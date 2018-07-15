#include <iostream>

#include "pheap.h"

using std::cin;
using std::cout;
using std::endl;

void trackFillAndEmptyMinified();

// todo: smart pointers for nodes..
int main(int argc, char *argv[]) {

int main(int argc, char *argv[]) {

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
        cout << "{\"pheap\":" << heap.toMinifiedLeveledJson() << ","
             << "\"extracted\":\"" << heap.extractMin() << "\"}";
        if (!heap.isEmpty()) cout << ",";
        cout << endl;
    }
    cout << "]}";
}