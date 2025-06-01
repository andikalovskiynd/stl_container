#include "gtest/gtest.h"          
#include "../include/skip_list.h" 

class SkipListIntTest : public ::testing::Test 
{
    protected:
        SkipList<int> int_list;

        // Method that finds elements at level 0
        bool check_level_0(const std::vector<int>& expected_elements) 
        {
            std::vector<int> actual_elements;
            std::shared_ptr<Node<int>> current = int_list.get_first_node_at_0();

            while (current != nullptr) 
            {
                actual_elements.push_back(current->getValue());
                current = current->next[0];
            }

            return expected_elements == actual_elements;
        }
};

TEST_F(SkipListIntTest, Initialization) 
{
    EXPECT_EQ(0, int_list.get_current_level());
    EXPECT_EQ(0, int_list.size());
}

// INSERT TESTS - NOT FULL YET. MORE FUNCTIONALITY IS NEEDED.
TEST_F(SkipListIntTest, Insert_SingleElement)
{
    int_list.insert(10);

    ASSERT_TRUE(int_list.contains(10));
    EXPECT_EQ(1, int_list.size());
    EXPECT_TRUE(check_level_0({10}));
}

TEST_F(SkipListIntTest, Insert_MultipleElements_Ascending)
{
    int_list.insert(10);
    int_list.insert(20);
    int_list.insert(30);

    ASSERT_TRUE(int_list.contains(10));
    ASSERT_TRUE(int_list.contains(20));
    ASSERT_TRUE(int_list.contains(30));

    EXPECT_EQ(3, int_list.size());
    EXPECT_TRUE(check_level_0({10, 20, 30}));
}

TEST_F(SkipListIntTest, Insert_MultipleElements_Descdending)
{
    int_list.insert(30);
    int_list.insert(20);
    int_list.insert(10);

    ASSERT_TRUE(int_list.contains(10));
    ASSERT_TRUE(int_list.contains(20));
    ASSERT_TRUE(int_list.contains(30));

    EXPECT_EQ(3, int_list.size());
    EXPECT_TRUE(check_level_0({10, 20, 30}));
}

TEST_F(SkipListIntTest, Insert_MultipleElements_Randomly)
{
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

    EXPECT_EQ(6, int_list.size());
    EXPECT_TRUE(check_level_0({1, 5, 13, 22, 79, 110}));
}

TEST_F(SkipListIntTest, Insert_DublicateElement)
{
    int_list.insert(10);
    int_list.insert(20);

    ASSERT_TRUE(int_list.contains(10));
    ASSERT_TRUE(int_list.contains(20));

    EXPECT_EQ(2, int_list.size());

    int_list.insert(10);
    EXPECT_EQ(2, int_list.size());
    EXPECT_TRUE(check_level_0({10, 20}));
}

// CONTAINS TEST
TEST_F(SkipListIntTest, Contains_EmptyList) 
{
    EXPECT_FALSE(int_list.contains(10));
}

TEST_F(SkipListIntTest, Contains_FewExisting)
{
    int_list.insert(10);
    int_list.insert(20);

    EXPECT_TRUE(int_list.contains(10));
    EXPECT_TRUE(int_list.contains(20));
}

TEST_F(SkipListIntTest, Contains_FewNotExisting)
{
    int_list.insert(10);
    int_list.insert(20);

    EXPECT_FALSE(int_list.contains(9));
    EXPECT_FALSE(int_list.contains(11));
}

// ERASE TESTS
TEST_F(SkipListIntTest, Erase_ExistingElements) 
{
    int_list.insert(10);
    int_list.insert(20);
    int_list.insert(30);
    int_list.insert(15); 

    EXPECT_TRUE(int_list.contains(20));
    EXPECT_TRUE(int_list.erase(20)); 
    EXPECT_FALSE(int_list.contains(20)); 
    EXPECT_TRUE(check_level_0({10, 15, 30})); 
    EXPECT_EQ(3, int_list.size()); 
}

TEST_F(SkipListIntTest, Erase_NotExistingElements)
{
    int_list.insert(10);
    int_list.insert(15);

    ASSERT_FALSE(int_list.erase(20));

    EXPECT_TRUE(int_list.contains(10));
    EXPECT_TRUE(int_list.contains(15));

    EXPECT_TRUE(check_level_0({10, 15}));
    EXPECT_EQ(2, int_list.size());
}

TEST_F(SkipListIntTest, Erase_EmptyList)
{
    ASSERT_FALSE(int_list.erase(10));
    EXPECT_TRUE(check_level_0({}));
    EXPECT_EQ(0, int_list.size());
}

