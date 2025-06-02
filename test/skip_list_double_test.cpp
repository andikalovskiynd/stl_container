/**
 * @file skip_list_double_test.cpp
 * @brief Tests for the SkipList class using double as the data type.
 * @details This file contains unit tests for the SkipList class, specifically
 * testing its functionality with 'double' data types. It covers initialization,
 * insertion (single, multiple, ascending, descending, random, and duplicates),
 * containment checks, and various lexicographical comparison operators
 * ('<', '>', '<=', '>=').
 */

#include "gtest/gtest.h"          
#include "../include/skip_list.h" 

/**
 * @brief Test fixture for SkipList<double> tests.
 * @details Provides a SkipList<double> instance and helper variables/functions
 * for consistent testing across multiple test cases.
 */
class SkipListDoubleTest : public ::testing::Test 
{
    protected:
        /// @brief SkipList object for testing with double values.
        SkipList<double> double_list;

        /// @brief Constant for number 0.
        const std::size_t ZERO = 0;

        /// @brief Constant for number 1.
        const std::size_t ONE = 1;

        /// @brief Constant for number 2.
        const std::size_t TWO = 2;

        /// @brief Constant for number 3.
        const std::size_t THREE = 3;

        /// @brief Helper function to check elements at level 0 of the SkipList.
        /// @param expected_elements A vector of doubles representing the expected elements in sorted order at level 0.
        /// @return True if the elements at level 0 match the expected elements, false otherwise.
        bool check_level_0(const std::vector<double>& expected_elements) 
        {
            std::vector<double> actual_elements;
            std::shared_ptr<Node<double>> current = double_list.get_first_node_at_0();

            while (current != nullptr) 
            {
                actual_elements.push_back(current->getValue());
                current = current->next[0];
            }

            return expected_elements == actual_elements;
        }
};

/**
 * @brief Test for SkipList initialization.
 */
TEST_F(SkipListDoubleTest, Initialization) 
{
    EXPECT_EQ(ZERO, double_list.get_current_level());
    EXPECT_EQ(ZERO, double_list.size());
}

/**
 * @brief Test for inserting a single element into the SkipList.
 */
TEST_F(SkipListDoubleTest, Insert_SingleElement)
{
    double_list.insert(10.75892);

    ASSERT_TRUE(double_list.contains(10.75892));
    EXPECT_EQ(ONE, double_list.size());
    EXPECT_TRUE(check_level_0({10.75892}));
}

/**
 * @brief Test for inserting multiple elements in ascending order.
 */
TEST_F(SkipListDoubleTest, Insert_MultipleElements_Ascending)
{
    double_list.insert(10.75892);
    double_list.insert(20.4432);
    double_list.insert(20.5566);

    ASSERT_TRUE(double_list.contains(10.75892));
    ASSERT_TRUE(double_list.contains(20.4432));
    ASSERT_TRUE(double_list.contains(20.5566));

    EXPECT_EQ(THREE, double_list.size());
    EXPECT_TRUE(check_level_0({10.75892, 20.4432, 20.5566}));
}

/**
 * @brief Test for inserting multiple elements in descending order.
 */
TEST_F(SkipListDoubleTest, Insert_MultipleElements_Descdending)
{
    double_list.insert(20.5566);
    double_list.insert(20.4432);
    double_list.insert(10.75892);

    ASSERT_TRUE(double_list.contains(10.75892));
    ASSERT_TRUE(double_list.contains(20.4432));
    ASSERT_TRUE(double_list.contains(20.5566));

    EXPECT_EQ(THREE, double_list.size());
    EXPECT_TRUE(check_level_0({10.75892, 20.4432, 20.5566}));
}

/**
 * @brief Test for inserting multiple elements in random order.
 */
TEST_F(SkipListDoubleTest, Insert_MultipleElements_Randomly)
{
    double_list.insert(13.674554);
    double_list.insert(5.55543);
    double_list.insert(1.0001);
    double_list.insert(22.4432);
    double_list.insert(110.75892);
    double_list.insert(79.6667);

    ASSERT_TRUE(double_list.contains(13.674554));
    ASSERT_TRUE(double_list.contains(5.55543));
    ASSERT_TRUE(double_list.contains(1.0001));
    ASSERT_TRUE(double_list.contains(22.4432));
    ASSERT_TRUE(double_list.contains(110.75892));
    ASSERT_TRUE(double_list.contains(79.6667));

    EXPECT_EQ(THREE + THREE, double_list.size());
    EXPECT_TRUE(check_level_0({1.0001, 5.55543, 13.674554, 22.4432, 79.6667, 110.75892}));
}

/**
 * @brief Test for inserting a duplicate element.
 */
TEST_F(SkipListDoubleTest, Insert_DublicateElement)
{
    double_list.insert(10.75892);
    double_list.insert(20.5656);

    ASSERT_TRUE(double_list.contains(10.75892));
    ASSERT_TRUE(double_list.contains(20.5656));

    EXPECT_EQ(TWO, double_list.size());

    double_list.insert(10.75892);
    EXPECT_EQ(TWO, double_list.size());
    EXPECT_TRUE(check_level_0({10.75892, 20.5656}));
}

/**
 * @brief Test for 'contains()' on an empty SkipList.
 */
TEST_F(SkipListDoubleTest, Contains_EmptyList) 
{
    EXPECT_FALSE(double_list.contains(10.4321));
}

/**
 * @brief Test for 'contains()' with existing elements.
 */
TEST_F(SkipListDoubleTest, Contains_FewExisting)
{
    double_list.insert(10.555);
    double_list.insert(20.121);

    EXPECT_TRUE(double_list.contains(10.555));
    EXPECT_TRUE(double_list.contains(20.121));
}

/**
 * @brief Test for 'contains()' with not existing elements.
 */
TEST_F(SkipListDoubleTest, Contains_FewNotExisting)
{
    double_list.insert(10.443);
    double_list.insert(20.443);

    EXPECT_FALSE(double_list.contains(10.444));
    EXPECT_FALSE(double_list.contains(20.444));
}

/**
 * @brief Test for erasing existing elements from the SkipList.
 */
TEST_F(SkipListDoubleTest, Erase_ExistingElements) 
{
    double_list.insert(10.1);
    double_list.insert(20.1);
    double_list.insert(30.1);
    double_list.insert(15.1); 

    EXPECT_TRUE(double_list.contains(20.1));
    EXPECT_TRUE(double_list.erase(20.1)); 
    EXPECT_FALSE(double_list.contains(20.1)); 
    EXPECT_TRUE(check_level_0({10.1, 15.1, 30.1})); 
    EXPECT_EQ(THREE, double_list.size()); 
}

/**
 * @brief Test for erasing not existing elements from the SkipList.
 */
TEST_F(SkipListDoubleTest, Erase_NotExistingElements)
{
    double_list.insert(10.1);
    double_list.insert(15.1);

    ASSERT_FALSE(double_list.erase(20.1));

    EXPECT_TRUE(double_list.contains(10.1));
    EXPECT_TRUE(double_list.contains(15.1));

    EXPECT_TRUE(check_level_0({10.1, 15.1}));
    EXPECT_EQ(TWO, double_list.size());
}

/**
 * @brief Test for erasing from an empty SkipList.
 */
TEST_F(SkipListDoubleTest, Erase_EmptyList)
{
    ASSERT_FALSE(double_list.erase(10));
    EXPECT_TRUE(check_level_0({}));
    EXPECT_EQ(ZERO, double_list.size());
}

// Lexicographic 
// <
/**
 * @brief Test for '<' (less than) with an empty list compared to a not empty list.
 */
TEST_F(SkipListDoubleTest, Operator_LessThan_EmptyVsNotEmpty)
{
    SkipList<double> other_list;
    other_list.insert(10.5); 
    EXPECT_TRUE(double_list < other_list);
    EXPECT_FALSE(other_list < double_list);
}

/**
 * @brief Test for '<' (less than) with two lists where one is less than the other.
 */
TEST_F(SkipListDoubleTest, Operator_LessThan_TwoDifferent)
{
    double_list.insert(10.0);
    double_list.insert(20.0);

    SkipList<double> other_list;
    other_list.insert(10.0);
    other_list.insert(20.0);
    other_list.insert(30.0);

    EXPECT_TRUE(double_list < other_list);
    EXPECT_FALSE(other_list < double_list);
}

/**
 * @brief Test for '<'(less than) with two lists where one is greater than other.
 */
TEST_F(SkipListDoubleTest, Operator_LessThan_LessVsGreater)
{
    double_list.insert(10.0);
    double_list.insert(20.0);
    double_list.insert(30.0);

    SkipList<double> other_list;
    other_list.insert(10.0);
    other_list.insert(20.0);
    other_list.insert(25.5); 

    EXPECT_TRUE(other_list < double_list); 
    EXPECT_FALSE(double_list < other_list);
}

// >
/**
 * @brief Test for '>' (greater than) with a non-empty list compared to an empty list.
 */
TEST_F(SkipListDoubleTest, Operator_GreaterThan_EmptyVsNotEmpty)
{
    SkipList<double> other_list;
    double_list.insert(10.5);
    EXPECT_TRUE(double_list > other_list);
    EXPECT_FALSE(other_list > double_list);
}

/**
 * @brief Test for '>' (greater than) with two lists where one is less than the other.
 */
TEST_F(SkipListDoubleTest, Operator_GreaterThan_TwoDifferent)
{
    double_list.insert(10.0);
    double_list.insert(20.0);
    double_list.insert(30.0);

    SkipList<double> other_list;
    other_list.insert(10.0);
    other_list.insert(20.0);

    EXPECT_TRUE(double_list > other_list);
    EXPECT_FALSE(other_list > double_list);
}

/**
 * @brief Test for '>' (greater than) with two lists where one is greater than the other.
 */
TEST_F(SkipListDoubleTest, Operator_GreaterThan_LessVsGreater)
{
    double_list.insert(10.0);
    double_list.insert(20.0);
    double_list.insert(30.0); 

    SkipList<double> other_list;
    other_list.insert(10.0);
    other_list.insert(20.0);
    other_list.insert(25.5); 

    EXPECT_TRUE(double_list > other_list);
    EXPECT_FALSE(other_list > double_list);
}

// <=
/**
 * @brief Test for '<=' (less than or equal to) with two identical lists.
 */
TEST_F(SkipListDoubleTest, Operator_LessOrEqual_Identical)
{
    double_list.insert(10.0);
    double_list.insert(20.0);

    SkipList<double> other_list(double_list); 

    EXPECT_TRUE(double_list <= other_list);
    EXPECT_TRUE(other_list <= double_list);
}

/**
 * @brief Test for '<=' (less than or equal to) where one is less than other.
 */
TEST_F(SkipListDoubleTest, Operator_LessOrEqual_LessVsGreater)
{
    double_list.insert(10.0);
    double_list.insert(20.0);

    SkipList<double> other_list;
    other_list.insert(10.0);
    other_list.insert(20.0);
    other_list.insert(30.0);

    EXPECT_TRUE(double_list <= other_list);
    EXPECT_FALSE(other_list <= double_list);
}

// >=
/**
 * @brief Test for '>=' (less than or equal to) with two identical lists.
 */
TEST_F(SkipListDoubleTest, Operator_GreaterOrEqual_Identical)
{
    double_list.insert(10.0);
    double_list.insert(20.0);

    SkipList<double> other_list(double_list);

    EXPECT_TRUE(double_list >= other_list);
    EXPECT_TRUE(other_list >= double_list);
}

/**
 * @brief Test for '<=' (less than or equal ti ) where one is less than other.
 */
TEST_F(SkipListDoubleTest, Operator_GreaterOrEqual_LessVsGreater)
{
    double_list.insert(10.0);
    double_list.insert(20.0);
    double_list.insert(30.0);

    SkipList<double> other_list;
    other_list.insert(10.0);
    other_list.insert(20.0);
    
    EXPECT_TRUE(double_list >= other_list);
    EXPECT_FALSE(other_list >= double_list);
}