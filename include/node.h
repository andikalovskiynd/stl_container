/**
 * @file node.h
 * @brief Definition of the Node structure for SkipList.
 */

#ifndef NODE_H
#define NODE_H

#include <cstddef>
#include <vector>
#include <memory>

/**
 * @struct Node
 * @brief Represents a node in a Skip List.
 * @details Each node stores a value of type T, its level in the Skip List,
 * @tparam T The type of the value stored in the node.
 */
template <typename T>
struct Node 
{
private:
    /// @brief The value stored in the node.
    T value;

public:
    /// @brief The level of the node in the Skip List. 
    std::size_t level;

    /// @brief A vector of pointers to the next nodes at each level.
    std::vector<std::shared_ptr<Node<T>>> next;

    /**
     * @brief Constructor for creating a regular node with a given value and level.
     * @param val The value to be stored in the node.
     * @param lvl The level at which the node will be created.
     */
    Node(const T& val, std::size_t level);
            
    /**
     * @brief Constructor for creating a "dummy" node.
     * @details This constructor initializes the node with only a level, without a specific value.
     * @param _lvl The level of the dummy node.
     */
    Node(std::size_t _level);

    /// @brief Default destructor.
    ~Node() = default;

    /**
     * @brief Returns a reference to the value stored in the node.
     * @return A reference to the modifiable value of the node.
     */
    T& getValue();

    /**
     * @brief Returns a constant reference to the value stored in the node.
     * @return A constant reference to the value of the node.
     */
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