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

    ASSERT_TRUE(double_list.contains(10.75892));
    EXPECT_EQ(1, double_list.size());
    EXPECT_TRUE(check_level_0({10.75892}));
}

TEST_F(SkipListDoubleTest, Insert_MultipleElements_Ascending)
{
    double_list.insert(10.75892);
    double_list.insert(20.4432);
    double_list.insert(20.5566);

    ASSERT_TRUE(double_list.contains(10.75892));
    ASSERT_TRUE(double_list.contains(20.4432));
    ASSERT_TRUE(double_list.contains(20.5566));

    EXPECT_EQ(3, double_list.size());
    EXPECT_TRUE(check_level_0({10.75892, 20.4432, 20.5566}));
}

TEST_F(SkipListDoubleTest, Insert_MultipleElements_Descdending)
{
    double_list.insert(20.5566);
    double_list.insert(20.4432);
    double_list.insert(10.75892);

    ASSERT_TRUE(double_list.contains(10.75892));
    ASSERT_TRUE(double_list.contains(20.4432));
    ASSERT_TRUE(double_list.contains(20.5566));

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

    ASSERT_TRUE(double_list.contains(13.674554));
    ASSERT_TRUE(double_list.contains(5.55543));
    ASSERT_TRUE(double_list.contains(1.0001));
    ASSERT_TRUE(double_list.contains(22.4432));
    ASSERT_TRUE(double_list.contains(110.75892));
    ASSERT_TRUE(double_list.contains(79.6667));

    EXPECT_EQ(6, double_list.size());
    EXPECT_TRUE(check_level_0({1.0001, 5.55543, 13.674554, 22.4432, 79.6667, 110.75892}));
}

TEST_F(SkipListDoubleTest, Insert_DublicateElement)
{
    double_list.insert(10.75892);
    double_list.insert(20.5656);

    ASSERT_TRUE(double_list.contains(10.75892));
    ASSERT_TRUE(double_list.contains(20.5656));

    EXPECT_EQ(2, double_list.size());

    double_list.insert(10.75892);
    EXPECT_EQ(2, double_list.size());
    EXPECT_TRUE(check_level_0({10.75892, 20.5656}));
}

// CONTAINS TEST
TEST_F(SkipListDoubleTest, Contains_EmptyList) 
{
    EXPECT_FALSE(double_list.contains(10.4321));
}

TEST_F(SkipListDoubleTest, Contains_FewExisting)
{
    double_list.insert(10.555);
    double_list.insert(20.121);

    EXPECT_TRUE(double_list.contains(10.555));
    EXPECT_TRUE(double_list.contains(20.121));
}

TEST_F(SkipListDoubleTest, Contains_FewNotExisting)
{
    double_list.insert(10.443);
    double_list.insert(20.443);

    EXPECT_FALSE(double_list.contains(10.444));
    EXPECT_FALSE(double_list.contains(20.444));
}

// Lexicographic 
// <
TEST_F(SkipListDoubleTest, Operator_LessThan_EmptyVsNotEmpty)
{
    SkipList<double> other_list;
    other_list.insert(10.5); 
    EXPECT_TRUE(double_list < other_list);
    EXPECT_FALSE(other_list < double_list);
}

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
TEST_F(SkipListDoubleTest, Operator_GreaterThan_EmptyVsNotEmpty)
{
    SkipList<double> other_list;
    double_list.insert(10.5);
    EXPECT_TRUE(double_list > other_list);
    EXPECT_FALSE(other_list > double_list);
}

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
TEST_F(SkipListDoubleTest, Operator_LessOrEqual_Identical)
{
    double_list.insert(10.0);
    double_list.insert(20.0);

    SkipList<double> other_list(double_list); 

    EXPECT_TRUE(double_list <= other_list);
    EXPECT_TRUE(other_list <= double_list);
}

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
TEST_F(SkipListDoubleTest, Operator_GreaterOrEqual_Identical)
{
    double_list.insert(10.0);
    double_list.insert(20.0);

    SkipList<double> other_list(double_list);

    EXPECT_TRUE(double_list >= other_list);
    EXPECT_TRUE(other_list >= double_list);
}

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