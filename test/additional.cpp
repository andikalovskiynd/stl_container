#include "../include/skip_list.h"

template <typename T>
const std::size_t SkipList<T>::MAX_LEVEL;

template const std::size_t SkipList<int>::MAX_LEVEL;
template const std::size_t SkipList<double>::MAX_LEVEL;
template const std::size_t SkipList<std::string>::MAX_LEVEL;
