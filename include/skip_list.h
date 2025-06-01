#ifndef SKIP_LIST_H
#define SKIP_LIST_H

#include <vector>
#include <memory>
#include <random>

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

        void doNothing(const T& value);

        // Init checking
        std::size_t get_current_level() const;
        std::size_t size() const;

        // Test requirements
        std::shared_ptr<Node<T>> get_first_node_at_0() const;

        // Main functionality
        void insert(const T& value);
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
}

template <typename T>
void SkipList<T>::doNothing(const T& value)
{
    (void)value;
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
    // update array which contains nods pointers 
    std::vector<Node<T>*> update(MAX_LEVEL + 1, nullptr);

    // current MUST be raw pointer to avoid affect on logic of shared ptrs 
    Node<T>* current = head.get();

    // Step 1
    // going from top to bottom. for every level we search the rightest current node which value is lower than 'value' 
    for (std::size_t i = current_level; i>= 1; --i)
    {
        while (current->next[i] != nullptr && current->next[i]->getValue() < value)
        {
            current = current->next[i].get();
        }
        update[i] = current;
    }

    // Step 2
    // Finding place for element at level 0
    while(current->next[0] != nullptr && current->next[0]->getValue() < value)
    {
        current = current->next[0].get();
    }
    update[0] = current;

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

    for (std::size_t i = 0; i < new_node_level; ++i)
    {
        new_node->next[i] = update[i]->next[i];
        update[i]->next[i] = new_node; 
    }

    num_elements++;
}
#endif