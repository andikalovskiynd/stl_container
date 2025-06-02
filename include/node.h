#ifndef NODE_H
#define NODE_H

#include <cstddef>
#include <vector>
#include <memory>

template <typename T>
struct Node 
{
private:
    T value;

public:
    std::size_t level;
    std::vector<std::shared_ptr<Node<T>>> next;


    Node(const T& val, std::size_t level);
            
    // Dummy node constructor (for example - head)
    Node(std::size_t _level);

    ~Node() = default;

    // 
    T& getValue();
    const T& getValue() const;
};

template <typename T>
Node<T>::Node(const T& val, std::size_t lvl) : value(val), level(lvl), next(level + 1, nullptr) {}

template <typename T> 
Node<T>::Node(std::size_t _lvl) : level(_lvl), next(_lvl + 1, nullptr) {};

template <typename T>
T& Node<T>::getValue() 
{
    return value;
}

template <typename T>
const T& Node<T>::getValue() const
{
    return value;
}

#endif