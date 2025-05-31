#ifndef NODE_H
#define NODE_H

#include <cstddef>
#include <vector>

template <typename T>
struct Node 
{
    T value;
    std::vector<Node*> next;

    Node(const T& val, std::size_t level);
            
    // Dummy node constructor (for example - head)
    Node(std::size_t _level);

    ~Node() = default;
};

template <typename T>
Node<T>::Node(const T& val, std::size_t level) : value(val), next(level, nullptr) {}

template <typename T> 
Node<T>::Node(std::size_t _level) : next(_level, nullptr) {};

#endif