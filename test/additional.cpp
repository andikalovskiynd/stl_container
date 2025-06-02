/**
 * @file additional.cpp 
 * @brief File with additional definitions for MAX_LEVEL for different data types.
*/

#include "../include/skip_list.h"

template <typename T>
const std::size_t SkipList<T>::MAX_LEVEL;

/**
 * @brief Initialization for MAX_LEVEL for int. 
*/
template const std::size_t SkipList<int>::MAX_LEVEL;

/**
 * @brief Initialization for MAX_LEVEL for double. 
*/
template const std::size_t SkipList<double>::MAX_LEVEL;

/**
 * @brief Initialization for MAX_LEVEL for string. 
*/
template const std::size_t SkipList<std::string>::MAX_LEVEL;
