#include <iostream>
#include <queue>
#include <vector>
#include <unordered_map>
#include <stack>

using namespace std;

// Node structure for Huffman Tree
struct Node {
    char ch;
    int freq;
    Node* left;
    Node* right;
    
    Node(char ch, int freq) {
        left = right = nullptr;
        this->ch = ch;
        this->freq = freq;
    }
};

// Comparator for priority queue (min-heap)
struct Compare {
    bool operator()(Node* l, Node* r) {
        return l->freq > r->freq;
    }
};

// Function to print Huffman codes using an iterative preorder traversal
void printHuffmanCodes(Node* root) {
    if (!root) return;

    stack<pair<Node*, string>> s; // Stack for iterative traversal
    s.push({root, ""}); // Push root and an empty string (code)

    while (!s.empty()) {
        auto node_pair = s.top();
        s.pop();
        Node* node = node_pair.first;
        string code = node_pair.second;

        // If it's a leaf node (i.e., it contains a character), print the code
        if (!node->left && !node->right) {
            cout << node->ch << ": " << code << endl;
        }

        // Push right and left children to the stack (right first, because we want to process left first)
        if (node->right) {
            s.push({node->right, code + "1"});
        }
        if (node->left) {
            s.push({node->left, code + "0"});
        }
    }
}

// Function to build the Huffman Tree
Node* buildHuffmanTree(const string& S, const vector<int>& freq) {
    priority_queue<Node*, vector<Node*>, Compare> minHeap;

    // Step 1: Create a leaf node for each character and add it to the priority queue.
    for (int i = 0; i < S.size(); ++i) {
        minHeap.push(new Node(S[i], freq[i]));
    }

    // Step 2: Build the tree by combining the two smallest nodes.
    while (minHeap.size() != 1) {
        Node* left = minHeap.top(); minHeap.pop();
        Node* right = minHeap.top(); minHeap.pop();

        // Create a new internal node with frequency equal to the sum of the two nodes
        int sum = left->freq + right->freq;
        Node* newNode = new Node('$', sum); // '$' is a special marker for internal nodes
        newNode->left = left;
        newNode->right = right;

        minHeap.push(newNode);
    }

    // The remaining node is the root of the Huffman Tree
    return minHeap.top();
}

int main() {
    string S = "abcdef";
    vector<int> freq = {5, 9, 12, 13, 16, 45};

    // Build Huffman Tree
    Node* root = buildHuffmanTree(S, freq);

    // Print the Huffman codes (Preorder traversal)
    printHuffmanCodes(root);

    return 0;
}
