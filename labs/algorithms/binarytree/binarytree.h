#pragma once

// TODO: template value instead of int

class MyNode {
    friend class BinaryTree;
    
    private:
        int value_;
        MyNode* left_;
        MyNode* right_;
    public:
        MyNode(int value);
};

class BinaryTree {
    private:
        MyNode* root_;
    
    public:
        BinaryTree();
        void insert(int value);
        bool contains(int value);
        int min();
        int max();
        void traverse();

};
