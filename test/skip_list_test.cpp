#include "gtest/gtest.h"          
#include "../include/skip_list.h" 

TEST(SkipListBasicTest, InitTest) 
{
    SkipList<int> int_list;

    int_list.doNothing(42);

    SUCCEED() << "SkipList<int> instantiated and do_nothing_but_compile method called successfully.";
}