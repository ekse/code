#include <cstddef>
#include "binarytree.h"

/* This class implements an AVL tree.
 *
 */

MyNode::MyNode(int v) {
    value = v;
    left = nullptr;
    right = nullptr;
}

BinaryTree::BinaryTree() { root = nullptr; }

void BinaryTree::insert(int v) {
    auto node = new MyNode(v);

    if (root == nullptr) {
        root = node;
        return;
    }

    auto cur_node = root;

    while (true) {
        if ((v < cur_node->value) && cur_node->left == nullptr) {
            if (cur_node->left == nullptr) {
                cur_node->left = node;
                break;
            }
            cur_node = cur_node->left;
        } else {
            if (cur_node->right == nullptr) {
                cur_node->right = node;
                break;
            }
            cur_node = cur_node->right;
        }
    }

    return;
}

// default min value is 0
int BinaryTree::min() {
    if (root == nullptr) {
        return (0);
    }

    auto cur_node = root;

    while (true) {
        if (cur_node->left == nullptr) {
            break;
        }
        cur_node = cur_node->left;
    }
    return (cur_node->value);
}

// default max value is 0
int BinaryTree::max() {
    if (root == nullptr) {
        return (0);
    }

    auto cur_node = root;

    while (true) {
        if (cur_node->right == nullptr) {
            break;
        }
        cur_node = cur_node->right;
    }

    return (cur_node->value);
}
