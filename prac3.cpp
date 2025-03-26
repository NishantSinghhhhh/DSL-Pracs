#include<iostream>
#include<stack>

using namespace std;

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