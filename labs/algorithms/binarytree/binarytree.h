#include <cstddef>
#pragma once

/* This class implements an AVL tree.
 *
 */

template <typename T>
class BinaryTree;

template <typename T>
class MyNode {
    friend class BinaryTree<T>;

   public:
    MyNode<T>(T value);

   private:
    T value_;
    MyNode<T>* left_;
    MyNode<T>* right_;
};

template <typename T>
MyNode<T>::MyNode(T value)
    : left_(nullptr), right_(nullptr) {
    value_ = value;
}

// BinaryTree
template <typename T>
class BinaryTree {
   public:
    BinaryTree<T>();
    void Insert(T value);
    bool Contains(T value);
    bool IsEmpty() { return (root_ == nullptr); };
    T Min();
    T Max();
    // void traverse(); -- not implemented yet

   private:
    MyNode<T>* root_;
};

template <typename T>
BinaryTree<T>::BinaryTree()
    : root_(nullptr) {}

template <typename T>
bool BinaryTree<T>::Contains(T value) {
    if (root_ == nullptr) {
        return false;
    }

    auto cur_node = root_;

    while (true) {
        if (value == cur_node->value_) {
            return true;
        } else if (value < cur_node->value_) {
            if (cur_node->left_ == nullptr) {
                return false;
            }
            cur_node = cur_node->left_;
        } else {
            if (cur_node->right_ == nullptr) {
                return false;
            }
            cur_node = cur_node->right_;
        }
    }
}

template <typename T>
void BinaryTree<T>::Insert(T value) {
    MyNode<T>* node = new MyNode<T>(value);

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
template <typename T>
T BinaryTree<T>::Min() {
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
template <typename T>
T BinaryTree<T>::Max() {
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

