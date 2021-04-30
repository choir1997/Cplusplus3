#ifndef CS235_LAB_8_BST_H
#define CS235_LAB_8_BST_H
#include "BSTInterface.h"
#include <sstream>

using namespace std;

template<typename T>
class BST : public BSTInterface<T> {
private:
    struct Node {
        T dataValue;
        Node* leftNode;
        Node* rightNode;
        Node(T d) : dataValue(d), leftNode(NULL), rightNode(NULL) {}
    };
    Node* rootNode;
    size_t treeSize = 0;
public:
    BST() { this->rootNode = NULL; }
    ~BST() { clearTree(); }

    void replace_parent(Node*& old_root, Node*& local_root) {
        if (local_root->rightNode != NULL) {
            replace_parent(old_root, local_root->rightNode);
        }
        else {
            old_root->dataValue = local_root->dataValue;
            old_root = local_root;
            local_root = local_root->leftNode;
        }
    }

    bool addNode(const T& newNodeData) { //todo: add temporary root node
        return insert(rootNode, newNodeData);
    }

    bool insert(Node*& node, const T& data) {
        if (node == NULL) {
            node = new Node(data);
            treeSize++;
            return true;
        }
        else if (data < node->dataValue) {
            return insert(node->leftNode, data);
        }
        else if (data > node->dataValue) {
            return insert(node->rightNode, data);
        }
        else {
            return false;
        }
    }

    bool removeNode(const T& data) {
        return deleteNode(rootNode, data);
    }

    bool deleteNode(Node*& node, const T& data) {
        if (node == NULL) {
            return false;
        }
        else {
            if (data < node->dataValue) {
                return deleteNode(node->leftNode, data);
            }
            else if (data > node->dataValue) {
                return deleteNode(node->rightNode, data);
            }
            else {
                Node* old_root = node;
                if (node->leftNode == NULL) {
                    node = node->rightNode;
                }
                else if (node->rightNode == NULL) {
                    node = node->leftNode;
                }
                else {
                    replace_parent(old_root, old_root->leftNode);
                }
                delete old_root;
                treeSize--;
                old_root = NULL;
                return true;
            }
        }
    }

    bool findNode(const T& nodeData) {
        return find(rootNode, nodeData);
    }

    bool find(Node* node, const T& nodeData) {
        if (node == NULL) {
            return false;
        }
        if (node->dataValue == nodeData) {
            return true;
        }
        if (find(node->leftNode, nodeData)) {
            return true;
        }
        else {
            return find(node->rightNode, nodeData);
        }
    }

    bool clearTree() {
        return deleteTree(rootNode);
    }

    bool deleteTree(Node*& node) {
        if (node == NULL) {
            return true;
        }
        deleteTree(node->leftNode);
        deleteTree(node->rightNode);

        delete node;
        node = NULL;
        return true;
    }

    bool outLevel(Node* root, int level, ostringstream& out) const {
        if (root == NULL) {
            return false;
        }
        else if (level == 1) {
            out << " " << root->dataValue;
            if (root->leftNode != NULL || root->rightNode != NULL) {
                return true;
            }
        }
        else if ((level == 2) && !root->leftNode && root->rightNode) out << " _";
        bool left = outLevel(root->leftNode, level - 1, out);
        bool right = outLevel(root->rightNode,level - 1, out);
        if ((level == 2) && root->leftNode && !root->rightNode) out << " _";
        return left || right;
    }

    size_t sizeTree() {
        if (rootNode == NULL) {
            treeSize = 0;
        }
        return treeSize;
    }

    string toString() const {
        ostringstream outputString;
        if (rootNode == NULL) {
            outputString << " empty";
        }
        else {
            int level = 0;
            do {
                outputString << endl << " " << ++level << ":";
            } while (outLevel(rootNode, level, outputString));
        }
        return outputString.str();
    }
    friend ostream &operator<<(ostream &os, BST<T> &bst) {
            os << bst.toString();
        return os;
    }
};

#endif //CS235_LAB_8_BST_H
