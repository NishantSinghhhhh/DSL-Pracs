#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>
#include <string>
#include <limits>
using namespace std;

// A tree node for Huffman coding
struct Node {
    char ch;       // character
    int freq;      // frequency
    Node *left;    // left child
    Node *right;   // right child
};

// A comparator for the priority queue (min-heap)
struct Compare {
    bool operator()(Node* l, Node* r) {
        return l->freq > r->freq;  // smallest freq has highest priority
    }
};

// Utility to create a new Huffman tree node
Node* getNode(char ch, int freq, Node* left, Node* right) {
    Node* node = new Node();
    node->ch = ch;
    node->freq = freq;
    node->left = left;
    node->right = right;
    return node;
}

// Build Huffman tree given vectors of characters and frequencies
Node* buildHuffmanTree(const vector<char>& chars, const vector<int>& freqs) {
    // min-heap of tree nodes
    priority_queue<Node*, vector<Node*>, Compare> pq;

    // Create a leaf node for each character and push it into the queue
    for (size_t i = 0; i < chars.size(); i++) {
        pq.push(getNode(chars[i], freqs[i], nullptr, nullptr));
    }

    // Repeat until the heap size is 1 (root of the Huffman tree)
    while (pq.size() > 1) {
        // Remove two nodes of highest priority (lowest frequency)
        Node* left = pq.top(); 
        pq.pop();
        Node* right = pq.top(); 
        pq.pop();

        // Create a new internal node with frequency = sum of two nodes
        int sum = left->freq + right->freq;
        pq.push(getNode('\0', sum, left, right));
    }

    // The remaining node is the root of the Huffman tree
    return pq.top();
}

// Traverse the Huffman tree and store codes in an unordered_map
void buildCodes(Node* root, const string &str, unordered_map<char, string> &huffmanCode) {
    if (!root) return;

    // If this is a leaf node, assign the code
    if (!root->left && !root->right) {
        // Edge case: if there's only one character, give it "0" code
        huffmanCode[root->ch] = (str != "") ? str : "0";
        return;
    }

    // Traverse left
    buildCodes(root->left, str + "0", huffmanCode);
    // Traverse right
    buildCodes(root->right, str + "1", huffmanCode);
}

// Encode a string using the Huffman codes
string encodeString(const string &text, const unordered_map<char, string> &huffmanCode) {
    string encoded;
    for (char ch : text) {
        encoded += huffmanCode.at(ch);  // append this char's code
    }
    return encoded;
}

// Decode a bit sequence using the Huffman tree
string decodeString(const string &encoded, Node* root) {
    string decoded;
    Node* curr = root;
    for (char bit : encoded) {
        // Go left for '0', right for '1'
        if (bit == '0') curr = curr->left;
        else            curr = curr->right;

        // If leaf node is reached
        if (!curr->left && !curr->right) {
            decoded += curr->ch;
            curr = root;  // reset to root for next character
        }
    }
    return decoded;
}

int main() {
    int n;
    cout << "Enter the number of distinct characters: ";
    cin >> n;

    // Read characters and their frequencies
    vector<char> chars(n);
    vector<int> freqs(n);
    cout << "Enter character followed by its frequency:\n";
    for (int i = 0; i < n; i++) {
        cin >> chars[i] >> freqs[i];
    }

    // 1) Build Huffman Tree
    Node* root = buildHuffmanTree(chars, freqs);

    // 2) Build Huffman Codes (char -> bitstring)
    unordered_map<char, string> huffmanCode;
    buildCodes(root, "", huffmanCode);

    // Print the Huffman codes
    cout << "\nHuffman Codes:\n";
    for (auto &pair : huffmanCode) {
        cout << pair.first << " -> " << pair.second << "\n";
    }

    // Encode a string
    cout << "\nEnter a string to encode: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');  // clear leftover newline
    string text;
    getline(cin, text);

    string encoded = encodeString(text, huffmanCode);
    cout << "Encoded string: " << encoded << "\n";

    // Decode a bit sequence
    cout << "\nEnter a bit sequence to decode: ";
    string bitSeq;
    getline(cin, bitSeq);

    string decoded = decodeString(bitSeq, root);
    cout << "Decoded string: " << decoded << "\n";

    return 0;
}
