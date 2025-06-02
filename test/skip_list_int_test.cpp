/**
 * @file skip_list_int_test.cpp
 * @brief Tests for the SkipList class using int as the data type.
 * @details This file contains unit tests for the SkipList class, specifically
 * testing its functionality with 'int' data types. It covers initialization,
 * insertion (single, multiple, ascending, descending, random, and duplicates),
 * containment checks, element erasure, and various lexicographical comparison operators
 * ('<', '>', '<=', '>=').
 */

#include "gtest/gtest.h"
#include "../include/skip_list.h"

/**
 * @brief Test fixture for SkipList<int> tests.
 * @details Provides a SkipList<int> instance and helper variables/functions
 * for consistent testing across multiple test cases.
 */
class SkipListIntTest : public ::testing::Test {
  protected:
    /// @brief SkipList object for testing with int values.
    SkipList<int> int_list;

    /// @brief Constant for number 0.
    const std::size_t ZERO = 0;

    /// @brief Constant for number 1.
    const std::size_t ONE = 1;

    /// @brief Constant for number 2.
    const std::size_t TWO = 2;

    /// @brief Constant for number 3.
    const std::size_t THREE = 3;

    /// @brief Helper function to check elements at level 0 of the SkipList.
    /// @param expected_elements A vector of ints representing the expected elements in sorted order at level 0.
    /// @return True if the elements at level 0 match the expected elements, false otherwise.
    bool check_level_0(const std::vector<int>& expected_elements) {
        std::vector<int> actual_elements;
        std::shared_ptr<Node<int>> current = int_list.get_first_node_at_0();

        while (current != nullptr) {
            actual_elements.push_back(current->getValue());
            current = current->next[0];
        }

        return expected_elements == actual_elements;
    }
};

/**
 * @brief Test for SkipList initialization.
 */
TEST_F(SkipListIntTest, Initialization) {
    EXPECT_EQ(ZERO, int_list.get_current_level());
    EXPECT_EQ(ZERO, int_list.size());
}

/**
 * @brief Test for inserting a single element into the SkipList.
 */
TEST_F(SkipListIntTest, Insert_SingleElement) {
    int_list.insert(10);

    ASSERT_TRUE(int_list.contains(10));
    EXPECT_EQ(ONE, int_list.size());
    EXPECT_TRUE(check_level_0({10}));
}

/**
 * @brief Test for inserting multiple elements in ascending order.
 */
TEST_F(SkipListIntTest, Insert_MultipleElements_Ascending) {
    int_list.insert(10);
    int_list.insert(20);
    int_list.insert(30);

    ASSERT_TRUE(int_list.contains(10));
    ASSERT_TRUE(int_list.contains(20));
    ASSERT_TRUE(int_list.contains(30));

    EXPECT_EQ(THREE, int_list.size());
    EXPECT_TRUE(check_level_0({10, 20, 30}));
}

/**
 * @brief Test for inserting multiple elements in descending order.
 */
TEST_F(SkipListIntTest, Insert_MultipleElements_Descdending) {
    int_list.insert(30);
    int_list.insert(20);
    int_list.insert(10);

    ASSERT_TRUE(int_list.contains(10));
    ASSERT_TRUE(int_list.contains(20));
    ASSERT_TRUE(int_list.contains(30));

    EXPECT_EQ(THREE, int_list.size());
    EXPECT_TRUE(check_level_0({10, 20, 30}));
}

/**
 * @brief Test for inserting multiple elements in random order.
 */
TEST_F(SkipListIntTest, Insert_MultipleElements_Randomly) {
    int_list.insert(13);
    int_list.insert(5);
    int_list.insert(1);
    int_list.insert(22);
    int_list.insert(110);
    int_list.insert(79);

    ASSERT_TRUE(int_list.contains(13));
    ASSERT_TRUE(int_list.contains(5));
    ASSERT_TRUE(int_list.contains(1));
    ASSERT_TRUE(int_list.contains(22));
    ASSERT_TRUE(int_list.contains(110));
    ASSERT_TRUE(int_list.contains(79));

    EXPECT_EQ(THREE + THREE, int_list.size());
    EXPECT_TRUE(check_level_0({1, 5, 13, 22, 79, 110}));
}

/**
 * @brief Test for inserting a duplicate element.
 */
TEST_F(SkipListIntTest, Insert_DublicateElement) {
    int_list.insert(10);
    int_list.insert(20);

    ASSERT_TRUE(int_list.contains(10));
    ASSERT_TRUE(int_list.contains(20));

    EXPECT_EQ(TWO, int_list.size());

    int_list.insert(10);
    EXPECT_EQ(TWO, int_list.size());
    EXPECT_TRUE(check_level_0({10, 20}));
}

/**
 * @brief Test for 'contains()' on an empty SkipList.
 */
TEST_F(SkipListIntTest, Contains_EmptyList) {
    EXPECT_FALSE(int_list.contains(10));
}

/**
 * @brief Test for 'contains()' with existing elements.
 */
TEST_F(SkipListIntTest, Contains_FewExisting) {
    int_list.insert(10);
    int_list.insert(20);

    EXPECT_TRUE(int_list.contains(10));
    EXPECT_TRUE(int_list.contains(20));
}

/**
 * @brief Test for 'contains()' with not existing elements.
 */
TEST_F(SkipListIntTest, Contains_FewNotExisting) {
    int_list.insert(10);
    int_list.insert(20);

    EXPECT_FALSE(int_list.contains(9));
    EXPECT_FALSE(int_list.contains(11));
}

/**
 * @brief Test for erasing existing elements from the SkipList.
 */
TEST_F(SkipListIntTest, Erase_ExistingElements) {
    int_list.insert(10);
    int_list.insert(20);
    int_list.insert(30);
    int_list.insert(15);

    EXPECT_TRUE(int_list.contains(20));
    EXPECT_TRUE(int_list.erase(20));
    EXPECT_FALSE(int_list.contains(20));
    EXPECT_TRUE(check_level_0({10, 15, 30}));
    EXPECT_EQ(THREE, int_list.size());
}

/**
 * @brief Test for erasing not existing elements from the SkipList.
 */
TEST_F(SkipListIntTest, Erase_NotExistingElements) {
    int_list.insert(10);
    int_list.insert(15);

    ASSERT_FALSE(int_list.erase(20));

    EXPECT_TRUE(int_list.contains(10));
    EXPECT_TRUE(int_list.contains(15));

    EXPECT_TRUE(check_level_0({10, 15}));
    EXPECT_EQ(TWO, int_list.size());
}

/**
 * @brief Test for erasing from an empty SkipList.
 */
TEST_F(SkipListIntTest, Erase_EmptyList) {
    ASSERT_FALSE(int_list.erase(10));
    EXPECT_TRUE(check_level_0({}));
    EXPECT_EQ(ZERO, int_list.size());
}

// Lexicographic operators
// <
/**
 * @brief Test for '<' (less than) with an empty list compared to a not empty list.
 */
TEST_F(SkipListIntTest, Operator_LessThan_EmptyVsNotEmpty) {
    SkipList<int> other_list;

    other_list.insert(10);

    EXPECT_TRUE(int_list < other_list);
    EXPECT_FALSE(other_list < int_list);
}

/**
 * @brief Test for '<' (less than) with two lists where one is less than the other.
 */
TEST_F(SkipListIntTest, Operator_LessThan_TwoDifferent) {
    int_list.insert(10);
    int_list.insert(20);

    SkipList<int> other_list;
    other_list.insert(10);
    other_list.insert(20);
    other_list.insert(30);

    EXPECT_TRUE(int_list < other_list);
    EXPECT_FALSE(other_list < int_list);
}

/**
 * @brief Test for '<'(less than) with two lists where one is greater than other.
 */
TEST_F(SkipListIntTest, Operator_LessThan_LessVsGreater) {
    int_list.insert(10);
    int_list.insert(20);
    int_list.insert(30);

    SkipList<int> other_list;
    other_list.insert(10);
    other_list.insert(20);
    other_list.insert(25);

    EXPECT_TRUE(other_list < int_list);
    EXPECT_FALSE(int_list < other_list);
}

// >
/**
 * @brief Test for '>' (greater than) with a non-empty list compared to an empty list.
 */
TEST_F(SkipListIntTest, Operator_GreaterThan_EmptyVsNotEmpty) {
    SkipList<int> other_list;

    int_list.insert(10);

    EXPECT_TRUE(int_list > other_list);
    EXPECT_FALSE(other_list > int_list);
}

/**
 * @brief Test for '>' (greater than) with two lists where one is less than the other.
 */
TEST_F(SkipListIntTest, Operator_GreaterThan_TwoDifferent) {
    int_list.insert(10);
    int_list.insert(20);
    int_list.insert(30);

    SkipList<int> other_list;
    other_list.insert(10);
    other_list.insert(20);

    EXPECT_TRUE(int_list > other_list);
    EXPECT_FALSE(other_list > int_list);
}

/**
 * @brief Test for '>' (greater than) with two lists where one is greater than the other.
 */
TEST_F(SkipListIntTest, Operator_GreaterThan_LessVsGreater) {
    int_list.insert(10);
    int_list.insert(20);
    int_list.insert(30);

    SkipList<int> other_list;
    other_list.insert(10);
    other_list.insert(20);
    other_list.insert(25);

    EXPECT_TRUE(int_list > other_list);
    EXPECT_FALSE(other_list > int_list);
}

// <=
/**
 * @brief Test for '<=' (less than or equal to) with two identical lists.
 */
TEST_F(SkipListIntTest, Operator_LessOrEqual_Identical) {
    int_list.insert(10);
    int_list.insert(20);

    SkipList<int> other_list(int_list);

    EXPECT_TRUE(int_list <= other_list);
    EXPECT_TRUE(other_list <= int_list);
}

/**
 * @brief Test for '<=' (less than or equal to) where one is less than other.
 */
TEST_F(SkipListIntTest, Operator_LessOrEqual_LessVsGreater) {
    int_list.insert(10);
    int_list.insert(20);

    SkipList<int> other_list;
    other_list.insert(10);
    other_list.insert(20);
    other_list.insert(30);

    EXPECT_TRUE(int_list <= other_list);
    EXPECT_FALSE(other_list <= int_list);
}

// >=
/**
 * @brief Test for '>=' (less than or equal to) with two identical lists.
 */
TEST_F(SkipListIntTest, Operator_GreaterOrEqual_Identical) {
    int_list.insert(10);
    int_list.insert(20);

    SkipList<int> other_list(int_list);

    EXPECT_TRUE(int_list >= other_list);
    EXPECT_TRUE(other_list >= int_list);
}

/**
 * @brief Test for '<=' (less than or equal ti ) where one is less than other.
 */
TEST_F(SkipListIntTest, Operator_GreaterOrEqual_LessVsGreater) {
    int_list.insert(10);
    int_list.insert(20);
    int_list.insert(30);

    SkipList<int> other_list;
    other_list.insert(10);
    other_list.insert(20);

    EXPECT_TRUE(int_list >= other_list);
    EXPECT_FALSE(other_list >= int_list);
}