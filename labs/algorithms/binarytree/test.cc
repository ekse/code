#include "binarytree.h"
#include <stdio.h>

int main(int argc, char* argv[])
{
    auto tree = BinaryTree();
    
    tree.insert(1);
    tree.insert(2);
    tree.insert(6);
    tree.insert(8);
    tree.insert(10);
    
    printf("min: %d\n", tree.min());
    printf("max: %d\n", tree.max());

    return(0);
}
