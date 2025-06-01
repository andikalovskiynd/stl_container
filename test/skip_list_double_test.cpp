#include "gtest/gtest.h"          
#include "../include/skip_list.h" 

class SkipListDoubleTest : public ::testing::Test 
{
    protected:
        SkipList<double> double_list;

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

TEST_F(SkipListDoubleTest, Initialization) 
{
    EXPECT_EQ(0, double_list.get_current_level());
    EXPECT_EQ(0, double_list.size());
}

// INSERT
TEST_F(SkipListDoubleTest, Insert_SingleElement)
{
    double_list.insert(10.75892);

    EXPECT_EQ(1, double_list.size());
    EXPECT_TRUE(check_level_0({10.75892}));
}

TEST_F(SkipListDoubleTest, Insert_MultipleElements_Ascending)
{
    double_list.insert(10.75892);
    double_list.insert(20.4432);
    double_list.insert(20.5566);

    EXPECT_EQ(3, double_list.size());
    EXPECT_TRUE(check_level_0({10.75892, 20.4432, 20.5566}));
}

TEST_F(SkipListDoubleTest, Insert_MultipleElements_Descdending)
{
    double_list.insert(20.5566);
    double_list.insert(20.4432);
    double_list.insert(10.75892);

    EXPECT_EQ(3, double_list.size());
    EXPECT_TRUE(check_level_0({10.75892, 20.4432, 20.5566}));
}

TEST_F(SkipListDoubleTest, Insert_MultipleElements_Randomly)
{
    double_list.insert(13.674554);
    double_list.insert(5.55543);
    double_list.insert(1.0001);
    double_list.insert(22.4432);
    double_list.insert(110.75892);
    double_list.insert(79.6667);

    EXPECT_EQ(6, double_list.size());
    EXPECT_TRUE(check_level_0({1.0001, 5.55543, 13.674554, 22.4432, 79.6667, 110.75892}));
}

TEST_F(SkipListDoubleTest, Insert_DublicateElement)
{
    double_list.insert(10.75892);
    double_list.insert(20.5656);

    EXPECT_EQ(2, double_list.size());

    double_list.insert(10.75892);
    EXPECT_EQ(2, double_list.size());
    EXPECT_TRUE(check_level_0({10.75892, 20.5656}));
}