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

    public:
        SkipList();
        ~SkipList() = default;

        void doNothing(const T& value);

        // Init checking
        std::size_t get_current_level() const;
        std::size_t size() const;
};

template <typename T>
SkipList<T>::SkipList() : head(std::make_unique<Node<T>>(MAX_LEVEL)), current_level(0), num_elements(0) 
{
    std::random_device rd;
    rng.seed(rd());
    dis = std::uniform_real_distribution<>(0.0, 1.0);
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

#endif