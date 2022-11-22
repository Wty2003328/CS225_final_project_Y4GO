#include <cstddef>
#include <cmath>
#include "heap_dijkstra.h"

template <class T, class Compare>
class heap;

template <class T, class Compare>
size_t heap<T, Compare>::root() const
{
    return 0;
}

template <class T, class Compare>
size_t heap<T, Compare>::leftChild(size_t currentIdx) const
{
    return currentIdx*2 + 1;
}

template <class T, class Compare>
size_t heap<T, Compare>::rightChild(size_t currentIdx) const
{
    return currentIdx*2 + 2;
}

template <class T, class Compare>
size_t heap<T, Compare>::parent(size_t currentIdx) const
{
    return std::floor((currentIdx-1)/2);
}

template <class T, class Compare>
bool heap<T, Compare>::hasAChild(size_t currentIdx) const
{
    if(_elems.size() > leftChild(currentIdx)) {
        return true;
    } else {
        return false;
    }
}

template <class T, class Compare>
size_t heap<T, Compare>::maxPriorityChild(size_t currentIdx) const
{
    if(_elems.size()-1 <= leftChild(currentIdx)) {
        return leftChild(currentIdx);
    } else if(_elems[leftChild(currentIdx)] > _elems[rightChild(currentIdx)]) {
        return leftChild(currentIdx);
    } else {
        return rightChild(currentIdx);
    }
    //return 0;
}

template <class T, class Compare>
void heap<T, Compare>::heapifyDown(size_t currentIdx)
{
   if(hasAChild(currentIdx)) {
    int min = maxPriorityChild(currentIdx);
    if(higherPriority(_elems[min], _elems[currentIdx])) {
        std::swap(_elems[currentIdx], _elems[min]);
        heapifyDown(min);
    }
   }
}

template <class T, class Compare>
void heap<T, Compare>::heapifyUp(size_t currentIdx)
{
    if (currentIdx == root())
        return;
    size_t parentIdx = parent(currentIdx);
    if (higherPriority(_elems[currentIdx], _elems[parentIdx])) {
        std::swap(_elems[currentIdx], _elems[parentIdx]);
        heapifyUp(parentIdx);
    }
}

template <class T, class Compare>
heap<T, Compare>::heap()
{

}

template <class T, class Compare>
heap<T, Compare>::heap(const std::vector<T>& elems) 
{
    for(size_t i = 0; i < elems.size(); i++) {
        _elems.push_back(elems[i]);
    }
    for(unsigned i = 0; i <=parent(_elems.size() - 1);i++) {
        heapifyDown(parent(_elems.size() - 1) -i);
    }
}

template <class T, class Compare>
T heap<T, Compare>::pop()
{
    T output = _elems[0];
    _elems[0] = _elems[_elems.size() -1];
    _elems.pop_back();
    heapifyDown(0);
    return output;
}

template <class T, class Compare>
T heap<T, Compare>::peek() const
{
    return _elems[0];
}

template <class T, class Compare>
void heap<T, Compare>::push(const T& elem)
{
    _elems.push_back(elem);
    heapifyUp(_elems.size() -1);
}

template <class T, class Compare>
void heap<T, Compare>::updateElem(const size_t & idx, const T& elem)
{
    _elems[idx] = elem;
    for(unsigned i = 0; i <= parent(_elems.size()-1);i++) {
        heapifyDown(parent(_elems.size()-1) -i);
    }
}


template <class T, class Compare>
bool heap<T, Compare>::empty() const
{
    if(_elems.size() == 0) {
        return true;
    }
    return false;
}

template <class T, class Compare>
void heap<T, Compare>::getElems(std::vector<T> & heaped) const
{
    for (size_t i = root(); i < _elems.size(); i++) {
        heaped.push_back(_elems[i]);
    }
}
