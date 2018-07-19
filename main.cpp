#include <iostream>

#include "pheap.h"

using std::cin;
using std::cout;
using std::endl;

void checkNodeCopyConstructorAndAssignment();
void checkPHeapCopyConstructorAndAssignment();
void decreaseSomeKeys();
void trackFillAndEmptyMinified();

// todo: smart pointers for nodes?
int main(int argc, char *argv[]) {
    checkNodeCopyConstructorAndAssignment();

    checkPHeapCopyConstructorAndAssignment();

    // decreaseSomeKeys();

    // trackFillAndEmptyMinified();

    return 0;
}

void checkNodeCopyConstructorAndAssignment() {
    cerr << "---checkNodeCopyConstructorAndAssignment()---" << endl;
    //    1
    //   2  3
    //  6  4 5
    // 7
    Node<> n1(
      1, new Node<>(2, new Node<>(6, new Node<>(7)),
                    new Node<>(3, new Node<>(4, nullptr, new Node<>(5)))));

    Node<> n2 = n1;
    Node<> n3;
    n3 = n1;

    cout << endl
         << "---Parent pointers validation---" << endl
         << "n1 valid: " << n1.hasValidChilds() << endl
         << "n2 valid: " << n2.hasValidChilds() << endl
         << "n3 valid: " << n3.hasValidChilds() << endl
         << "--------------------------------" << endl;

    // cout << "n2-------------------------------" << endl
    //      << n2.toLeveledJson() << endl;
    // cout << "n3-------------------------------" << endl
    //      << n3.toLeveledJson() << endl
    //      << "---------------------------------" << endl;
}

void checkPHeapCopyConstructorAndAssignment() {
    cerr << "---checkPHeapCopyConstructorAndAssignment()--" << endl;

    int array[5] = {3, 2, 4, 1, 5};
    PHeap<> heap1;
    for (int i = 0; i < 5; i++) heap1.insert(array[i]);
    //  1
    // 5  2
    //   4 3

    cout << heap1 << endl;

    PHeap<> heap2 = heap1;
    PHeap<> heap3;
    heap3 = heap1;

    cout << endl
         << "---Parent pointers validation---" << endl
         << "heap1 valid: " << heap1.isValid() << endl
         << "heap2 valid: " << heap2.isValid() << endl
         << "heap3 valid: " << heap3.isValid() << endl
         << "--------------------------------" << endl;

    while (!(heap1.isEmpty() && heap2.isEmpty() && heap3.isEmpty())) {
        int t1 = heap1.removeMin(), t2 = heap2.removeMin(),
            t3 = heap3.removeMin();
        if (!(t1 == t2 && t1 == t3)) cout << "AAAAAAAAAAAAAAAH" << endl;
    }
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