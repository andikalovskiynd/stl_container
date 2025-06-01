#include "gtest/gtest.h"

#include "../include/node.h"
#include "../include/skip_list.h"

// There is no actual sense to make tests for every type of data that we test
// so we make tests for int and suppose that it will work for other types

TEST(SkipListIteratorTest, Iterators_EmptyList) 
{
    SkipList<int> list;

    ASSERT_TRUE(list.begin() == list.end());
    ASSERT_TRUE(list.cbegin() == list.cend());

    ASSERT_THROW(*list.begin(), std::out_of_range);
    ASSERT_THROW(*list.end(), std::out_of_range);
}

TEST(SkipListIteratorTest, Iterator_SingleElement)
{
    SkipList<int> list;
    list.insert(11);

    auto it = list.begin();

    ASSERT_NE(it, list.end());
    ASSERT_EQ(*it, 11);

    ++it;
    ASSERT_TRUE(it == list.end());
}

TEST(SkipListIteratorTest, Iterator_SingleElement_Const)
{
    SkipList<int> list;
    list.insert(11);

    const auto& const_list = list;
    auto cit = const_list.cbegin();
    EXPECT_EQ(*cit, 11);

    ++cit;
    ASSERT_TRUE(cit == const_list.cend());
}

TEST(SkipListIteratorTest, BasicTraversal) 
{
    SkipList<int> list;
    list.insert(10);
    list.insert(20);
    list.insert(5);
    list.insert(15);
    list.insert(25);

    std::vector<int> expected = {5, 10, 15, 20, 25};
    std::vector<int> actual_elements;

    for (const auto& val : list) 
    { 
        actual_elements.push_back(val);
    }
    ASSERT_EQ(expected, actual_elements);


    actual_elements.clear();

    for (auto it = list.begin(); it != list.end(); ++it) 
    { 
        actual_elements.push_back(*it);
    }
    ASSERT_EQ(expected, actual_elements);


    actual_elements.clear();

    for (auto it = list.cbegin(); it != list.cend(); ++it) 
    { 
        actual_elements.push_back(*it);
    }
    ASSERT_EQ(expected, actual_elements);
}

TEST(SkipListIteratorTest, ArrowOperator) 
{
    SkipList<int> list;
    list.insert(10);

    auto it = list.begin();
    EXPECT_EQ(*it, *it.operator->());
}

TEST(SkipListIteratorTest, PostfixIncrement) 
{
    SkipList<int> list;
    list.insert(10);
    list.insert(20);

    auto it = list.begin(); 
    auto old_it = it++; 

    EXPECT_EQ(*old_it, 10);
    EXPECT_EQ(*it, 20);
    
    ++it; 
    ASSERT_TRUE(it == list.end());
}

TEST(SkipListIteratorTest, StdFind) 
{
    SkipList<int> list;
    list.insert(10);
    list.insert(20);
    list.insert(5);

    auto found_it = std::find(list.begin(), list.end(), 10);
    ASSERT_NE(found_it, list.end());
    EXPECT_EQ(*found_it, 10);

    auto not_found_it = std::find(list.begin(), list.end(), 100);
    ASSERT_EQ(not_found_it, list.end());
}

TEST(SkipListIteratorTest, ConstIterator_ConstructionFromIterator) 
{
    SkipList<int> list;
    list.insert(10);
    list.insert(20);

    SkipList<int>::iterator it = list.begin();
    EXPECT_EQ(*it, 10);

    SkipList<int>::const_iterator cit = it;
    EXPECT_EQ(*cit, 10); 

    ++it;
    EXPECT_EQ(*it, 20);
    EXPECT_EQ(*cit, 10);

    ++cit;
    EXPECT_EQ(*cit, 20);
}

TEST(SkipListIteratorTest, IteratorConstIteratorComparison) 
{
    SkipList<int> list;
    list.insert(10);
    list.insert(20);
    list.insert(30);

    SkipList<int>::iterator it_10 = list.begin();
    SkipList<int>::iterator it_20 = ++SkipList<int>::iterator(list.begin());

    SkipList<int>::const_iterator cit_10 = list.cbegin();
    SkipList<int>::const_iterator cit_20 = ++SkipList<int>::const_iterator(list.cbegin());

    ASSERT_TRUE(it_10 == cit_10);
    ASSERT_TRUE(cit_10 == it_10); 

    ASSERT_TRUE(it_10 != cit_20);
    ASSERT_TRUE(cit_20 != it_10);

    ASSERT_TRUE(it_20 == cit_20);
    ASSERT_TRUE(cit_20 == it_20);

    ASSERT_TRUE(list.end() == list.cend());
    ASSERT_TRUE(list.cend() == list.end());

    SkipList<int>::iterator it_end = list.end();
    SkipList<int>::const_iterator cit_end = list.cend();
    ASSERT_TRUE(it_end == cit_end);
    ASSERT_TRUE(cit_end == it_end);

    ASSERT_TRUE(it_10 != cit_end);
    ASSERT_TRUE(cit_end != it_10);
}