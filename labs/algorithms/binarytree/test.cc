#include <cstddef>
#include <iostream>
#include "binarytree.h"


using namespace std;

int main(int argc, char* argv[]) {
    auto tree = new BinaryTree<int>();
    tree->Insert(4);
    tree->Print(); std::cout << endl;

    tree->Insert(1);
    tree->Print(); std::cout << endl;

    tree->Insert(2);
    tree->Print(); std::cout << endl;

    tree->Insert(10);
    tree->Print(); std::cout << endl;



    return 0;
}
