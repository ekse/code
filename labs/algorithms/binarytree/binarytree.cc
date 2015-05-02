#include <cstddef>
#include "binarytree.h"

/* This class implements an AVL tree.
 *
 */

MyNode::MyNode(int value) : left_(nullptr), right_(nullptr) {
    value_ = value;

}

BinaryTree::BinaryTree() : root_(nullptr) {}

void BinaryTree::insert(int value) {
    auto node = new MyNode(value);

    if (root_ == nullptr) {
        root_ = node;
        return;
    }

    auto cur_node = root_;

    while (true) {
        if (value < cur_node->value_) {
            if (cur_node->left_ == nullptr) {
                cur_node->left_ = node;
                return;
            }
            cur_node = cur_node->left_;
        } else {
            if (cur_node->right_ == nullptr) {
                cur_node->right_ = node;
                return;
            }
            cur_node = cur_node->right_;
        }
    }
}

// default min value is 0
int BinaryTree::min() {
    if (root_ == nullptr) {
        return 0;
    }

    auto cur_node = root_;

    while (true) {
        if (cur_node->left_ == nullptr) {
            break;
        }
        cur_node = cur_node->left_;
    }
    return (cur_node->value_);
}

// default max value is 0
int BinaryTree::max() {
    if (root_ == nullptr) {
        return 0;
    }

    auto cur_node = root_;

    while (true) {
        if (cur_node->right_ == nullptr) {
            break;
        }
        cur_node = cur_node->right_;
    }

    return (cur_node->value_);
}
