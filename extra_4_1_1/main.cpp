/* - Create a program that prompts input from the user via a printed menu
    1. Insert Tree `node *insert()` (insert random integer)
    2. Search Tree `bool search()`(randomly)
    3. Print InOrder
    4. Exit Menu
    5. While (ans == yes)  the menu
*/


#include <iostream>
#include <string>
#include <random>
using namespace std;

struct Node {
    Node* left;
    Node* right;
    int data;
    Node(int val) : data(val), left(nullptr), right(nullptr) {}
};

Node* root = nullptr;

// First Option: Inserts a random node recursively
// ? Remove args for random node insertion ?
Node* insert(Node *currNode, int val) {
    cout << "Inserted value: " << val << endl;

    // Stop Condition: We are at a leaf, create a new node and return as a leaf node
    if (currNode == nullptr) {
        currNode = new Node(val);
    }
    // Left Child Case: If val is less than current node, recursively insert into the left subtree
    else if (val < currNode->data) {
        currNode->left = insert(currNode->left, val); // if not null then assigns to itself: OK
    // Right Child Case: If val is greater than current node, recursively insert into the right subtree
    } else if (val > currNode->data) {
        currNode->right = insert(currNode->right, val); // if not null then assigns to itself: OK
    } else {
        return; // Got an existing value: ignore it as it is already present
    }
    // currNode is returned to maintain the tree's structure during the recursion (updating the arg for insert())
    return currNode;
}

// Second Option: Searches for a key recursively
// Returns true if the value was present & found, false otherwise
bool search(Node *currNode, int key) {
	cout << "Searching for value: " << key << endl;
    
    // Base Case(s): 
    if (currNode == nullptr)
        return false;

	if (currNode->data == key) {
        return true;
    // Left Child Case: If key is less than current node's data, recursively search in the left subtree
    } else if (key < currNode->data) {
		return search(currNode->left, key);
    // Right Child Case: If key is greater than current node's data, recursively search in the right subtree
    } else if (key > currNode->data) {
        return search(currNode->right, key);
    }
    return true;
}

// Third Option: Prints the BST values in ascending order through recursive traversal
void printInOrder(Node* node) {
	// Base Case
    if (node == nullptr)
		return;

	// Traverses through all possible left subtrees first, then right
    printInOrder(node->left);
	cout << node->data << " ";
	printInOrder(node->right);

    return;
}

// Final Option: Exits the menu
void exit() {
    cout << "Exiting...\n" ;
    ::exit(0);  // Exit the program
}


// Menu should initialize the menu itself, prompt for input, etc.
void menu() {
    srand(time(NULL));        // Seeding for rand()
    string answer;

    while (answer != "4") {
        // Displaying the top border and menu
        cout << "                     - M E N U -                     "
        cout << "---------------------------------------------------\n";
        cout << "Please enter a number 1- 4 to make a selection:\n";
        cout << "1) Insert a random value into the tree.\n";
        cout << "2) Search for a specific value in the tree.\n";
        cout << "3) Print the tree in ascending order.\n";
        cout << "4) Exit menu.\n";
        cout << "---------------------------------------------------\n";
        cin >> answer;

        // Randomly inserting nodes into the tree
        if (answer == "1") {
            cout << "---------------------------------------------------\n";
            int val = rand() % 100 + 1;
            root = insert(root, val);
            cout << "Inserted value: " << val << endl;
            cout << "---------------------------------------------------\n";
        } else if (answer == "2") {             // Searching for the key
            int val;
            cout << "---------------------------------------------------\n";
            cout << "Number to search for: " ;
            cin >> val;
    
            bool found = search(root, val);
            cout << "Found " << val << " : " << boolalpha << found << endl;
            cout << "---------------------------------------------------\n";

        } else if (answer == "3") {
            cout << "---------------------------------------------------\n";
            printInOrder(root);
            cout << endl;
            cout << "---------------------------------------------------\n";
        } else if (answer == "4") {
            cout << "---------------------------------------------------\n";
            exit();
        } else{
            cout << "---------------------------------------------------\n";
            cout << "Invalid input: " << answer << " ." << "Try again.\n";
            cout << "---------------------------------------------------\n";
        }
    }

    return 0;
}

int main() {
    menu();
    return 0;
}