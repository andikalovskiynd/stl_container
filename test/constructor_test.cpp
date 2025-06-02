/**
 * @file constructor_test.cpp
 * @brief Tests for the copy and move constructors of the SkipList class.
 */

#include "gtest/gtest.h"
#include "../include/skip_list.h"

/// @brief Constant size_t for the number 2.
const std::size_t TWO = 2;

/// @brief Constant size_t for the number 3.
const std::size_t THREE = 3;

/**
 * @brief Test for the SkipList copy constructor with an empty list.
 */
TEST(SkipListCopyConstructor, EmptyList)
{   
    SkipList<int> list;

    SkipList<int> copied_list(list);

    EXPECT_TRUE(copied_list.empty());
    EXPECT_TRUE(list == copied_list); 
}

/**
 * @brief Test for the SkipList copy constructor with a not empty list.
 */
TEST(SkipListCopyConstructor, NotEmptyList)
{   
    SkipList<int> list;

    list.insert(10);
    list.insert(20);
    list.insert(30);

    SkipList<int> copied_list(list);

    EXPECT_EQ(copied_list.size(), THREE);
    EXPECT_TRUE(copied_list.contains(10));
    EXPECT_TRUE(copied_list.contains(20));
    EXPECT_TRUE(copied_list.contains(30));
    EXPECT_TRUE(list == copied_list); 
}

/**
 * @brief Test for the SkipList copy constructor: copy, then change the original list.
 * @details Verifies that the copied list is an independent copy and changes to the original list do not affect the copied one.
 */
TEST(SkipListCopyConstructor, CopyThenChange)
{
    SkipList<int> list;
    list.insert(10);
    list.insert(20);

    SkipList<int> copied_list(list);

    list.insert(5);
    list.erase(20);

    EXPECT_EQ(list.size(), TWO);
    EXPECT_TRUE(list.contains(5));
    EXPECT_FALSE(list.contains(20));

    EXPECT_EQ(copied_list.size(), TWO);
    EXPECT_TRUE(copied_list.contains(10));
    EXPECT_TRUE(copied_list.contains(20));
    EXPECT_FALSE(copied_list.contains(5));

    EXPECT_FALSE(list == copied_list); 
}

// MOVE
/**
 * @brief Test for the SkipList move constructor with an empty list.
 */
TEST(SkipListMoveConstructor, EmptyList)
{
    SkipList<int> original_list; 

    SkipList<int> moved_list(std::move(original_list));

    EXPECT_TRUE(moved_list.empty());
    EXPECT_TRUE(original_list.empty()); 
}

/**
 * @brief Test for the SkipList move constructor with a not empty list.
 */
TEST(SkipListMoveConstructor, NotEmptyList)
{
    SkipList<int> original_list;
    original_list.insert(10);
    original_list.insert(20);
    original_list.insert(30);
    size_t original_size = original_list.size();
    
    SkipList<int> moved_list(std::move(original_list));

    EXPECT_EQ(moved_list.size(), original_size);
    EXPECT_TRUE(moved_list.contains(10));
    EXPECT_TRUE(moved_list.contains(20));
    EXPECT_TRUE(moved_list.contains(30));

    EXPECT_TRUE(original_list.empty());
    EXPECT_FALSE(original_list.contains(10));
    
    // Check if we have working container
    moved_list.insert(5);
    EXPECT_TRUE(moved_list.contains(5));
    EXPECT_EQ(moved_list.size(), TWO + TWO);
}