#include "gtest/gtest.h"          
#include "../include/skip_list.h" 

template <typename T>
const std::size_t SkipList<T>::MAX_LEVEL;

TEST(SkipListBasicTest, InitTest) 
{
    SkipList<int> int_list;

    int_list.doNothing(42);

    SUCCEED() << "SkipList<int> instantiated and do_nothing_but_compile method called successfully.";
}

TEST(SkipListBasicTest, GetCurrentLevelTest)
{
    SkipList<int> int_list;

    ASSERT_EQ(0, int_list.get_current_level());
}

TEST(SkipListBasicTest, SizeTest)
{
    SkipList<int> int_list;

    ASSERT_EQ(0, int_list.size());
}