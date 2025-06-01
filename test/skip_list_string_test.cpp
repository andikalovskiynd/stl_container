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

    EXPECT_EQ(1, string_list.size());
    EXPECT_TRUE(check_level_0({"Word"}));
}

TEST_F(SkipListStringTest, Insert_MultipleElements_Ascending)
{
    string_list.insert("Apple");
    string_list.insert("Banana");
    string_list.insert("Cherry");

    EXPECT_EQ(3, string_list.size());
    EXPECT_TRUE(check_level_0({"Apple", "Banana", "Cherry"}));
}

TEST_F(SkipListStringTest, Insert_MultipleElements_Descdending)
{
    string_list.insert("Cherry");
    string_list.insert("Banana");
    string_list.insert("Apple");

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

    EXPECT_EQ(6, string_list.size());
    EXPECT_TRUE(check_level_0({"Apple", "Banana", "Cherry", "Demon", "Helicopter", "Witch"}));
}

TEST_F(SkipListStringTest, Insert_DublicateElement)
{
    string_list.insert("Apple");
    string_list.insert("Banana");

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