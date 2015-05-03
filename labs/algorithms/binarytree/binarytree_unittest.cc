#include "gtest/gtest.h"
#include "binarytree.h"

namespace {

TEST(BinaryTree, IsEmpty) {
    auto tree = BinaryTree<int>();
    EXPECT_EQ(tree.IsEmpty(), true);

    tree.Insert(1);
    EXPECT_EQ(tree.IsEmpty(), false);
}

TEST(BinaryTree, Contains) {
    auto tree = BinaryTree<int>();
    EXPECT_EQ(tree.Contains(1), false);

    tree.Insert(1);
    EXPECT_EQ(tree.Contains(0), false);
    EXPECT_EQ(tree.Contains(1), true);
    EXPECT_EQ(tree.Contains(2), false);

    tree.Insert(2);
    EXPECT_EQ(tree.Contains(0), false);
    EXPECT_EQ(tree.Contains(1), true);
    EXPECT_EQ(tree.Contains(2), true);
}

TEST(BinaryTree, Insert) {
    auto tree = BinaryTree<int>();

    tree.Insert(1);
    tree.Insert(2);
    tree.Insert(6);
    tree.Insert(8);
    tree.Insert(10);

    EXPECT_EQ(tree.Min(), 1);
    EXPECT_EQ(tree.Max(), 10);
}

}  // namespace

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
