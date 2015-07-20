#include <cstddef>
#pragma once

/* TODO:
 - make BinaryTree an abstract class and AVLTree a subclass.
 - implement Traverse() iterator

 * This class implements an AVL tree.
 *
 *The balance_factor of a node is calculated as height(left_subtree) -
 *height(right_subtree). For a balanced tree the balance_factor of all nodes
 *needs to be in interval (-1,+1). When this range is exceeded, a rotation needs
 *to be done on the subtree.
 */

template <typename T>
class MyNode {
   public:
    MyNode<T>(T value);
    void Insert(T value);
    bool Contains(T value);
    MyNode<T>* RotateLeft();
    MyNode<T>* RotateRight();
    T Min();
    T Max();
    // void traverse(); -- not implemented yet

    static int Height(MyNode<T>* p) { return p ? p->height_:0;};
    static int BalanceFactor(MyNode<T>* p) { return Height(p->right_) - Height(p->left_); }

   private:
    T value_;
    MyNode<T>* parent_;
    MyNode<T>* left_;
    MyNode<T>* right_;
    int height_;

    void FixHeight();
    MyNode<T>* Balance();
};

template <typename T>
MyNode<T>::MyNode(T value)
    : left_(nullptr), right_(nullptr), parent_(nullptr), height_(1) {
    value_ = value;
}

template <typename T>
MyNode<T>* MyNode<T>::RotateLeft() {
    MyNode<T>* p = this;
    MyNode<T>* q = p->right_;
    p->right_ = q->left_;
    q->left_ = p;
    p->FixHeight();
    q->FixHeight();
    return q;
}

template <typename T>
MyNode<T>* MyNode<T>::RotateRight() {
    MyNode<T>* p = this;
    MyNode<T>* q = p->left_;
    p->left_ = q->right_;
    q->right_ = p;
    p->FixHeight();
    q->FixHeight();
    return q;
}

template <typename T>
void MyNode<T>::FixHeight() {
    int height_left = Height(left_);
    int height_right = Height(right_);
    height_ = (height_left > height_right ? height_left : height_right) + 1;
}

template<typename T>
MyNode<T> *MyNode<T>::Balance() {
    MyNode<T> *p = this;
    FixHeight();
    if (BalanceFactor(p) == 2) {
        if (BalanceFactor(right_) < 0)
            right_ = p->right_->RotateRight();
        return (p->RotateLeft());
    }

    if (BalanceFactor(p) == -2) {
        if (BalanceFactor(left_) > 0)
            left_ = p->left_->RotateLeft();
        return (p->RotateRight());
    }
    return this; // no balance needed
}

template<typename T>
bool MyNode<T>::Contains(T value) {

    auto cur_node = this;

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
void MyNode<T>::Insert(T value) {
    MyNode<T>* node = new MyNode<T>(value);

    auto cur_node = this;

    while (true) {
        if (value < cur_node->value_) {
            if (cur_node->left_ == nullptr) {
                cur_node->left_ = node;
                node->parent_ = cur_node;
                break;
            }
            cur_node = cur_node->left_;
        } else {
            if (cur_node->right_ == nullptr) {
                cur_node->right_ = node;
                node->parent_ = cur_node;
                break;
            }
            cur_node = cur_node->right_;
        }
    }

    Balance();
}

// default min value is 0
template <typename T>
T MyNode<T>::Min() {

    auto cur_node = this;

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
T MyNode<T>::Max() {
    auto cur_node = this;

    while (true) {
        if (cur_node->right_ == nullptr) {
            break;
        }
        cur_node = cur_node->right_;
    }

    return (cur_node->value_);
}

