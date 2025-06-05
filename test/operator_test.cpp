/**
 * @file operator_test.cpp
 * @brief Tests for overloaded operators of the SkipList class, including equality, copy assignment, and move assignment.
 * @details This file contains unit tests using the Google Test framework to ensure the correct behavior
 */

#include "gtest/gtest.h"
#include "../include/skip_list.h"

/// @brief Constant for number 2.
const std::size_t TWO = 2;

/// @brief Constant for number 3.
const std::size_t THREE = 3;

// EQUALITY
/**
 * @brief Test for the equality operator with two empty SkipLists.
 */
TEST(SkipListOperatorTest, Equality_EmptyList) {
    SkipList<int> list;
    SkipList<int> other_list;

    EXPECT_TRUE(list == other_list);
}

/**
 * @brief Test for the equality operator with two identical SkipLists.
 */
TEST(SkipListOperatorTest, Equality_IdenticalLists) {
    SkipList<int> list;
    SkipList<int> other_list;
    list.insert(10);
    list.insert(20);
    list.insert(30);

    other_list.insert(10);
    other_list.insert(20);
    other_list.insert(30);

    EXPECT_TRUE(list == other_list);
}

/**
 * @brief Test for the equality operator with SkipLists of different sizes.
 */
TEST(SkipListOperatorTest, Equality_DifferentSizes) {
    SkipList<int> list;
    SkipList<int> other_list;

    list.insert(10);
    list.insert(20);

    other_list.insert(10);
    other_list.insert(20);
    other_list.insert(30);

    EXPECT_FALSE(list == other_list);
}

/**
 * @brief Test for the equality operator with SkipLists containing different elements.
 */
TEST(SkipListOperatorTest, Equality_DifferentElements) {
    SkipList<int> list;
    SkipList<int> other_list;

    list.insert(10);
    list.insert(20);
    list.insert(30);

    other_list.insert(10);
    other_list.insert(20);
    other_list.insert(40);

    EXPECT_FALSE(list == other_list);
}

/**
 * @brief Test for the equality operator with SkipLists having elements inserted in a different order.
 */
TEST(SkipListOperatorTest, Equality_DifferentOrder) {
    SkipList<int> list;
    list.insert(30);
    list.insert(10);
    list.insert(20);

    SkipList<int> other_list;
    other_list.insert(20);
    other_list.insert(30);
    other_list.insert(10);

    EXPECT_TRUE(list == other_list);
}

// COPY ASSIGNMENT
/**
 * @brief Test for the copy assignment operator when assigning from an empty SkipList.
 */
TEST(SkipListOperatorTest, CopyAssignment_FromEmptyList) {
    SkipList<int> list;

    list.insert(1);
    list.insert(2);
    list.insert(3);

    SkipList<int> empty_list;
    list = empty_list;

    EXPECT_TRUE(list.empty());
    EXPECT_TRUE(list == empty_list);
}

/**
 * @brief Test for the copy assignment operator when assigning to an empty SkipList.
 */
TEST(SkipListOperatorTest, CopyAssignment_ToEmptyList) {
    SkipList<int> list;
    SkipList<int> other_list;
    other_list.insert(100);
    other_list.insert(200);

    list = other_list;

    EXPECT_EQ(list.size(), TWO);
    EXPECT_TRUE(list.contains(100));
    EXPECT_TRUE(list.contains(200));
    EXPECT_TRUE(list == other_list);
}

/**
 * @brief Test for the copy assignment operator when overwriting an existing SkipList.
 */
TEST(SkipListOperatorTest, CopyAssignment_Overwrite) {
    SkipList<int> list;
    list.insert(1);
    list.insert(2);

    SkipList<int> other_list;
    other_list.insert(10);
    other_list.insert(20);
    other_list.insert(30);

    list = other_list;

    EXPECT_EQ(list.size(), THREE);
    EXPECT_TRUE(list.contains(10));
    EXPECT_TRUE(list.contains(20));
    EXPECT_TRUE(list.contains(30));
    EXPECT_TRUE(list == other_list);
}

/**
 * @brief Test for the copy assignment operator followed by changes to the original list.
 */
TEST(SkipListOperatorTest, CopyAssignment_CopyThenChange) {
    SkipList<int> list;
    list.insert(10);
    list.insert(20);

    SkipList<int> other_list;
    other_list.insert(100);
    other_list.insert(200);

    list = other_list;

    other_list.insert(50);
    other_list.erase(200);

    EXPECT_EQ(other_list.size(), TWO);
    EXPECT_TRUE(other_list.contains(100));
    EXPECT_TRUE(other_list.contains(50));
    EXPECT_FALSE(other_list.contains(200));

    // list must not change
    EXPECT_EQ(list.size(), TWO);
    EXPECT_TRUE(list.contains(100));
    EXPECT_TRUE(list.contains(200));
    EXPECT_FALSE(list.contains(50));

    EXPECT_FALSE(list == other_list);
}

/**
 * @brief Test for the copy assignment operator with self-assignment.
 */
TEST(SkipListOperatorTest, CopyAssignment_CopyToSelf) {
    SkipList<int> list;
    list.insert(10);
    list.insert(20);
    list.insert(30);
    size_t original_size = list.size();

    // DELIBERATE CHOICE FOR TEST
    list = list;

    EXPECT_EQ(list.size(), original_size);
    EXPECT_TRUE(list.contains(10));
    EXPECT_TRUE(list.contains(20));
    EXPECT_TRUE(list.contains(30));
}

// MOVE
/**
 * @brief Test for the move assignment operator when assigning to an empty SkipList.
 */
TEST(SkipListOperatorTest, MoveAssignment_ToEmptyList) {
    SkipList<int> list;
    SkipList<int> original_list;
    original_list.insert(10);
    original_list.insert(20);

    // DELIBERATE CHOICE FOR TEST
    list = std::move(original_list);

    EXPECT_EQ(list.size(), TWO);
    EXPECT_TRUE(list.contains(10));
    EXPECT_TRUE(list.contains(20));

    EXPECT_TRUE(original_list.empty());
}

/**
 * @brief Test for the move assignment operator when overwriting an existing SkipList.
 */
TEST(SkipListOperatorTest, MoveAssignment_Overwrite) {
    SkipList<int> list;
    list.insert(1);
    list.insert(2);

    SkipList<int> original_list;
    original_list.insert(10);
    original_list.insert(20);
    original_list.insert(30);

    // DELIBERATE CHOICE FOR TEST
    list = std::move(original_list);

    EXPECT_EQ(list.size(), THREE);
    EXPECT_TRUE(list.contains(10));
    EXPECT_TRUE(list.contains(20));
    EXPECT_TRUE(list.contains(30));

    EXPECT_TRUE(original_list.empty());
}

/**
 * @brief Test for the move assignment operator with self-assignment.
 */
TEST(SkipListOperatorTest, MoveAssignment_Self) {
    SkipList<int> list;
    list.insert(10);
    list.insert(20);
    list.insert(30);
    size_t original_size = list.size();

    // DELIBERATE CHOICE FOR TEST
    list = std::move(list);

    EXPECT_EQ(list.size(), original_size);
    EXPECT_TRUE(list.contains(10));
    EXPECT_TRUE(list.contains(20));
    EXPECT_TRUE(list.contains(30));
}