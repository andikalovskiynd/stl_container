#include "gtest/gtest.h"
#include "../include/skip_list.h"

// EQUALITY
TEST(SkipListOperatorTest, Equality_EmptyList)
{
    SkipList<int> list;
    SkipList<int> other_list;

    EXPECT_TRUE(list == other_list);
}

TEST(SkipListOperatorTest, Equality_IdenticalLists) 
{
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

TEST(SkipListOperatorTest, Equality_DifferentSizes) 
{
    SkipList<int> list;
    SkipList<int> other_list;

    list.insert(10);
    list.insert(20);

    other_list.insert(10);
    other_list.insert(20);
    other_list.insert(30);

    EXPECT_FALSE(list == other_list);
}

TEST(SkipListOperatorTest, Equality_DifferentElements) 
{
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

TEST(SkipListOperatorTest, Equality_DifferentOrder) 
{
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
TEST(SkipListOperatorTest, CopyAssignment_FromEmptyList)
{
    SkipList<int> list;

    list.insert(1);
    list.insert(2);
    list.insert(3);

    SkipList<int> empty_list;
    list = empty_list; 

    EXPECT_TRUE(list.empty());
    EXPECT_TRUE(list == empty_list);
}

TEST(SkipListOperatorTest, CopyAssignment_ToEmptyList)
{
    SkipList<int> list;
    SkipList<int> other_list;
    other_list.insert(100);
    other_list.insert(200);

    list = other_list; // Присваиваем непустой список пустому

    EXPECT_EQ(list.size(), 2);
    EXPECT_TRUE(list.contains(100));
    EXPECT_TRUE(list.contains(200));
    EXPECT_TRUE(list == other_list);
}

TEST(SkipListOperatorTest, CopyAssignment_Overwrite)
{
    SkipList<int> list;
    list.insert(1);
    list.insert(2);

    SkipList<int> other_list;
    other_list.insert(10);
    other_list.insert(20);
    other_list.insert(30);

    list = other_list; // Присваиваем один непустой список другому

    EXPECT_EQ(list.size(), 3);
    EXPECT_TRUE(list.contains(10));
    EXPECT_TRUE(list.contains(20));
    EXPECT_TRUE(list.contains(30));
    EXPECT_TRUE(list == other_list);
}

TEST(SkipListOperatorTest, CopyAssignment_CopyThenChange)
{
    SkipList<int> list;
    list.insert(10);
    list.insert(20);

    SkipList<int> other_list;
    other_list.insert(100);
    other_list.insert(200);

    list = other_list; 

    other_list.insert(50);
    other_list.erase(200);

    EXPECT_EQ(other_list.size(), 2);
    EXPECT_TRUE(other_list.contains(100));
    EXPECT_TRUE(other_list.contains(50));
    EXPECT_FALSE(other_list.contains(200));

    // list must not change
    EXPECT_EQ(list.size(), 2);
    EXPECT_TRUE(list.contains(100));
    EXPECT_TRUE(list.contains(200));
    EXPECT_FALSE(list.contains(50));

    EXPECT_FALSE(list == other_list);
}

TEST(SkipListOperatorTest, CopyAssignment_CopyToSelf)
{
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
TEST(SkipListOperatorTest, MoveAssignment_ToEmptyList)
{
    SkipList<int> list;
    SkipList<int> original_list;
    original_list.insert(10);
    original_list.insert(20);

    // DELIBERATE CHOICE FOR TEST
    list = std::move(original_list);

    EXPECT_EQ(list.size(), 2);
    EXPECT_TRUE(list.contains(10));
    EXPECT_TRUE(list.contains(20));

    EXPECT_TRUE(original_list.empty());
}

TEST(SkipListOperatorTest, MoveAssignment_Overwrite)
{
    SkipList<int> list;
    list.insert(1);
    list.insert(2); 

    SkipList<int> original_list;
    original_list.insert(10);
    original_list.insert(20);
    original_list.insert(30); 

    // DELIBERATE CHOICE FOR TEST
    list = std::move(original_list); 

    EXPECT_EQ(list.size(), 3);
    EXPECT_TRUE(list.contains(10));
    EXPECT_TRUE(list.contains(20));
    EXPECT_TRUE(list.contains(30));

    EXPECT_TRUE(original_list.empty()); 
}

TEST(SkipListOperatorTest, MoveAssignment_Self)
{
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