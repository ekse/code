#include "gtest/gtest.h"
#include "binarytree.h"

namespace {

    TEST(BinaryTree, Contains) {
        auto tree = MyNode<int>(0);
        EXPECT_EQ(tree.Contains(1), false);

        tree.Insert(1);
        EXPECT_EQ(tree.Contains(0), true);
        EXPECT_EQ(tree.Contains(1), true);
        EXPECT_EQ(tree.Contains(2), false);
        EXPECT_EQ(tree.Contains(3), false);

        tree.Insert(2);
        EXPECT_EQ(tree.Contains(0), true);
        EXPECT_EQ(tree.Contains(1), true);
        EXPECT_EQ(tree.Contains(2), true);
        EXPECT_EQ(tree.Contains(3), false);
    }

    TEST(BinaryTree, Insert) {
        auto tree = MyNode<int>(1);
        tree.Insert(2);
        tree.Insert(6);
        tree.Insert(10);
        tree.Insert(8);

        EXPECT_EQ(tree.Min(), 1);
        EXPECT_EQ(tree.Max(), 10);
    }

}  // namespace
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
