#include<iostream>
#include<stack>
#include <chrono>
using namespace std;
using namespace std::chrono;
struct Node{
    int data;
    Node* left;
    Node* right;
};

Node* insert(Node* root, int data){
    if(!root) return new Node{data, nullptr, nullptr};
    if (data < root->data) root->left = insert(root->left, data);
    else root->right = insert(root->right, data);
    return root;
}

void inorder(Node* root){
    if(!root) return;
    inorder(root->left);
    cout << root->data << " ";
    inorder(root->right);
}

void preorder(Node* root){
    if(!root) return;

    cout<<root->data<<" ";
    preorder(root->left);
    preorder(root->right);
}

void postorder(Node* root){
    if(!root) return;

    postorder(root->left);
    postorder(root->right);
    cout<<root->data<<" ";
}

void inorderIterative(Node* root){
    stack<Node*> s;

    Node* curr = root;

    while(curr || !s.empty()){
        while(curr){
            s.push(curr);
            curr = curr->left;
        }

        curr = s.top(); s.pop();
        cout<<curr->data<<" ";
        curr = curr->right;
    }
}

void preorderIterative(Node* root){
    if(!root) return;

    stack<Node*> s;
    s.push(root);

    while(!s.empty()){
        Node* curr = s.top(); s.pop();
        cout<<curr->data<<" ";

        if(curr->right) s.push(curr->right);
        if(curr->left) s.push(curr->left);
    }
}

void postorderIterative(Node* root) {
    if (!root) return;
    stack<Node*> st1, st2;
    st1.push(root);

    while (!st1.empty()) {
        Node* curr = st1.top(); st1.pop();
        st2.push(curr);

        if (curr->left) st1.push(curr->left);
        if (curr->right) st1.push(curr->right);
    }

    while (!st2.empty()) {
        cout << st2.top()->data << " ";
        st2.pop();
    }
}


int height(Node* root) {
    if (!root) return 0;
    return 1 + max(height(root->left), height(root->right));
}

Node* clone(Node* root) {
    if (!root) return nullptr;
    Node* newNode = new Node{root->data};
    newNode->left = clone(root->left);
    newNode->right = clone(root->right);
    return newNode;
}

Node* mirror(Node* root) {
    if (!root) return nullptr;
    Node* mirrored = new Node{root->data};
    mirrored->left = mirror(root->right);
    mirrored->right = mirror(root->left);
    return mirrored;
}

void erase(Node* &root) {
    if (!root) return;
    erase(root->left);
    erase(root->right);
    delete root;
    root = nullptr;
}

int preIndex = 0;

Node* buildFromInPre(int inorder[], int preorder[], int inStart, int inEnd) {
    if (inStart > inEnd) return nullptr;

    Node* root = new Node{preorder[preIndex++]};

    int inIndex;
    for (inIndex = inStart; inIndex <= inEnd; inIndex++) {
        if (inorder[inIndex] == root->data) break;
    }

    root->left = buildFromInPre(inorder, preorder, inStart, inIndex - 1);
    root->right = buildFromInPre(inorder, preorder, inIndex + 1, inEnd);
    return root;
}

Node* findMin(Node* root) {
    while (root && root->left) root = root->left;
    return root;
}

Node* deleteNode(Node* root, int key) {
    if (!root) return nullptr;

    if (key < root->data)
        root->left = deleteNode(root->left, key);
    else if (key > root->data)
        root->right = deleteNode(root->right, key);
    else {
        if (!root->left) {
            Node* temp = root->right;
            delete root;
            return temp;
        } else if (!root->right) {
            Node* temp = root->left;
            delete root;
            return temp;
        }

        Node* temp = findMin(root->right);
        root->data = temp->data;
        root->right = deleteNode(root->right, temp->data);
    }

    return root;
}

bool areEqual(Node* a, Node* b) {
    if (!a && !b) return true;
    if (!a || !b) return false;
    return a->data == b->data &&
           areEqual(a->left, b->left) &&
           areEqual(a->right, b->right);
}

int main() {
    Node* root = nullptr;

    // Insert some nodes
    root = insert(root, 50);
    insert(root, 30);
    insert(root, 70);
    insert(root, 20);
    insert(root, 40);
    insert(root, 60);
    insert(root, 80);

    cout << "\n=== Recursive Traversals ===\n";
    cout << "Inorder: ";
    auto start = high_resolution_clock::now();
    inorder(root);
    auto end = high_resolution_clock::now();
    cout << "\nTime: " << duration_cast<nanoseconds>(end - start).count() << " ns\n";

    cout << "Preorder: ";
    start = high_resolution_clock::now();
    preorder(root);
    end = high_resolution_clock::now();
    cout << "\nTime: " << duration_cast<nanoseconds>(end - start).count() << " ns\n";

    cout << "Postorder: ";
    start = high_resolution_clock::now();
    postorder(root);
    end = high_resolution_clock::now();
    cout << "\nTime: " << duration_cast<nanoseconds>(end - start).count() << " ns\n";

    cout << "\n=== Iterative Traversals ===\n";
    cout << "Inorder Iterative: ";
    start = high_resolution_clock::now();
    inorderIterative(root);
    end = high_resolution_clock::now();
    cout << "\nTime: " << duration_cast<nanoseconds>(end - start).count() << " ns\n";

    cout << "Preorder Iterative: ";
    start = high_resolution_clock::now();
    preorderIterative(root);
    end = high_resolution_clock::now();
    cout << "\nTime: " << duration_cast<nanoseconds>(end - start).count() << " ns\n";

    cout << "Postorder Iterative: ";
    start = high_resolution_clock::now();
    postorderIterative(root);
    end = high_resolution_clock::now();
    cout << "\nTime: " << duration_cast<nanoseconds>(end - start).count() << " ns\n";

    cout << "\n=== Height of Tree ===\n";
    start = high_resolution_clock::now();
    int h = height(root);
    end = high_resolution_clock::now();
    cout << "Height: " << h << "\nTime: " << duration_cast<nanoseconds>(end - start).count() << " ns\n";

    cout << "\n=== Cloning Tree ===\n";
    start = high_resolution_clock::now();
    Node* cloneTree = clone(root);
    end = high_resolution_clock::now();
    cout << "Clone created.\nTime: " << duration_cast<nanoseconds>(end - start).count() << " ns\n";

    cout << "\n=== Mirroring Tree ===\n";
    start = high_resolution_clock::now();
    Node* mirrored = mirror(root);
    end = high_resolution_clock::now();
    cout << "Mirror created.\nTime: " << duration_cast<nanoseconds>(end - start).count() << " ns\n";

    cout << "\n=== Check Equality ===\n";
    start = high_resolution_clock::now();
    bool equal = areEqual(root, cloneTree);
    end = high_resolution_clock::now();
    cout << "Trees equal? " << (equal ? "Yes" : "No") << "\nTime: " << duration_cast<nanoseconds>(end - start).count() << " ns\n";

    cout << "\n=== Delete a Node ===\n";
    start = high_resolution_clock::now();
    root = deleteNode(root, 70);
    end = high_resolution_clock::now();
    cout << "Deleted 70 from tree.\nTime: " << duration_cast<nanoseconds>(end - start).count() << " ns\n";

    cout << "Inorder after deletion: ";
    inorder(root);
    cout << "\n";

    cout << "\n=== Build Tree from Inorder + Preorder ===\n";
    int in[] = {20, 30, 40, 50, 60, 80};
    int pre[] = {50, 30, 20, 40, 80, 60};
    preIndex = 0;
    start = high_resolution_clock::now();
    Node* rebuilt = buildFromInPre(in, pre, 0, 5);
    end = high_resolution_clock::now();
    cout << "Built tree Inorder: ";
    inorder(rebuilt);
    cout << "\nTime: " << duration_cast<nanoseconds>(end - start).count() << " ns\n";

    // Cleanup
    erase(root);
    erase(cloneTree);
    erase(mirrored);
    erase(rebuilt);

    return 0;
}