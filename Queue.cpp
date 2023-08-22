#include <iostream>
#include <queue>
#include <climits>

using namespace std;

// Method to generate binary numbers between 1 and n using queue with string
void generateBinary(int n)
{
    queue<string> q;
    //create a queue and then push 1 because whenver this method is called it's from to n
    q.push("1");
 
    
    for(int i = 1; i <= n; i++){
        q.push(q.front() + "0"); // append 0 to the string to get following element and push it to the queue
        q.push(q.front() + "1");// append 0 to the string to get the following element and push it the queue
 
        // print the front then pop/dequeue
        cout << q.front() << ' ';
        q.pop();
    }
}


// Function to find the index of the minimum element in the queue up to a given sortedIndex
int minIndex(queue<int> &q, int sortedIndex) {
    int min_index = -1;
    int min_val = INT_MAX;
    int n = q.size();
    for (int i = 0; i < n; i++) {
        int curr = q.front();
        q.pop(); // Remove the front element

        if (curr <= min_val && i <= sortedIndex) {
            min_index = i;
            min_val = curr;
        }
        q.push(curr); // Repush the element
    }
    return min_index;
}

// Function to move the minimum element at min_index to the end of the queue
void pushMinToEnd(queue<int> &q, int min_index) {
    int min_val;
    int n = q.size();
    for (int i = 0; i < n; i++) {
        int curr = q.front();
        q.pop();

        if (i != min_index)
            q.push(curr); // Repush all elements except the minimum
        else
            min_val = curr; // Store the minimum value
    }
    q.push(min_val); // Repush the minimum value to the end
}

// Function to sort the queue in ascending order, on each iteration we have moved an element to the end
// of the queue sorted in its correct place, it's like selection sort but at the end of the queue and on each iteration we look to size - i beacuse 
// on each iteration a new element is sorted at the end
void sortQueue(queue<int> &q) {
    for (int i = 1; i <= q.size(); i++) {
        int min_index = minIndex(q, q.size() - i);
        pushMinToEnd(q, min_index);
    }
}

int main() {
    int binarySize = 0;
    cout << "Enter N to generate binary numbers from 1 to N using queue: ";
    cin >> binarySize;
    generateBinary(binarySize);
    cout << endl;
    
    queue<int> q;
    int queueSize = 0;
    bool isPushed = false;
    cout << "Enter the number of elements will you push / enqueue to the queue: ";
    cin >> queueSize;
    for (int i = 0; i < queueSize; i++)
    {
        int value;
        cout << "Enter element to push: ";
        cin >> value;
        q.push(value);
        isPushed = true;
    }
    if(isPushed){
    cout << "Elements pushed successfully to the queue." << endl;
    }

    // make a copy of the queue to print how it looks before and after sort
    queue<int> qCopy = q;
    cout << "Queue before sort: " << endl;
    while (!qCopy.empty()) {
        cout << qCopy.front() << " ";
        qCopy.pop();
    }
    cout << endl;

    // Sort the queue
    sortQueue(q);


    // Print the sorted queue
    cout << "Queue after sorting: " << endl;
    while (!q.empty()) {
        cout << q.front() << " ";
        q.pop();
    }
    cout << endl;
    return 0;
}