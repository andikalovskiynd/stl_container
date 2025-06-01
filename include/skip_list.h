#ifndef SKIP_LIST_H
#define SKIP_LIST_H

#include <vector>
#include <memory>
#include <random>
#include <iostream>

#include "node.h"

template <typename T>
class SkipList 
{
    private:
        static const std::size_t MAX_LEVEL = 16; 
        std::unique_ptr<Node<T>> head;

        std::size_t current_level;
        std::size_t num_elements;

        std::mt19937 rng;
        std::uniform_real_distribution<> dis;
        std::size_t get_random_level();

    public:
        SkipList();
        ~SkipList() = default;

        // Init checking
        std::size_t get_current_level() const;
        std::size_t size() const;

        // Test requirements
        std::shared_ptr<Node<T>> get_first_node_at_0() const;

        // Main functionality
        void insert(const T& value);
        bool contains(const T& value) const;
        bool erase(const T& value);
};

template <typename T>
SkipList<T>::SkipList() : head(std::make_unique<Node<T>>(MAX_LEVEL)), current_level(0), num_elements(0) 
{
    std::random_device rd;
    rng.seed(rd());
    dis = std::uniform_real_distribution<>(0.0, 1.0);
}

/* Node is now contains shared_ptr so destructor may be default. Keep it if needed later.
template <typename T>
SkipList<T>::~SkipList()
{
    for (std::size_t i = 0; i < num_elements; ++i)
    {
        Node<T>* current = head->next[0];

        while (current != nullptr) 
        {
            Node<T>* next_node = current->next[0]; 
            delete current;                               
            current = next_node;                         
        }
    }
}
*/

template <typename T>
std::size_t SkipList<T>::get_random_level()
{
    std::size_t level = 1;
    while (dis(rng) < 0.25 && level < MAX_LEVEL)
    {
        ++level;
    }
    return level;

    /*
    static std::mt19937 fixed_gen(0); 
    std::uniform_int_distribution<> distrib(0, MAX_LEVEL);
    std::size_t level = 0;
    while (distrib(fixed_gen) % 2 == 0 && level < MAX_LEVEL) {
        level++;
    }
    return level;
    */
}

template <typename T>
std::size_t SkipList<T>::get_current_level() const 
{
    return current_level;
}

template <typename T>
std::size_t SkipList<T>::size() const 
{
    return num_elements;
}

template <typename T>
std::shared_ptr<Node<T>> SkipList<T>::get_first_node_at_0() const
{
    return head->next[0];
}

template <typename T>
void SkipList<T>::insert(const T& value)
{
    // Array for predecessors at every level which pointers we have to update
    std::vector<Node<T>*> update(MAX_LEVEL + 1, nullptr);

    // current MUST be raw pointer to avoid affect on logic of shared ptrs 
    Node<T>* current = head.get();

    // Step 1 and 2 
    for (std::size_t i = current_level + 1; i-- > 0;) // Идем от current_level до 0 включительно
    {
        while (current->next[i] != nullptr && current->next[i]->getValue() < value)
        {
            current = current->next[i].get();
        }
        update[i] = current;
    }

    // checking for dublicates 
    if (current->next[0] != nullptr && current->next[0]->getValue() == value) 
    {
        return;
    }

   // Step 3
   // Generating random level for new node
    std::size_t new_node_level = get_random_level();

    // Check if new level is higher than max level
    if (new_node_level > current_level)
    {
        for (std::size_t i = current_level + 1; i <= new_node_level; ++i) 
        {
            update[i] = head.get(); 
        }
        current_level = new_node_level;
    }

    // Step 4
    // Creating and inserting a node
    std::shared_ptr<Node<T>> new_node = std::make_shared<Node<T>>(value, new_node_level);

    for (std::size_t i = 0; i <= new_node_level; ++i)
    {
        new_node->next[i] = update[i]->next[i];
        update[i]->next[i] = new_node; 
    }

    num_elements++;

    // DEBUG
    /*
    std::cout << "DEBUG: Inserted value: " << value << ". Current list on level 0: ";
    std::shared_ptr<Node<T>> debug_current = head->next[0];
    while (debug_current != nullptr) 
    {
        std::cout << debug_current->getValue() << " ";
        debug_current = debug_current->next[0];
    }
    std::cout << std::endl;
    std::cout << "DEBUG: current_level after insert: " << current_level << std::endl;
    */
}

template <typename T>
bool SkipList<T>::contains(const T& value) const
{
    // std::cout << "DEBUG: contains(" << value << ") called. current_level: " << current_level << std::endl;

    Node<T>* current = head.get();

    for (std::size_t i = current_level; i >=1; --i)
    {
        // std::cout << "DEBUG: contains: Level " << i << ", current value: " << current->getValue() << std::endl;
        while (current->next[i] != nullptr && current->next[i]->getValue() < value)
        {
            current = current->next[i].get();
        }
    }

    // std::cout << "DEBUG: contains: After loop, current value: " << current->getValue() << std::endl;
    // std::cout << "DEBUG: contains: Checking head->next[0] value: " << (current->next[0] ? std::to_string(current->next[0]->getValue()) : "nullptr") << std::endl;

    if (current->next[0] != nullptr && current->next[0]->getValue() == value)
    {
        return true;
    }

    return false;
}

template <typename T>
bool SkipList<T>::erase(const T& value)
{
    // Logic is similar for insert() at the beginning
    std::vector<Node<T>*> update(MAX_LEVEL + 1);

    Node<T>* current = head.get();

    for (std::size_t i = current_level; i>= 1; --i)
    {
        while (current->next[i] != nullptr && current->next[i]->getValue() < value)
        {
            current = current->next[i].get();
        }
        update[i] = current;
    }

    while(current->next[0] != nullptr && current->next[0]->getValue() < value)
    {
        current = current->next[0].get();
    }
    update[0] = current;

    // Here we go other way
    std::shared_ptr<Node<T>> node_to_delete = current->next[0];

    if (node_to_delete != nullptr && node_to_delete->getValue() == value) 
    {
        // Element is found. Now delete it and update pointers. 
        for (std::size_t i = 0; i <= node_to_delete->level; ++i) 
        {
            // If predecessor on its level points on deleting node, we make it go next node after deleting one.
            if (update[i]->next[i] != nullptr && update[i]->next[i]->getValue() == value) 
            {
                update[i]->next[i] = node_to_delete->next[i];
            }
        }

        num_elements--;

        // Update current level 
        while (current_level > 0 && head->next[current_level] == nullptr) 
        {
            current_level--;
        }
        return true;
    }

    return false;
}





#endif