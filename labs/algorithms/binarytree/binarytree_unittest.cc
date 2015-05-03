#include "gtest/gtest.h"
#include "binarytree.h"

namespace {

TEST(BinaryTree, empty) {
    auto tree = BinaryTree<int>();
    EXPECT_EQ(tree.empty(), true);

    tree.Insert(1);
    EXPECT_EQ(tree.empty(), false);
}

TEST(BinaryTree, Insert) {
    auto tree = BinaryTree<int>();

    tree.Insert(1);
    tree.Insert(2);
    tree.Insert(6);
    tree.Insert(8);
    tree.Insert(10);

    EXPECT_EQ(tree.min(), 1);
    EXPECT_EQ(tree.max(), 10);
}

}  // namespace

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
