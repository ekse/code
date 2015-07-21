#include <cstddef>
#include <iostream>

#pragma once

/*
 * This class implements an AVL tree.
 * Heavily based on http://kukuruku.co/hub/cpp/avl-trees.
 *
 *The balance_factor of a node is calculated as height(left_subtree) -
 *height(right_subtree). For a balanced tree the balance_factor of all nodes
 *needs to be in interval (-1,+1). When this range is exceeded, a rotation needs
 *to be done on the subtree.
 */


template<typename T>
class BinaryTree;

template<typename T>
class MyNode {

    friend class BinaryTree<T>;

public:
    MyNode<T>(const T &value);

    void Insert(const T &value);

    bool Contains(const T &value) const;

    const T &Min() const;

    const T &Max() const;

private:
    T value_;
    MyNode<T> *parent_;
    MyNode<T> *left_;
    MyNode<T> *right_;
    int height_;

    static int Height(MyNode<T> *p) { return p ? p->height_ : 0; };

    static int BalanceFactor(MyNode<T> *p) { return Height(p->right_) - Height(p->left_); }

    static MyNode<T> *insert(MyNode *p, const T &value) {
        if (!p)
            return new MyNode<T>(value);
        if (value < p->value_) {
            p->left_ = insert(p->left_, value);
        }
        else {
            p->right_ = insert(p->right_, value);
        };
        return p->Balance();
    }

    void FixHeight();

    MyNode<T> *Balance();

    MyNode<T> *RotateLeft();

    MyNode<T> *RotateRight();
};

template<typename T>
MyNode<T>::MyNode(const T &value)
        : left_(nullptr), right_(nullptr), parent_(nullptr), height_(1) {
    value_ = value;
}

template<typename T>
MyNode<T> *MyNode<T>::RotateLeft() {
    MyNode<T> *p = this;
    MyNode<T> *q = p->right_;
    p->right_ = q->left_;
    q->left_ = p;
    p->FixHeight();
    q->FixHeight();
    return q;
}

template<typename T>
MyNode<T> *MyNode<T>::RotateRight() {
    MyNode<T> *p = this;
    MyNode<T> *q = p->left_;
    p->left_ = q->right_;
    q->right_ = p;
    p->FixHeight();
    q->FixHeight();
    return q;
}

template<typename T>
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
    return this;
}

template<typename T>
bool MyNode<T>::Contains(const T &value) const {

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

template<typename T>
const T &MyNode<T>::Min() const {

    auto cur_node = this;

    while (true) {
        if (cur_node->left_ == nullptr) {
            break;
        }
        cur_node = cur_node->left_;
    }
    return (cur_node->value_);
}

template<typename T>
const T &MyNode<T>::Max() const {
    auto cur_node = this;

    while (true) {
        if (cur_node->right_ == nullptr) {
            break;
        }
        cur_node = cur_node->right_;
    }

    return (cur_node->value_);
}

template<typename T>
void MyNode<T>::Insert(const T &value) {
    insert(this, value);
}


template<typename T>
class BinaryTree {
public:
    BinaryTree<T>();

    void Insert(const T &value);

    bool Contains(const T &value) const;

    void Print() const;

    void PrintBalanceFactors() const;

    bool IsBalanced() const;

private:
    MyNode<T> *root_;

    static void print_node(MyNode<T> *p) {
        if (p) {
            print_node(p->left_);
            std::cout << p->value_ << " ";
            print_node(p->right_);
        }
    }

    static void print_balance_factors(MyNode<T> *p) {
        if (p) {
            print_balance_factors(p->left_);
            std::cout << p->value_ << " (" << MyNode<T>::BalanceFactor(p) << ")" << std::endl;
            print_balance_factors(p->right_);
        }
    }

    static bool is_balanced(MyNode<T> *p) {
        if (p) {
            auto node_balance_factor = MyNode<T>::BalanceFactor(p);
            return (node_balance_factor <= 1 && node_balance_factor >= -1)
                   && is_balanced(p->left_)
                   && is_balanced(p->right_);
        }
        return true;
    }

};

template<typename T>
BinaryTree<T>::BinaryTree() : root_(nullptr) { }

template<typename T>
void BinaryTree<T>::Insert(const T &value) {
    root_ = !root_ ? new MyNode<T>(value) : MyNode<T>::insert(root_, value);
}

template<typename T>
bool BinaryTree<T>::Contains(const T &value) const {
    return !root_ ? false : root_->Contains(value);
}

template<typename T>
void BinaryTree<T>::Print() const {
    if (root_) {
        BinaryTree<T>::print_node(root_);
    }
}

template<typename T>
void BinaryTree<T>::PrintBalanceFactors() const {
    if (root_) {
        BinaryTree<T>::print_balance_factors(root_);
    }
}

template<typename T>
bool BinaryTree<T>::IsBalanced() const {
    return BinaryTree<T>::is_balanced(root_);
}
