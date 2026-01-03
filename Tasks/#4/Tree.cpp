#include <iostream>
#include <queue>
#include <stdexcept>

using namespace std;

template <class T>
class BSTNode {
public:
    T data;
    BSTNode<T>* left;
    BSTNode<T>* right;

    BSTNode(const T& value) : data(value), left(nullptr), right(nullptr) {}
};

template <class T>
class BST {
private:
    BSTNode<T>* root;

    // Helper: Recursive delete for destructor
    void clear(BSTNode<T>* node) {
        if (node) {
            clear(node->left);
            clear(node->right);
            delete node;
        }
    }

    // Helper: Recursive insertion
    BSTNode<T>* insert(BSTNode<T>* node, const T& value) {
        if (!node) return new BSTNode<T>(value);

        if (value < node->data)
            node->left = insert(node->left, value);
        else if (value > node->data)
            node->right = insert(node->right, value);
        
        return node;
    }

    // Helper: Recursive search
    BSTNode<T>* search(BSTNode<T>* node, const T& value) const {
        if (!node || node->data == value) return node;
        if (value < node->data) return search(node->left, value);
        return search(node->right, value);
    }

    // Helper: Recursive deletion
    BSTNode<T>* remove(BSTNode<T>* node, const T& value) {
        if (!node) return nullptr;

        if (value < node->data) {
            node->left = remove(node->left, value);
        } else if (value > node->data) {
            node->right = remove(node->right, value);
        } else {
            // Case 1 & 2: One child or No child
            if (!node->left) {
                BSTNode<T>* temp = node->right;
                delete node;
                return temp;
            } else if (!node->right) {
                BSTNode<T>* temp = node->left;
                delete node;
                return temp;
            }

            // Case 3: Two children
            BSTNode<T>* temp = minValueNode(node->right);
            node->data = temp->data;
            node->right = remove(node->right, temp->data);
        }
        return node;
    }

    void inOrder(BSTNode<T>* node) const {
        if (!node) return;
        inOrder(node->left);
        cout << node->data << " ";
        inOrder(node->right);
    }
    
    BSTNode<T>* minValueNode(BSTNode<T>* node) const {
        BSTNode<T>* current = node;
        while (current && current->left) current = current->left;
        return current;
    }

    int maxDepth(BSTNode<T>* node) const {
        if(node == nullptr){
            return 0;
        }

        int leftDepth = maxDepth(node->left);
        int rightDepth = maxDepth(node->right);

        return 1 + std::max(leftDepth, rightDepth);
    }

public:
    BST() : root(nullptr) {}

    ~BST() {
        clear(root);
    }

    void insert(const T& value) { root = insert(root, value); }
    
    void remove(const T& value) { root = remove(root, value); }

    bool exists(const T& value) const { return search(root, value) != nullptr; }

    void printInOrder() const {
        inOrder(root);
        cout << endl;
    }

    void breadthFirst() const {
        if (!root) return;
        queue<BSTNode<T>*> q;
        q.push(root);
        while (!q.empty()) {
            BSTNode<T>* current = q.front();
            q.pop();
            cout << current->data << " ";
            if (current->left) q.push(current->left);
            if (current->right) q.push(current->right);
        }
        cout << endl;
    }


    // Return root value only for specific cases
    T getMin() const {
        BSTNode<T>* minNode = minValueNode(root);
        if (!minNode) throw runtime_error("Tree is empty");
        return minNode->data;
    }

    int getHeight() const {
        return maxDepth(root);
    }

    void printLevels() const {
    if (!root) {
        cout << "Tree is empty." << endl;
        return;
    }

    queue<BSTNode<T>*> q;
    q.push(root);

    while (!q.empty()) {
        int nodesAtCurrentLevel = q.size(); // Count how many nodes are on this "floor"

        while (nodesAtCurrentLevel > 0) {
            BSTNode<T>* current = q.front();
            q.pop();

            cout << current->data << " ";

            if (current->left) q.push(current->left);
            if (current->right) q.push(current->right);

            nodesAtCurrentLevel--;
        }
        cout << endl; // Move to the next line for the next level
    }
}
};

int main() {
    BST<int> tree;

    /* Let's build this tree:
              50
            /    \
          30      70
         /  \    /  \
        20  40  60  80
    */

    cout << "--- Inserting Nodes ---" << endl;
    int values[] = {50, 30, 70, 20, 40, 60, 80};
    for (int v : values) {
        tree.insert(v);
        cout << "Inserted: " << v << endl;
    }

    cout << "\n--- Tree Structure (Level-by-Level) ---" << endl;
    tree.printLevels();

    cout << "\n--- Sorted Order (In-Order) ---" << endl;
    tree.printInOrder();

    cout << "\n--- Statistics ---" << endl;
    cout << "Tree Height: " << tree.getHeight() << endl;
    cout << "Minimum Value: " << tree.getMin() << endl;

    cout << "\n--- Search Operations ---" << endl;
    int searchKeys[] = {40, 99};
    for (int key : searchKeys) {
        if (tree.exists(key)) {
            cout << "Value " << key << " exists in the tree." << endl;
        } else {
            cout << "Value " << key << " NOT found." << endl;
        }
    }

    cout << "\n--- Deletion Operations ---" << endl;
    
    // Case 1: Delete a leaf (20)
    cout << "Deleting leaf node (20)..." << endl;
    tree.remove(20);
    
    // Case 2: Delete a node with one child (Assume we add 85 then delete 80)
    tree.insert(85);
    cout << "Deleting node with one child (80)..." << endl;
    tree.remove(80);

    // Case 3: Delete the root (50) - Node with two children
    cout << "Deleting root node (50)..." << endl;
    tree.remove(50);

    cout << "\n--- Final Tree Structure ---" << endl;
    tree.printLevels();

    return 0;
}