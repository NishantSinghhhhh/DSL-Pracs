#include<iostream>
#include<cstdlib>

using namespace std;

struct Node{
    int data;
    Node* left;
    Node* right;
    bool lthread;
    bool rthread;
};

// ============================
// Utility: Create a new node
// ============================

Node* createNode(int key){
    Node* temp = new Node;
    temp->data = key;
    temp->left = nullptr;
    temp->right = nullptr;
    temp->lthread = true;
    temp->rthread= true;
    return temp;
}

// ============================================================
// Insert a new key into the Inorder Threaded BST
// ============================================================

Node* insertThreadedBST(Node* root, int key){
    if(root == nullptr){
        root = createNode(key);
        return root;
    }

    Node* curr = root;
    Node* parent = nullptr;

    while(curr != nullptr){
        if(key == curr->data){
            cout << "Key " << key << " already in tree.\n";
            return root;
        }

        parent = curr;

        if(key <curr->data){
             // Go left if it is not a thread
             if (!curr->lthread) curr = curr->left;
             else break; // we found a thread => insertion point
        }
        else { // key > curr->data
            // Go right if it is not a thread
            if (!curr->rthread) curr = curr->right;
            else break;
        }
    }

    Node* newNode = createNode(key);

    if(key <parent->data){
        newNode->left = parent->left;
        newNode->right = parent;
        parent->lthread = false;
        parent->left = newNode;
    }

    else {
        // Make newNode as right child
        newNode->right = parent->right;
        newNode->left = parent;
        parent->rthread = false;
        parent->right = newNode;
    }
    return root;
}

// ============================================================
// Find leftmost node in a Threaded BST (used for inorder start)
// ============================================================
Node* leftmost(Node* root) {
    if (root == nullptr) return nullptr;
    while (!root->lthread) root = root->left;
    return root;
}

// ============================================================
// Inorder traversal in a Threaded BST
// ============================================================
void inorderT(Node* root){
    if (root == nullptr) {
        cout << "Tree is empty.\n";
        return;
    }

    Node* curr = leftmost(root);

    while(curr != nullptr){
        cout<<curr->data<<" ";
        if(curr->rthread){
            curr = curr->right;
        }
        else{
            curr = leftmost(curr->right);
        }
    }
    cout<<endl;
}

// ============================================================
// Preorder traversal in a Threaded BST
// ============================================================
void preorderT(Node* root) {
    if (root == nullptr) {
        cout << "Tree is empty.\n";
        return;
    }

    Node* curr = root;
    while (curr != nullptr) {
        // Print current
        cout << curr->data << " ";

        // If left link is a child, move left
        if (!curr->lthread) {
            curr = curr->left;
        }
        else if (!curr->rthread) {
            // else if right link is a child, move right
            curr = curr->right;
        }
        else {
            // Otherwise, follow threads until we find a node
            // that has a right child we haven't visited
            while (curr != nullptr && curr->rthread) {
                curr = curr->right;
            }
            // Then go to that right child
            if (curr != nullptr) curr = curr->right;
        }
    }
    cout << endl;
}

void convertToThreaded(Node* root, Node*& prev){
    if(root == nullptr) return;

    convertToThreaded(root->left, prev);

 // If left child is null, make it thread
    if(root->left ==nullptr){
        root->lthread = true;

        root->left=prev;
    }
    else{
        root->lthread = false;
    }

    // If prev's right is null, make it thread
    if(prev != nullptr && prev->right == nullptr){
        prev->rthread = true;
        prev->right = root;
    }

    prev = root;
    convertToThreaded(root->right, prev);
}


Node* insertNormalBST(Node* root, int key){
    if(root == nullptr){
        Node* temp = new Node;
        temp->data = key;
        temp->left = nullptr;
        temp->right = nullptr;
        temp->lthread = false;
        temp->rthread = false;
        return temp;
    }

    if(key <root->data){
        root->left = insertNormalBST(root->left, key);
    }
    else{
        root->right = insertNormalBST(root->right, key); 
    }

    return root;
}

Node* convertBSTtoThreaded(Node* root) {
    // First, ensure all threads are false
    // Or assume a normal BST means no threads
    Node* prev = nullptr;
    convertToThreaded(root, prev);
    return root;
}

int main() {
    Node* tbt = nullptr; // TBT root
    cout << "Creating an Inorder Threaded BST by insertion...\n";
    tbt = insertThreadedBST(tbt, 50);
    tbt = insertThreadedBST(tbt, 30);
    tbt = insertThreadedBST(tbt, 70);
    tbt = insertThreadedBST(tbt, 20);
    tbt = insertThreadedBST(tbt, 40);
    tbt = insertThreadedBST(tbt, 60);
    tbt = insertThreadedBST(tbt, 80);

    cout << "\nInorder (Threaded): ";
    inorderT(tbt);

    cout << "Preorder (Threaded): ";
    preorderT(tbt);

    cout << "\n\n=== Convert a normal BST to Threaded BST ===\n";
    Node* normalBST = nullptr;
    normalBST = insertNormalBST(normalBST, 50);
    normalBST = insertNormalBST(normalBST, 30);
    normalBST = insertNormalBST(normalBST, 70);
    normalBST = insertNormalBST(normalBST, 20);
    normalBST = insertNormalBST(normalBST, 40);
    normalBST = insertNormalBST(normalBST, 60);
    normalBST = insertNormalBST(normalBST, 80);

    // Convert
    convertBSTtoThreaded(normalBST);

    cout << "Now normalBST is threaded. Let's do an inorderT.\n";
    // We can reuse the same inorderT function, but it expects
    // that we have "leftmost" logic. So let's define leftmost quickly:
    // (We can reuse the existing leftmost function if it expects lthread.)
    // We can do so if we accept that normalBST might not have "leftmost" set as threads.
    // But after convertToThreaded, it should be partially set.

    // We'll do an inorder traversal using the same approach as inorderT:
    Node* start = normalBST;
    // go to leftmost
    while (start && !start->lthread) start = start->left;

    cout << "Inorder after convert: ";
    while (start != nullptr) {
        cout << start->data << " ";
        // if rthread, go to right
        if (start->rthread) {
            start = start->right;
        }
        else {
            // else go leftmost in right subtree
            Node* temp = start->right;
            while (temp && !temp->lthread) temp = temp->left;
            start = temp;
        }
    }
    cout << endl;

    return 0;
}