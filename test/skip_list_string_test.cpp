#include "gtest/gtest.h"          
#include "../include/skip_list.h" 

#include <string>

class SkipListStringTest : public ::testing::Test 
{
    protected:
        SkipList<std::string> string_list;

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

TEST_F(SkipListStringTest, Initialization) 
{
    EXPECT_EQ(0, string_list.get_current_level());
    EXPECT_EQ(0, string_list.size());
}

// INSERT TESTS - NOT FULL YET. MORE FUNCTIONALITY IS NEEDED.
TEST_F(SkipListStringTest, Insert_SingleElement)
{
    string_list.insert("Word");

    ASSERT_TRUE(string_list.contains("Word"));
    EXPECT_EQ(1, string_list.size());
    EXPECT_TRUE(check_level_0({"Word"}));
}

TEST_F(SkipListStringTest, Insert_MultipleElements_Ascending)
{
    string_list.insert("Apple");
    string_list.insert("Banana");
    string_list.insert("Cherry");

    ASSERT_TRUE(string_list.contains("Apple"));
    ASSERT_TRUE(string_list.contains("Banana"));
    ASSERT_TRUE(string_list.contains("Cherry"));

    EXPECT_EQ(3, string_list.size());
    EXPECT_TRUE(check_level_0({"Apple", "Banana", "Cherry"}));
}

TEST_F(SkipListStringTest, Insert_MultipleElements_Descdending)
{
    string_list.insert("Cherry");
    string_list.insert("Banana");
    string_list.insert("Apple");

    ASSERT_TRUE(string_list.contains("Apple"));
    ASSERT_TRUE(string_list.contains("Banana"));
    ASSERT_TRUE(string_list.contains("Cherry"));

    EXPECT_EQ(3, string_list.size());
    EXPECT_TRUE(check_level_0({"Apple", "Banana", "Cherry"}));
}

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

    EXPECT_EQ(6, string_list.size());
    EXPECT_TRUE(check_level_0({"Apple", "Banana", "Cherry", "Demon", "Helicopter", "Witch"}));
}

TEST_F(SkipListStringTest, Insert_DublicateElement)
{
    string_list.insert("Apple");
    string_list.insert("Banana");

    ASSERT_TRUE(string_list.contains("Apple"));
    ASSERT_TRUE(string_list.contains("Banana"));

    EXPECT_EQ(2, string_list.size());

    string_list.insert("Apple");
    EXPECT_EQ(2, string_list.size());
    EXPECT_TRUE(check_level_0({"Apple", "Banana"}));
}

// CONTAINS TEST
TEST_F(SkipListStringTest, Contains_EmptyList) 
{
    EXPECT_FALSE(string_list.contains("Apple"));
}

TEST_F(SkipListStringTest, Contains_FewExisting)
{
    string_list.insert("Apple");
    string_list.insert("Banana");

    EXPECT_TRUE(string_list.contains("Apple"));
    EXPECT_TRUE(string_list.contains("Banana"));
}

TEST_F(SkipListStringTest, Contains_FewNotExisting)
{
    string_list.insert("Apple");
    string_list.insert("Banana");

    EXPECT_FALSE(string_list.contains("Cherry"));
    EXPECT_FALSE(string_list.contains("Dragonfruit"));
}

// Lexicographic operators
TEST_F(SkipListStringTest, Operator_LessThan_EmptyVsNotEmpty)
{
    SkipList<std::string> other_list;
    other_list.insert("Apple");
    EXPECT_TRUE(string_list < other_list);
    EXPECT_FALSE(other_list < string_list);
}

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
TEST_F(SkipListStringTest, Operator_GreaterThan_EmptyVsNotEmpty)
{
    SkipList<std::string> other_list;
    string_list.insert("Apple");
    EXPECT_TRUE(string_list > other_list);
    EXPECT_FALSE(other_list > string_list);
}

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
TEST_F(SkipListStringTest, Operator_LessOrEqual_Identical)
{
    string_list.insert("Apple");
    string_list.insert("Banana");

    SkipList<std::string> other_list(string_list); 

    EXPECT_TRUE(string_list <= other_list);
    EXPECT_TRUE(other_list <= string_list);
}

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
TEST_F(SkipListStringTest, Operator_GreaterOrEqual_Identical)
{
    string_list.insert("Apple");
    string_list.insert("Banana");

    SkipList<std::string> other_list(string_list);

    EXPECT_TRUE(string_list >= other_list);
    EXPECT_TRUE(other_list >= string_list);
}

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
