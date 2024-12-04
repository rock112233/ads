#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

// Node structure for the suffix tree
struct SuffixTreeNode {
    map<char, SuffixTreeNode*> children; // Edges leading to children
    int start;                           // Start index of the edge
    int* end;                            // End index of the edge
    SuffixTreeNode* suffixLink;          // Suffix link

    SuffixTreeNode(int start, int* end) : start(start), end(end), suffixLink(nullptr) {}
};

class SuffixTree {
private:
    string text;                   // Input string
    SuffixTreeNode* root;          // Root of the tree
    int remainingSuffixCount;      // Number of suffixes to be added
    int activeLength;              // Active length for active node
    SuffixTreeNode* activeNode;    // Currently active node
    int activeEdge;                // Active edge
    int leafEnd;                   // Global leaf end
    int size;                      // Size of the string
    vector<int> suffixArray;       // For storing suffix indices

    void extendSuffixTree(int pos);
    void setSuffixIndex(SuffixTreeNode* node, int labelHeight);
    void buildSuffixArray(SuffixTreeNode* node, int labelHeight); // Fixed

public:
    SuffixTree(const string& input);
    ~SuffixTree();
    void printSuffixTree();
    void buildSuffixArray();
};

// Constructor
SuffixTree::SuffixTree(const string& input) : text(input + "$"), size(input.length() + 1), leafEnd(-1) {
    root = new SuffixTreeNode(-1, new int(-1));
    activeNode = root;
    activeEdge = -1;
    activeLength = 0;
    remainingSuffixCount = 0;

    for (int i = 0; i < size; ++i)
        extendSuffixTree(i);

    setSuffixIndex(root, 0);
}

// Destructor
SuffixTree::~SuffixTree() {
    // Proper memory cleanup (not implemented for brevity)
}

// Function to extend the suffix tree
void SuffixTree::extendSuffixTree(int pos) {
    leafEnd = pos;
    remainingSuffixCount++;

    SuffixTreeNode* lastNewNode = nullptr;

    while (remainingSuffixCount > 0) {
        if (activeLength == 0) activeEdge = pos;

        char currentChar = text[activeEdge];
        if (activeNode->children.find(currentChar) == activeNode->children.end()) {
            activeNode->children[currentChar] = new SuffixTreeNode(pos, &leafEnd);
            if (lastNewNode) {
                lastNewNode->suffixLink = activeNode;
                lastNewNode = nullptr;
            }
        } else {
            SuffixTreeNode* next = activeNode->children[currentChar];
            int edgeLength = *(next->end) - next->start + 1;

            if (activeLength >= edgeLength) {
                activeEdge += edgeLength;
                activeLength -= edgeLength;
                activeNode = next;
                continue;
            }

            if (text[next->start + activeLength] == text[pos]) {
                if (lastNewNode) {
                    lastNewNode->suffixLink = activeNode;
                    lastNewNode = nullptr;
                }
                activeLength++;
                break;
            }

            int* splitEnd = new int(next->start + activeLength - 1);
            SuffixTreeNode* split = new SuffixTreeNode(next->start, splitEnd);
            activeNode->children[currentChar] = split;

            split->children[text[pos]] = new SuffixTreeNode(pos, &leafEnd);
            next->start += activeLength;
            split->children[text[next->start]] = next;

            if (lastNewNode) {
                lastNewNode->suffixLink = split;
            }

            lastNewNode = split;
        }

        remainingSuffixCount--;

        if (activeNode == root && activeLength > 0) {
            activeLength--;
            activeEdge = pos - remainingSuffixCount + 1;
        } else if (activeNode != root) {
            activeNode = activeNode->suffixLink ? activeNode->suffixLink : root;
        }
    }
}

// Function to set suffix indices
void SuffixTree::setSuffixIndex(SuffixTreeNode* node, int labelHeight) {
    if (!node) return;

    bool isLeaf = true;
    for (auto& child : node->children) {
        isLeaf = false;
        setSuffixIndex(child.second, labelHeight + *(child.second->end) - child.second->start + 1);
    }

    if (isLeaf) {
        suffixArray.push_back(size - labelHeight);
    }
}

// Function to build the suffix array
void SuffixTree::buildSuffixArray(SuffixTreeNode* node, int labelHeight) {
    if (!node) return;

    bool isLeaf = true;
    for (auto& child : node->children) {
        isLeaf = false;
        buildSuffixArray(child.second, labelHeight + *(child.second->end) - child.second->start + 1);
    }

    if (isLeaf) {
        suffixArray.push_back(size - labelHeight);
    }
}

// Function to print the suffix tree
void SuffixTree::printSuffixTree() {
    cout << "Suffix Tree construction complete. Implement traversal to view edges." << endl;
}

// Main function
int main() {
    string input;
    cout << "Enter a string: ";
    cin >> input;

    SuffixTree suffixTree(input);
    suffixTree.printSuffixTree();

    return 0;
}