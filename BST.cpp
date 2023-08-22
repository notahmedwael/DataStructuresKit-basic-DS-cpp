#include <iostream>
#include <queue> // for breadthFirst search
#include <string>

using namespace std;

template <class T>
class BSTNode { // Node class that has left and right nodes so it makes a tree structure
public:
    BSTNode<T>* left;
    BSTNode<T>* right;
    T data;

    BSTNode(const T& value) : data(value), left(nullptr), right(nullptr) {}
};
    // template class Binary Search tree that uses an object of the template class BSTNode
template <class T>
class BST {
private:    // root node as a private member of the template class
    BSTNode<T>* root;

public:
    //  Default constructor that set the root to null when defining an object of the class
    BST() : root(nullptr) {}

    //  Method that searches for a value in the BST
    BSTNode<T>* searchBST(BSTNode<T>* node, const T& value) const {
        if (node == nullptr || node->data == value) { // If the node is pointing no nothing or we find the data we are looking for we return the node
            return node;
        }
        
        if (value < node->data) { // If the current node data is larger than the value we are looking for then we go left to find smaller data nodes
            return searchBST(node->left, value);
        } else {    //  if the value we are looking for is larger than the cuurent node then we go right to find larger data nodes
            return searchBST(node->right, value);
        }
    }
    
    //  Method that does breadfirst Search using queue
    void breadthFirst() {
        if (root == nullptr) {  //  If the tree is empty return outside the method
            return;
        }
        
        queue<BSTNode<T>*> q;
        q.push(root); // push the root of the tree to the queue

        while (!q.empty()) {  // Iterate over the tree level by level and add them to the queue then print them and pop them level by level
            BSTNode<T>* current = q.front();
            q.pop();
            cout << current->data << " ";

            if (current->left) {
                q.push(current->left);
            }
            if (current->right) {
                q.push(current->right);
            }
        }
    }

    // Method to call the insert a node in BST, this method start the process
    void insertBST(const T& value) {
        root = insertBST(root, value);
    }

    //  Method that takes the root as a parameter and the value to insert them in the correct place
    // It keeps going in the correct place in the tree and recursively calls itself to traverse through the tree until it 
    // Finds the correct place
    BSTNode<T>* insertBST(BSTNode<T>* node, const T& value) {
        if (node == nullptr) { // If the node is pointing to nothing (nullptr), then make a new Node with the value as its data and return it
                              //  This will happen when the tree is empty
            return new BSTNode<T>(value);
        }

        if (value < node->data) { //    If the current node is value is greater than the value we are trying to insert, then we go to the left node to find smaller elements
            node->left = insertBST(node->left, value);
        } else {    //  If the node current value is smaller than the value then we need to go right to find larger elements
            node->right = insertBST(node->right, value);
        }
        return node;   //   Finally return the node
    }

    //  Method to delete a node by its value, this method starts the process
    void DeleteBST(const T& value) {
        root = DeleteBST(root, value);
    }

    //  Recursively call the method until we find the value
    BSTNode<T>* DeleteBST(BSTNode<T>* node, const T& value) {
        if (node == nullptr) { // If the tree is empty or we couldn't find the value return the node the method is pointing to
            return node;
        }

        if (value < node->data) {   // If the current node is value is greater than the value we are trying to delete, then we go to the left node to find smaller elements
            node->left = DeleteBST(node->left, value);
        } else if (value > node->data) {   //  If the node current value is smaller than the value then we need to go right to find larger elements
            node->right = DeleteBST(node->right, value);
        } else {
            if (node->left == nullptr) {    //  If the node we are trying to delete has no left child, replace the node with its right child(might be nullptr)
                                            //  after that delete the node and return the right child
                BSTNode<T>* temp = node->right;
                delete node;
                return temp;
            } else if (node->right == nullptr) {//  If the node we are trying to delete has no right child, replace the node with its left child
                                            //  after that delete the node and return the left child
                BSTNode<T>* temp = node->left;
                delete node;
                return temp;
            }
            // Else if it has both left and right children, then we need to get the smallest node in the right subtree
            // we will do it using the minValueNode which gets the minumum noding given a tree to traverse it
            BSTNode<T>* temp = minValueNode(node->right);
            node->data = temp->data; // Replace the current node's data with the data of the minimum node
            node->right = DeleteBST(node->right, temp->data); // Recursively call DeleteBST with the right child, using the data of the minimum node as the value to be deleted from the right subtree
        }
        return node;    //  Finally return the node
    }

    //  The method gets the minumum noding given a tree to traverse it
    BSTNode<T>* minValueNode(BSTNode<T>* node) {
        BSTNode<T>* current = node;
        while (current && current->left) {
            current = current->left;
        }
        return current;
    }

    //  Return the root node
    BSTNode<T>* getRoot() {
        return root;
    }

    //  Print the tree in order
    void InOrder(BSTNode<T>* node) {
        if (node == nullptr) {
            return;
        }
        InOrder(node->left);
        cout << node->data << " ";
        InOrder(node->right);
    }
};

int main() {
    // Create an instance of the BST class
    BST<int> bst; 
    //  String literal to show the menu to the user
    string menu = R"(
            ==============================
                Menu For BST Operations
            ==============================
            1) Insert a node.
            2) Delete a node.
            3) Search by value.
            4) Breadth First Search(Level by level).
            5) In Order Print BST.
            6) Return the value of the minimum node in the BST.
            7) Exit.
        )";

    while (true) {
        cout << menu << "\n";
        cout << "Enter your choice: ";

        //  Get user's menu choice
        int choice;
        cin >> choice;

        //  Place holder for search result & minimum value
        BSTNode<int>* searchResult;
        BSTNode<int>* minValue;

        switch (choice) {
            case 1:
                cout << "Enter value to insert: ";
                int insertValue;
                cin >> insertValue;
                bst.insertBST(insertValue);
                cout << "Value inserted successfully.\n";
                break;

            case 2:
                cout << "Enter value to delete: ";
                int deleteValue;
                cin >> deleteValue;
                bst.DeleteBST(deleteValue);
                cout << "Value deleted successfully.\n";
                break;

            case 3:
                cout << "Enter value to search for: ";
                int searchValue;
                cin >> searchValue;
                searchResult = bst.searchBST(bst.getRoot(), searchValue);
                if (searchResult) {
                    cout << "Value found: " << searchResult->data << endl;
                } else {
                    cout << "Value not found.\n";
                }
                break;

            case 4:
                cout << "Breadth First Traversal: ";
                bst.breadthFirst();
                cout << endl;
                break;

            case 5:
                cout << "In Order Traversal: ";
                bst.InOrder(bst.getRoot());
                cout << endl;
                break;

            case 6:
                minValue = bst.minValueNode(bst.getRoot());
                if (minValue) {
                    cout << "Minimum value in the BST: " << minValue->data << endl;
                } else {
                    cout << "BST is empty.\n";
                }
                break;

            case 7:
                cout << "Thanks for using the program...\n";
                return 0;

            default:
                cout << "Invalid choice. Please enter a valid option.\n";
                break;
        }
    }
    return 0;
}