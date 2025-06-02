/**
 * @file skip_list_string_test.cpp
 * @brief Tests for the SkipList class using string as the data type.
 * @details This file contains unit tests for the SkipList class, specifically
 * testing its functionality with 'string' data types. It covers initialization,
 * insertion (single, multiple, ascending, descending, random, and duplicates),
 * containment checks, element erasure, and various lexicographical comparison operators
 * ('<', '>', '<=', '>=').
 */

#include "gtest/gtest.h"          
#include "../include/skip_list.h" 

#include <string>

/**
 * @brief Test fixture for SkipList<string> tests.
 * @details Provides a SkipList<string> instance and helper variables/functions
 * for consistent testing across multiple test cases.
 */
class SkipListStringTest : public ::testing::Test 
{
    protected:
        /// @brief SkipList object for testing with string values.
        SkipList<std::string> string_list;

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
        bool check_level_0(const std::vector<std::string>& expected_elements) 
        {
            std::vector<std::string> actual_elements;
            std::shared_ptr<Node<std::string>> current = string_list.get_first_node_at_0();

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
TEST_F(SkipListStringTest, Initialization) 
{
    EXPECT_EQ(ZERO, string_list.get_current_level());
    EXPECT_EQ(ZERO, string_list.size());
}

/**
 * @brief Test for inserting a single element into the SkipList.
 */
TEST_F(SkipListStringTest, Insert_SingleElement)
{
    string_list.insert("Word");

    ASSERT_TRUE(string_list.contains("Word"));
    EXPECT_EQ(ONE, string_list.size());
    EXPECT_TRUE(check_level_0({"Word"}));
}

/**
 * @brief Test for inserting multiple elements in ascending order.
 */
TEST_F(SkipListStringTest, Insert_MultipleElements_Ascending)
{
    string_list.insert("Apple");
    string_list.insert("Banana");
    string_list.insert("Cherry");

    ASSERT_TRUE(string_list.contains("Apple"));
    ASSERT_TRUE(string_list.contains("Banana"));
    ASSERT_TRUE(string_list.contains("Cherry"));

    EXPECT_EQ(THREE, string_list.size());
    EXPECT_TRUE(check_level_0({"Apple", "Banana", "Cherry"}));
}

/**
 * @brief Test for inserting multiple elements in descending order.
 */
TEST_F(SkipListStringTest, Insert_MultipleElements_Descdending)
{
    string_list.insert("Cherry");
    string_list.insert("Banana");
    string_list.insert("Apple");

    ASSERT_TRUE(string_list.contains("Apple"));
    ASSERT_TRUE(string_list.contains("Banana"));
    ASSERT_TRUE(string_list.contains("Cherry"));

    EXPECT_EQ(THREE, string_list.size());
    EXPECT_TRUE(check_level_0({"Apple", "Banana", "Cherry"}));
}

/**
 * @brief Test for inserting multiple elements in random order.
 */
TEST_F(SkipListStringTest, Insert_MultipleElements_Randomly)
{
    string_list.insert("Apple");
    string_list.insert("Cherry");
    string_list.insert("Banana");
    string_list.insert("Demon");
    string_list.insert("Helicopter");
    string_list.insert("Witch");

    ASSERT_TRUE(string_list.contains("Apple"));
    ASSERT_TRUE(string_list.contains("Banana"));
    ASSERT_TRUE(string_list.contains("Cherry"));
    ASSERT_TRUE(string_list.contains("Demon"));
    ASSERT_TRUE(string_list.contains("Helicopter"));
    ASSERT_TRUE(string_list.contains("Witch"));

    EXPECT_EQ(THREE + THREE, string_list.size());
    EXPECT_TRUE(check_level_0({"Apple", "Banana", "Cherry", "Demon", "Helicopter", "Witch"}));
}

/**
 * @brief Test for inserting a duplicate element.
 */
TEST_F(SkipListStringTest, Insert_DublicateElement)
{
    string_list.insert("Apple");
    string_list.insert("Banana");

    ASSERT_TRUE(string_list.contains("Apple"));
    ASSERT_TRUE(string_list.contains("Banana"));

    EXPECT_EQ(TWO, string_list.size());

    string_list.insert("Apple");
    EXPECT_EQ(TWO, string_list.size());
    EXPECT_TRUE(check_level_0({"Apple", "Banana"}));
}

/**
 * @brief Test for 'contains()' on an empty SkipList.
 */
TEST_F(SkipListStringTest, Contains_EmptyList) 
{
    EXPECT_FALSE(string_list.contains("Apple"));
}

/**
 * @brief Test for 'contains()' with existing elements.
 */
TEST_F(SkipListStringTest, Contains_FewExisting)
{
    string_list.insert("Apple");
    string_list.insert("Banana");

    EXPECT_TRUE(string_list.contains("Apple"));
    EXPECT_TRUE(string_list.contains("Banana"));
}

/**
 * @brief Test for 'contains()' with not existing elements.
 */
TEST_F(SkipListStringTest, Contains_FewNotExisting)
{
    string_list.insert("Apple");
    string_list.insert("Banana");

    EXPECT_FALSE(string_list.contains("Cherry"));
    EXPECT_FALSE(string_list.contains("Dragonfruit"));
}

/**
 * @brief Test for erasing existing elements from the SkipList.
 */
TEST_F(SkipListStringTest, Erase_ExistingElements) 
{
    string_list.insert("Apple");
    string_list.insert("Banana");
    string_list.insert("Cherry");
    string_list.insert("Dragonfruit"); 

    EXPECT_TRUE(string_list.contains("Apple"));
    EXPECT_TRUE(string_list.erase("Apple")); 
    EXPECT_FALSE(string_list.contains("Apple")); 
    EXPECT_TRUE(check_level_0({"Banana", "Cherry", "Dragonfruit"})); 
    EXPECT_EQ(THREE, string_list.size()); 
}

/**
 * @brief Test for erasing not existing elements from the SkipList.
 */
TEST_F(SkipListStringTest, Erase_NotExistingElements)
{
    string_list.insert("Apple");
    string_list.insert("Banana");

    ASSERT_FALSE(string_list.erase("Cherry"));

    EXPECT_TRUE(string_list.contains("Apple"));
    EXPECT_TRUE(string_list.contains("Banana"));

    EXPECT_TRUE(check_level_0({"Apple", "Banana"}));
    EXPECT_EQ(TWO, string_list.size());
}

/**
 * @brief Test for erasing from an empty SkipList.
 */
TEST_F(SkipListStringTest, Erase_EmptyList)
{
    ASSERT_FALSE(string_list.erase("Apple"));
    EXPECT_TRUE(check_level_0({}));
    EXPECT_EQ(ZERO, string_list.size());
}



// Lexicographic operators
// <
/**
 * @brief Test for '<' (less than) with an empty list compared to a not empty list.
 */
TEST_F(SkipListStringTest, Operator_LessThan_EmptyVsNotEmpty)
{
    SkipList<std::string> other_list;
    other_list.insert("Apple");
    EXPECT_TRUE(string_list < other_list);
    EXPECT_FALSE(other_list < string_list);
}

/**
 * @brief Test for '<' (less than) with two lists where one is less than the other.
 */
TEST_F(SkipListStringTest, Operator_LessThan_TwoDifferent)
{
    string_list.insert("Apple");
    string_list.insert("Banana");

    SkipList<std::string> other_list;
    other_list.insert("Apple");
    other_list.insert("Banana");
    other_list.insert("Cherry");

    EXPECT_TRUE(string_list < other_list);
    EXPECT_FALSE(other_list < string_list);
}

/**
 * @brief Test for '<'(less than) with two lists where one is greater than other.
 */
TEST_F(SkipListStringTest, Operator_LessThan_LessVsGreater)
{
    string_list.insert("Apple");
    string_list.insert("Banana");
    string_list.insert("Cherry");

    SkipList<std::string> other_list;
    other_list.insert("Apple");
    other_list.insert("Banana");
    other_list.insert("Berry"); 

    EXPECT_TRUE(other_list < string_list);
    EXPECT_FALSE(string_list < other_list);
}

// >
/**
 * @brief Test for '>' (greater than) with a non-empty list compared to an empty list.
 */
TEST_F(SkipListStringTest, Operator_GreaterThan_EmptyVsNotEmpty)
{
    SkipList<std::string> other_list;
    string_list.insert("Apple");
    EXPECT_TRUE(string_list > other_list);
    EXPECT_FALSE(other_list > string_list);
}

/**
 * @brief Test for '>' (greater than) with two lists where one is less than the other.
 */
TEST_F(SkipListStringTest, Operator_GreaterThan_TwoDifferent)
{
    string_list.insert("Apple");
    string_list.insert("Banana");
    string_list.insert("Cherry");

    SkipList<std::string> other_list;
    other_list.insert("Apple");
    other_list.insert("Banana");

    EXPECT_TRUE(string_list > other_list);
    EXPECT_FALSE(other_list > string_list);
}

/**
 * @brief Test for '>' (greater than) with two lists where one is greater than the other.
 */
TEST_F(SkipListStringTest, Operator_GreaterThan_LessVsGreater)
{
    string_list.insert("Apple");
    string_list.insert("Banana");
    string_list.insert("Cherry");

    SkipList<std::string> other_list;
    other_list.insert("Apple");
    other_list.insert("Banana");
    other_list.insert("Berry");

    EXPECT_TRUE(string_list > other_list);
    EXPECT_FALSE(other_list > string_list);
}

// <=
/**
 * @brief Test for '<=' (less than or equal to) with two identical lists.
 */
TEST_F(SkipListStringTest, Operator_LessOrEqual_Identical)
{
    string_list.insert("Apple");
    string_list.insert("Banana");

    SkipList<std::string> other_list(string_list); 

    EXPECT_TRUE(string_list <= other_list);
    EXPECT_TRUE(other_list <= string_list);
}

/**
 * @brief Test for '<=' (less than or equal to) where one is less than other.
 */
TEST_F(SkipListStringTest, Operator_LessOrEqual_LessVsGreater)
{
    string_list.insert("Apple");
    string_list.insert("Banana");

    SkipList<std::string> other_list;
    other_list.insert("Apple");
    other_list.insert("Banana");
    other_list.insert("Cherry");

    EXPECT_TRUE(string_list <= other_list);
    EXPECT_FALSE(other_list <= string_list);
}

// >=
/**
 * @brief Test for '>=' (less than or equal to) with two identical lists.
 */
TEST_F(SkipListStringTest, Operator_GreaterOrEqual_Identical)
{
    string_list.insert("Apple");
    string_list.insert("Banana");

    SkipList<std::string> other_list(string_list);

    EXPECT_TRUE(string_list >= other_list);
    EXPECT_TRUE(other_list >= string_list);
}

/**
 * @brief Test for '<=' (less than or equal ti ) where one is less than other.
 */
TEST_F(SkipListStringTest, Operator_GreaterOrEqual_LessVsGreater)
{
    string_list.insert("Apple");
    string_list.insert("Banana");
    string_list.insert("Cherry");

    SkipList<std::string> other_list;
    other_list.insert("Apple");
    other_list.insert("Banana");
    
    EXPECT_TRUE(string_list >= other_list);
    EXPECT_FALSE(other_list >= string_list);
}
