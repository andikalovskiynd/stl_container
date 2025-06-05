/**
 * @file skip_list.h
 * @brief SkipList definition and implementation.
*/

#ifndef SKIP_LIST_H
#define SKIP_LIST_H

#include <vector>
#include <memory>
#include <random>
#include <iostream>
#include <algorithm>

#include "node.h"

/**
 * @brief A templated SkipList data structure for storing elements in sorted order.
 * @tparam T The type of elements to be stored in the SkipList.
 * @details Requires operator< and operator== to be defined for type T.
 */
template <typename T>
class SkipList {
  private:
    /// @brief Maximum number of levels in the SkipList.
    static const std::size_t MAX_LEVEL = 16;

    /// @brief Head node of the SkipList. Does not keep any value.
    std::unique_ptr<Node<T>> head;

    /// @brief Current maximum level reached by any node.
    std::size_t current_level;

    /// @brief Number of elements in list.
    std::size_t num_elements;

    /// @brief Random number generator.
    std::mt19937 rng;

    /// @brief Distribution for level generation probability.
    std::uniform_real_distribution<> dis;

  public:
    // ============================== //
    // Iterator classes               //
    // ============================== //

    // Forward declaration of const_iterator to allow friend declarations.
    class const_iterator;

    /// @brief Iterator class for iterating over elements in the SkipList.
    class iterator {
      private:
        /// @brief Pointer to the current node in the iteration.
        Node<T>* current_node;

      public:
        // Standard iterator traits
        using iterator_category = std::forward_iterator_tag; // SkipList only goes forward
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = T*;
        using reference = T&;

        /// @brief Allows const_iterator to access private members
        friend class const_iterator;

        /**
         * @brief Constructs an iterator.
         * @param node_ptr A pointer to the node the iterator should point to.
         * @details Default to 'nullptr' for an 'end()' iterator.
         */
        explicit iterator(Node<T>* node_ptr = nullptr) : current_node(node_ptr) {}

        /**
         * @brief Dereferences the iterator to access the value.
         * @return A reference to the value of the current node.
         * @throw std::out_of_range If the iterator is null (for example, end() iterator).
         */
        reference operator*() const
        {
            if (!current_node) {
                throw std::out_of_range("Dereferencing null iterator.");
            }
            return current_node->getValue();
        }

        /**
         * @brief Provides pointer-like access to the value.
         * @return A pointer to the value of the current node.
         * @throw std::out_of_range If the iterator is null (for example, end() iterator).
         */
        pointer operator->() const
        {
            if (!current_node) {
                throw std::out_of_range("Dereferencing null iterator.");
            }
            return &(current_node->getValue());
        }

        /**
         * @brief Pre-increments the iterator to the next node.
         * @return A reference to the incremented iterator.
         */
        iterator& operator++() {
            if (current_node) {
                current_node = current_node->next[0].get();
            }
            return *this;
        }

        /**
         * @brief Post-increments the iterator to the next node.
         * @return A copy of the iterator before incrementation.
         */
        iterator operator++(int) {
            iterator temp = *this;
            ++(*this);
            return temp;
        }

        /**
         * @brief Compares two iterators for equality.
         * @param other The iterator to compare with.
         * @return True if both iterators point to the same node, false otherwise.
         */
        bool operator==(const iterator& other) const { return current_node == other.current_node; }

        /**
         * @brief Compares two iterators for inequality.
         * @param other The iterator to compare with.
         * @return True if iterators point to different nodes, false otherwise.
         */
        bool operator!=(const iterator& other) const { return current_node != other.current_node; }

        // Comparing iterator with const_iterator
        /**
         * @brief Compares iterator and const_iterator for equality.
         * @details This operator is needed to compare two different iterators (const and not const).
         * @param other The const_iterator to compare with.
         * @return True if both iterators point to the same node, false otherwise.
         */
        bool operator==(const const_iterator& other) const { return current_node == other.current_node; }

        /**
         * @brief Compares iterator and const_iterator for inequality.
         * @details This operator is needed to compare two different iterators (const and not const).
         * @param other The const_iterator to compare with.
         * @return True if iterators point to different nodes, false otherwise.
         */
        bool operator!=(const const_iterator& other) const { return current_node != other.current_node; }
    };

    /// @brief Constant iterator class for iterating over elements in the SkipList.
    class const_iterator {
        friend class iterator;
      private:
        /// @brief Pointer to the current node in the iteration.
        const Node<T>* current_node;

      public:
        // Standard iterator traits
        using iterator_category = std::forward_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = const T*;
        using reference = const T&;

        /**
         * @brief Constructs a const_iterator.
         * @param node_ptr A pointer to the node the iterator should point to.
         */
        explicit const_iterator(const Node<T>* node_ptr) : current_node(node_ptr) {}

        /**
         * @brief Conversion constructor from a non-const iterator to a const_iterator.
         * @param other The non-const iterator to convert from.
         * @details Used to compare two iterators with different types.
         */
        const_iterator(const typename SkipList<T>::iterator& other) : current_node(other.current_node) {}

        /**
         * @brief Dereferences the const_iterator to access the constant value.
         * @return A constant reference to the value of the current node.
         * @throw std::out_of_range If the iterator is null (for example, end() iterator).
         */
        reference operator*() const
        {
            if (!current_node) {
                throw std::out_of_range("Dereferencing null iterator.");
            }
            return current_node->getValue();
        }

        /**
         * @brief Provides pointer-like access to the constant value.
         * @return A constant pointer to the value of the current node.
         * @throw std::out_of_range If the iterator is null (for example, end() iterator).
         */
        pointer operator->() const
        {
            if (!current_node) {
                throw std::out_of_range("Dereferencing null iterator.");
            }
            return &(current_node->getValue());
        }

        /**
         * @brief Pre-increments the const_iterator to the next node.
         * @return A reference to the incremented const_iterator.
         */
        const_iterator& operator++() {
            if (current_node) {
                current_node = current_node->next[0].get();
            }
            return *this;
        }

        /**
         * @brief Post-increments the const_iterator to the next node.
         * @return A copy of the const_iterator before incrementation.
         */
        const_iterator operator++(int) {
            const_iterator temp = *this;
            ++(*this);
            return temp;
        }

        /**
         * @brief Compares two const iterators for equality.
         * @param other The const iterator to compare with.
         * @return True if both const iterators point to the same node, false otherwise.
         */
        bool operator==(const const_iterator& other) const { return current_node == other.current_node; }

        /**
         * @brief Compares two const iterators for inequality.
         * @param other The const iterator to compare with.
         * @return True if operators point on different nodes, false otherwise.
         */
        bool operator!=(const const_iterator& other) const { return current_node != other.current_node; }

        // Comparing const_iterator with iterator:
        /**
         * @brief Compares const_iterator and iterator for equality.
         * @details This operator is needed to compare two different iterators (const and not const).
         * @param other The iterator to compare with.
         * @return True if both iterators point to the same node, false otherwise.
         */
        bool operator==(const iterator& other) const { return current_node == other.current_node; }

        /**
         * @brief Compares const_iterator and iterator for inequality.
         * @details This operator is needed to compare two different iterators (const and not const).
         * @param other The iterator to compare with.
         * @return True if operators point on different nodes, false otherwise.
         */
        bool operator!=(const iterator& other) const { return current_node != other.current_node; }
    };

    /**
     * @brief Returns an iterator to the first element of the SkipList.
     * @return An iterator pointing to the first element.
     */
    iterator begin() {
        return iterator(head->next[0].get());
    }

    /**
     * @brief Returns a const_iterator to the first element of the SkipList.
     * @return A const_iterator pointing to the first element.
     */
    const_iterator begin() const {
        return const_iterator(head->next[0].get());
    }

    /**
     * @brief Returns an iterator to the element following the last element.
     * @return An iterator pointing past the last element.
     */
    iterator end() {
        return iterator(nullptr);
    }

    /**
     * @brief Returns a const_iterator to the element following the last element.
     * @return A const_iterator pointing past the last element.
     */
    const_iterator end() const {
        return const_iterator(nullptr);
    }

    /**
     * @brief Returns a const_iterator to the first element of the SkipList (const version).
     * @return A const_iterator pointing to the first element.
     */
    const_iterator cbegin() const {
        return const_iterator(head->next[0].get());
    }

    /**
     * @brief Returns a const_iterator to the element following the last element (const version).
     * @return A const_iterator pointing past the last element.
     */
    const_iterator cend() const {
        return const_iterator(nullptr);
    }

    // ============================== //
    // Methods
    // ============================== //

    /// @brief Constructs an empty SkipList.
    SkipList();

    /**
     * @brief Copy constructor.
     * @param other The SkipList to copy from.
     */
    SkipList(const SkipList& other);

    /**
     * @brief Move constructor.
     * @param other The SkipList to move from (an rvalue reference).
     */
    SkipList(SkipList&& other) noexcept;

    /// @brief Destroys the SkipList. Defaulted due to smart pointer usage.
    ~SkipList() = default;

    // Main functionality

    /**
     * @brief  Generates a random level for a new node.
     * @return A randomly generated level for a new node.
     */
    std::size_t get_random_level();

    /**
     * @brief Returns the current maximum level of the SkipList.
     * @return The maximum level reached by any node in the list.
     */
    std::size_t get_current_level() const;

    /**
     * @brief Returns a shared pointer to the first node at level 0.
     * @details This is primarily for testing.
     * @return A shared pointer to the first actual data node at the base level.
     */
    std::shared_ptr<Node<T>> get_first_node_at_0() const;

    /**
     * @brief Returns the number of elements in the SkipList.
     * @return The total number of elements.
     */
    std::size_t size() const;

    /**
     * @brief Checks if the SkipList is empty.
     * @return True if the SkipList contains no elements, false otherwise.
     */
    bool empty() const;

    /**
     * @brief Inserts a new element into the SkipList.
     * @details If the value already exists, no insertion occurs.
     * @param value The value to insert.
     */
    void insert(const T& value);

    /**
     * @brief Checks if the SkipList contains a specific value.
     * @param value The value to search for.
     * @return True if the value is found, false otherwise.
     */
    bool contains(const T& value) const;

    /**
     * @brief Erases an element from the SkipList.
     * @param value The value to erase.
     * @return True if the element was found and erased, false otherwise.
     */
    bool erase(const T& value);

    // operators
    /**
     * @brief Equality comparison operator.
     * @param other The SkipList to compare with.
     * @return True if the SkipLists are equal, false otherwise.
     */
    bool operator==(const SkipList<T>& other) const;

    /**
     * @brief Inequality comparison operator.
     * @param other The SkipList to compare with.
     * @return True if the SkipLists are not equal, false otherwise.
     */
    bool operator!=(const SkipList<T>& other) const;

    /**
     * @brief Copy assignment operator.
     * @param other The SkipList to copy from.
     * @return A reference to this SkipList after assignment.
     */
    SkipList& operator=(const SkipList& other);

    /**
     * @brief Move assignment operator.
     * @param other The SkipList to move from (an rvalue reference).
     * @return A reference to this SkipList after assignment.
     */
    SkipList& operator=(SkipList&& other) noexcept;

    /**
     * @brief Less than comparison operator.
     * @param other The SkipList to compare with.
     * @return True if this SkipList is lexicographically less than the other, false otherwise.
     */
    bool operator<(const SkipList& other) const;

    /**
     * @brief Greater than comparison operator.
     * @param other The SkipList to compare with.
     * @return True if this SkipList is lexicographically greater than the other, false otherwise.
     */
    bool operator>(const SkipList& other) const;

    /**
     * @brief Less than or equal to comparison operator.
     * @param other The SkipList to compare with.
     * @return True if this SkipList is lexicographically less than or equal to the other, false otherwise.
     */
    bool operator<=(const SkipList& other) const;

    /**
     * @brief Greater than or equal to comparison operator.
     * @param other The SkipList to compare with.
     * @return True if this SkipList is lexicographically greater than or equal to the other, false otherwise.
     */
    bool operator>=(const SkipList& other) const;
};

template <typename T>
SkipList<T>::SkipList() : head(std::make_unique<Node<T>>(MAX_LEVEL)), current_level(0), num_elements(0) {
    std::random_device rd;
    rng.seed(rd());
    dis = std::uniform_real_distribution<>(0.0, 1.0);
}

template <typename T>
SkipList<T>::SkipList(const SkipList& other) : SkipList() {
    for (const T& value : other) {
        insert(value);
    }
}

template <typename T>
SkipList<T>::SkipList(SkipList&& other) noexcept :
    head(std::move(other.head)),
    current_level(other.current_level), num_elements(other.num_elements),
    rng(std::move(other.rng)),
    dis(std::move(other.dis)) {
    other.head = std::make_unique<Node<T>>(MAX_LEVEL);
    other.current_level = 0;
    other.num_elements = 0;
}


template <typename T>
std::size_t SkipList<T>::get_random_level() {
    std::size_t level = 1;
    while (dis(rng) < 0.25 && level < MAX_LEVEL) {
        ++level;
    }
    return level;
}

template <typename T>
std::size_t SkipList<T>::get_current_level() const {
    return current_level;
}

template <typename T>
std::size_t SkipList<T>::size() const {
    return num_elements;
}

template <typename T>
std::shared_ptr<Node<T>> SkipList<T>::get_first_node_at_0() const {
    return head->next[0];
}

template <typename T>
void SkipList<T>::insert(const T& value) {
    // Array for predecessors at every level which pointers we have to update
    std::vector<Node<T>*> update(MAX_LEVEL + 1, nullptr);

    // current MUST be raw pointer to avoid affect on logic of shared ptrs
    Node<T>* current = head.get();

    // Step 1 and 2
    for (std::size_t i = current_level + 1; i-- > 0;) {
        while (current->next[i] != nullptr && current->next[i]->getValue() < value) {
            current = current->next[i].get();
        }
        update[i] = current;
    }

    // checking for dublicates
    if (current->next[0] != nullptr && current->next[0]->getValue() == value) {
        return;
    }

    // Step 3
    // Generating random level for new node
    std::size_t new_node_level = get_random_level();

    // Check if new level is higher than max level
    if (new_node_level > current_level) {
        for (std::size_t i = current_level + 1; i <= new_node_level; ++i) {
            update[i] = head.get();
        }
        current_level = new_node_level;
    }

    // Step 4
    // Creating and inserting a node
    std::shared_ptr<Node<T>> new_node = std::make_shared<Node<T>>(value, new_node_level);

    for (std::size_t i = 0; i <= new_node_level; ++i) {
        new_node->next[i] = update[i]->next[i];
        update[i]->next[i] = new_node;
    }

    num_elements++;
}

template <typename T>
bool SkipList<T>::contains(const T& value) const {
    Node<T>* current = head.get();

    for (std::size_t level = current_level + 1; level-- > 0;) {
        while (current->next[level] != nullptr && current->next[level]->getValue() < value) {
            current = current->next[level].get();
        }
    }

    bool found = (current->next[0] != nullptr && current->next[0]->getValue() == value);

    return found;
}

template <typename T>
bool SkipList<T>::erase(const T& value) {
    // Logic is similar for insert() at the beginning
    std::vector<Node<T>*> update(MAX_LEVEL + 1);

    Node<T>* current = head.get();

    for (std::size_t i = current_level; i>= 1; --i) {
        while (current->next[i] != nullptr && current->next[i]->getValue() < value) {
            current = current->next[i].get();
        }
        update[i] = current;
    }

    while(current->next[0] != nullptr && current->next[0]->getValue() < value) {
        current = current->next[0].get();
    }
    update[0] = current;

    // Here we go other way
    std::shared_ptr<Node<T>> node_to_delete = current->next[0];

    if (node_to_delete != nullptr && node_to_delete->getValue() == value) {
        // Element is found. Now delete it and update pointers.
        for (std::size_t i = 0; i <= node_to_delete->level; ++i) {
            if (update[i]->next[i] == node_to_delete) {
                update[i]->next[i] = node_to_delete->next[i];
            }
        }

        num_elements--;

        // Update current level
        while (current_level > 0 && head->next[current_level] == nullptr) {
            current_level--;
        }
        return true;
    }

    return false;
}

template <typename T>
bool SkipList<T>::empty() const {
    return num_elements == 0;
}

// operators
template <typename T>
SkipList<T>& SkipList<T>::operator=(SkipList&& other) noexcept {
    if (this != &other) {
        head.reset();

        head = std::move(other.head);
        current_level = other.current_level;
        num_elements = other.num_elements;
        rng = std::move(other.rng);
        dis = std::move(other.dis);

        other.head = std::make_unique<Node<T>>(MAX_LEVEL);
        other.current_level = 0;
        other.num_elements = 0;
    }
    return *this;
}

template <typename T>
SkipList<T>& SkipList<T>::operator=(const SkipList& other) {
    if (this != &other) {
        SkipList temp(other);
        std::swap(head, temp.head);
        std::swap(current_level, temp.current_level);
        std::swap(num_elements, temp.num_elements);
    }
    return *this;
}

template <typename T>
bool SkipList<T>::operator==(const SkipList& other) const {
    if (num_elements != other.num_elements) {
        return false;
    }

    auto it1 = cbegin();
    auto it2 = other.cbegin();

    for (; it1 != cend() && it2 != other.cend(); ++it1, ++it2) {
        if (!(*it1 == *it2)) {
            return false;
        }
    }
    return true;
}

template <typename T>
bool SkipList<T>::operator<(const SkipList& other) const {
    auto it1 = cbegin();
    auto end1 = cend();
    auto it2 = other.cbegin();
    auto end2 = other.cend();

    for (; it1 != end1 && it2 != end2; ++it1, ++it2) {
        if (*it1 < *it2) {
            return true;
        }
        if (*it2 < *it1) {
            return false;
        }
    }

    return (it1 == end1 && it2 != end2);
}

template <typename T>
bool SkipList<T>::operator>(const SkipList& other) const {
    return other < *this;
}

template <typename T>
bool SkipList<T>::operator<=(const SkipList& other) const {
    return !(*this > other);
}

template <typename T>
bool SkipList<T>::operator>=(const SkipList& other) const {
    return !(*this < other);
}

#endif