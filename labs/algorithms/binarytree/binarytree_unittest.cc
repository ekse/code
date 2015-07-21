#include "gtest/gtest.h"
#include "binarytree.h"

namespace {

    TEST(BinaryTree, Contains) {
        auto tree = BinaryTree<int>();
        EXPECT_EQ(tree.Contains(0), false);

        tree.Insert(1);
        EXPECT_EQ(tree.Contains(0), false);
        EXPECT_EQ(tree.Contains(1), true);
        EXPECT_EQ(tree.Contains(2), false);
        EXPECT_EQ(tree.Contains(3), false);

        tree.Insert(2);
        EXPECT_EQ(tree.Contains(0), false);
        EXPECT_EQ(tree.Contains(1), true);
        EXPECT_EQ(tree.Contains(2), true);
        EXPECT_EQ(tree.Contains(3), false);
    }

    TEST(BinaryTree, Balanced) {
        auto tree = BinaryTree<int>();
        tree.Insert(2);
        tree.Insert(6);
        tree.Insert(10);
        tree.Insert(8);

        EXPECT_EQ(tree.Contains(2), true);
        EXPECT_EQ(tree.Contains(6), true);
        EXPECT_EQ(tree.Contains(8), true);
        EXPECT_EQ(tree.Contains(10), true);

        EXPECT_EQ(tree.IsBalanced(), true);


    }

}  // namespace
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
