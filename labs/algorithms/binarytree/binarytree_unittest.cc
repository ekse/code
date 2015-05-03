#include "gtest/gtest.h"
#include "binarytree.h"

namespace {

TEST(BinaryTree, Insertion) {
    auto tree = BinaryTree<int>();

    tree.insert(1);
    tree.insert(2);
    tree.insert(6);
    tree.insert(8);
    tree.insert(10);

    EXPECT_EQ(tree.min(), 1);
    EXPECT_EQ(tree.max(), 10);
}

}  // namespace

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
