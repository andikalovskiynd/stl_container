#include "gtest/gtest.h"
#include "../include/skip_list.h"

TEST(SkipListCopyConstructor, EmptyList)
{   
    SkipList<int> list;

    SkipList<int> copied_list(list);

    EXPECT_TRUE(copied_list.empty());
    EXPECT_TRUE(list == copied_list); 
}

TEST(SkipListCopyConstructor, NotEmptyList)
{   
    SkipList<int> list;

    list.insert(10);
    list.insert(20);
    list.insert(30);

    SkipList<int> copied_list(list);

    EXPECT_EQ(copied_list.size(), 3);
    EXPECT_TRUE(copied_list.contains(10));
    EXPECT_TRUE(copied_list.contains(20));
    EXPECT_TRUE(copied_list.contains(30));
    EXPECT_TRUE(list == copied_list); 
}

TEST(SkipListCopyConstructor, CopyThenChange)
{
    SkipList<int> list;
    list.insert(10);
    list.insert(20);

    SkipList<int> copied_list(list);

    list.insert(5);
    list.erase(20);

    EXPECT_EQ(list.size(), 2);
    EXPECT_TRUE(list.contains(5));
    EXPECT_FALSE(list.contains(20));

    EXPECT_EQ(copied_list.size(), 2);
    EXPECT_TRUE(copied_list.contains(10));
    EXPECT_TRUE(copied_list.contains(20));
    EXPECT_FALSE(copied_list.contains(5));

    EXPECT_FALSE(list == copied_list); 
}

// MOVE

TEST(SkipListMoveConstructor, EmptyList)
{
    SkipList<int> original_list; 

    SkipList<int> moved_list(std::move(original_list));

    EXPECT_TRUE(moved_list.empty());
    EXPECT_TRUE(original_list.empty()); 
}

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
    EXPECT_EQ(moved_list.size(), 4);
}

