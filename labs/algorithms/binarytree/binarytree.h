#pragma once

// TODO: template value instead of int

class MyNode {
    friend class BinaryTree;
    
    private:
        int value;
        MyNode* left;
        MyNode* right;
    public:
        MyNode(int v);
};

class BinaryTree {
    private:
        MyNode* root;
    
    public:
        BinaryTree();
        void insert(int v);
        bool contains(int v);
        int min();
        int max();
        void traverse();

};

