#include <iostream>

using namespace std;

template <class T>
class Node {
private:
    T info;
    Node* next;

public:
    explicit Node(T value, Node* n = nullptr);
    Node* getNext();
    void setNext(Node* n);
    T getInfo();
    void setInfo(T value);
};

template <class T>
class SLL {
private:
    Node<T>* head;
    Node<T>* tail;

public:
    SLL();
    void addToHead(T value);
    void addToTail(T value);
    T removeFromHead();
    T removeFromTail();
    T getValueAtHead();
    bool isEmpty();
    void clear();
    void swapPair();
    void unique();

    template<class M>
    friend ostream& operator<<(ostream& os, const SLL<M>& sll);
};

template <class T>
Node<T>::Node(T value, Node* n) : info(value), next(n) {}

template <class T>
Node<T>* Node<T>::getNext() {
    return next;
}

template <class T>
void Node<T>::setNext(Node* n) {
    next = n;
}

template <class T>
T Node<T>::getInfo() {
    return info;
}

template <class T>
void Node<T>::setInfo(T value) {
    info = value;
}

// SLL class implementation
template <class T>
SLL<T>::SLL() : head(nullptr), tail(nullptr) {}

template <class T>
bool SLL<T>::isEmpty() {
    return head == nullptr;
}

template <class T>
void SLL<T>::addToHead(T value) {
    Node<T>* newNode = new Node<T>(value, head);
    head = newNode;
    if (!tail) {    // if the tail is nullptr assign head to it
        tail = head;
    }
}

template <class T>
void SLL<T>::addToTail(T value) {
    Node<T>* newNode = new Node<T>(value);
    if (!head) {    // if the head is nullptr then assign newNode to head and tail
        head = newNode;
        tail = newNode;
    } else {        // else put the newNode as tail
        tail->setNext(newNode);
        tail = newNode;
    }
}

template <class T>
T SLL<T>::removeFromHead() {
    if (isEmpty()) {
        cout << "SLL is empty." << endl;
    }
    T value = head->getInfo();
    Node<T>* temp = head;
    head = head->getNext();
    delete temp;
    if (!head) {    // if the list is empty now after removal then assign tail to null ptr as well
        tail = nullptr;
    }
    return value;
}

template <class T>
T SLL<T>::removeFromTail() { // remove tail node and set the previous node as tail
    if (isEmpty()) {
       cout << "SLL is empty" << endl;
    }
    T value = tail->getInfo();
    if (head == tail) { // if only one element exists in the list then delete head and tail and assign their pointers to nullptr
        delete head;
        head = tail = nullptr;
    } else {
        Node<T>* temp = head;
        while (temp->getNext() != tail) {
            temp = temp->getNext();
        }
        delete tail;
        tail = temp;
        tail->setNext(nullptr);
    }
    return value;
}

template <class T>
T SLL<T>::getValueAtHead() { // return value at head without removing
    if (isEmpty()) {
        cout << "SLL is empty" << endl;
    }
    return head->getInfo();
}

template <class T>
void SLL<T>::swapPair() { // swap nodes pair wise
    Node<T>* current = head;
    while (current && current->getNext()) { // while the current node and the next to it are not pointing to nullptr, keep swapping pair wise
        T temp = current->getInfo();
        current->setInfo(current->getNext()->getInfo());
        current->getNext()->setInfo(temp);
        current = current->getNext()->getNext();
    }
}

template <class T>
void SLL<T>::clear() {
    while(head){    // while head does not point to nullptr
        Node<T>* temp = head;
        temp = head;
        head = head->getNext();
        delete temp;
    }
    tail = nullptr;
}

template <class T>
void SLL<T>::unique() { // remove duplicates from the list
    if (isEmpty()) {
        cout << "List is empty, cannot make it unique." << endl;
        return;
    }
    Node<T>* current = head;
    while (current) { // while the current node does not point to nullptr, we will compare it with the rest of the list, this loop runs once for each element in the list
        Node<T>* prev = current;
        while (prev->getNext()) {
            if (prev->getNext()->getInfo() == current->getInfo()) {// if we find a duplicate we edit the pointer of the prev to point to the element next to duplicate
                Node<T>* duplicate = prev->getNext();
                prev->setNext(duplicate->getNext());
                delete duplicate;
            } else {
                prev = prev->getNext();
            }
        }
        current = current->getNext();
    }
}

template <class T> // print the list using an object from friend class ostream
ostream& operator<<(ostream& os, const SLL<T>& sll) {
    Node<T>* current = sll.head;
    // we put a temp node at the head and start moving and printing till the end of the list(when the temp does not point to null)
    while (current) {
        os << current->getInfo() << " ";
        current = current->getNext();
    }
    os << endl;
    return os;
}
using namespace std;
int main() {
    SLL<int> list;
    cout << "Checking if list is empty (1-> true | 0->false): " << list.isEmpty() << endl; // prints 1 as list is empty
    list.addToHead(3);  // 3
    list.addToHead(5);  // 5 3
    list.addToTail(7);  // 5 3 7
    list.addToHead(5);  // 5 5 3 7
    list.addToTail(9);  // 5 5 3 7 9
    list.addToHead(7);  // 7 5 5 3 7 9
    list.addToTail(2);  // 7 5 5 3 7 9 2
    cout << "List after adding some elements: " << list;    // 7 5 5 3 7 9 2
    cout << "Checking if list is empty (1-> true | 0->false): " << list.isEmpty() << endl; // prints 0 as list isn't empty
    cout << "Element " << list.removeFromHead() << " removed from head of the list." << endl;   // prints 7
    cout << "Element " << list.removeFromTail() << " removed from tail of the list." << endl;   // prints 2
    cout << "List after head & tail removal: " << list; // 5 5 3 7 9
    list.swapPair();
    cout << "List after pair-wise swap: " << list; // 5 5 7 3 9
    list.unique();
    cout << "List after removing duplicates: " << list; // 5 7 3 9
    cout << "List head without removing: " << list.getValueAtHead() << endl; // prints 5
    list.clear();
    cout << "List after clear method: " << list; //prints nothing as it's empty
    SLL<int> list2;
    for (int i = 0; i < 5; i++)
    {
        list2.addToTail(1);
        list2.addToTail(2);
    }
    // list2: 1 2 1 2 1 2 1 2 1 2
    cout << "List 2: " << list2;
    list2.unique();
    cout <<"List 2 after making it unique: "<< list2;
    return 0;
}