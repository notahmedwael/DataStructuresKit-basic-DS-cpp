#include <iostream>
using namespace std;

template<class T>
class Stack {
private:
    struct Node {
        T item;
        Node* next;
    };
    Node* top;
    int size;

public:
    // default constructor
    Stack():top(nullptr), size(0) {}

    // method to check if stack is empty
    bool empty() {
        return size == 0;
    }

    // method to push element to the top of stack
    void push(T element) {
        Node* newItem = new Node;
        if (newItem == nullptr) { // if we run out of memory space or something
            cout << "Stack push cannot allocate memory." << endl;
            return;
        } else {
            newItem->item = element;
            newItem->next = top;
            top = newItem;
            size++;
        }
    }

    //  method to pop an element from the top of the stack
    void pop() {
        if (empty()) {
            cout << "Stack empty." << endl;
            return;
        } else {
            Node* temp = top;
            top = top->next;
            delete temp;
            size--;
        }
    }

    //  method that returns the top element in the stack without removing it
    T Top() {
        if (empty()) {
            cout << "Stack empty." << endl;
            return T();
        } else {
            return top->item;
        }
    }

    //  method that returns the current size of the stack
    int Size(){
        return size;
    }

    void reverse() { // we wil keep saving the top element in a temp and popping the elements in recursive calls, 
    //  then at the end the recursive calls unwind, and we insert at the bottom of the stack the top element from original order.
        if (!empty()) {
            T temp = Top();
            pop();
            reverse();
            insertBottom(temp);
        }
    }

    //   the method that inserts at bottom in recursive calls after the reverse method pops all elements and saves them in temp
    void insertBottom(T item) {
        if (empty()) {
            push(item);
        } else {
            T temp = Top();
            pop();
            insertBottom(item);
            push(temp);
        }
    }

    // method that removes middle element in a stack
    void deleteMiddle() {
        if (empty()) {
            return;
        }
        int middleIndex = size / 2; //  index of middle 
        Node* current = top; // we will use two pointers, one ahead of the other so we can delete a node in the middle without losing the links
        Node* prev = nullptr;
        for (int i = 0; i < middleIndex; i++) {
            prev = current;
            current = current->next;
        }
        if (prev){ // if the node does not point to null, which means the stack isn't empty, we set the next node of the element before middle to be the next to the middle
            prev->next = current->next;
            delete current; // delete middle node safely now after moving links
        }
        size--;
    }
};

int main() {
    Stack<int> s;
    for (int i = 1; i <= 10; i++)
    {
        s.push(i);
    }

    // 1 2 3 4 5 6 7 8 9 10
    // printing orignal stack then repushing it to stack
    cout << "Original stack: " << endl;
    while (!s.empty()) {
        cout << s.Top() << " ";
        s.pop();
    }
    cout << endl;

    for (int i = 1; i <= 10; i++)
    {
        s.push(i);
    }
    // 1 2 3 4 5 6 7 8 9 10

    s.reverse();
    cout << "Reversed stack: " << endl;
    while (!s.empty()) {
        cout << s.Top() << " ";
        s.pop();
    }
    cout << endl;

    // print reversed stack then repush it in the same order
    for (int i = 10; i >= 1; i--)
    {
        s.push(i);
    }

    s.deleteMiddle();
    cout << "Stack after deleting middle node: " << endl;
    while (!s.empty()) {
        cout << s.Top() << " ";
        s.pop();
    }
    cout << endl;
    
    return 0;
}