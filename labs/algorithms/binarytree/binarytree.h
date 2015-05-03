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

   private:
    T value_;
    MyNode<T>* left_;
    MyNode<T>* right_;

   public:
    MyNode<T>(T value);
};

template <typename T>
MyNode<T>::MyNode(T value)
    : left_(nullptr), right_(nullptr) {
    value_ = value;
}

// BinaryTree
template <typename T>
class BinaryTree {
   private:
    MyNode<T>* root_;

   public:
    BinaryTree<T>();
    void insert(T value);
    bool contains(T value);
    T min();
    T max();
    void traverse();
};

template <typename T>
BinaryTree<T>::BinaryTree()
    : root_(nullptr) {}

template <typename T>
void BinaryTree<T>::insert(T value) {
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
T BinaryTree<T>::min() {
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
T BinaryTree<T>::max() {
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

