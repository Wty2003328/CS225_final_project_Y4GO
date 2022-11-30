#pragma once
#include <iostream>
#include <vector>


template <class Type, class Comp>
class HeapNodeDescriptor;


template <class T, class Compare = std::less<T>>
class heap
{
  public:
    
    heap();

   
    heap(const std::vector<T>& elems);

    T pop();

    
    T peek() const;

    
    void push(const T& elem);

    
    void updateElem(const size_t & idx, const T& elem);

    bool empty() const;

    
    void getElems(std::vector<T> & heaped) const;

    
    size_t root() const;

    template <class Type, class Comp>
    friend std::ostream& operator<<(std::ostream& out,
                                    const heap<Type, Comp>& toPrint);

    friend class HeapNodeDescriptor<T, Compare>;

  private:
    
    std::vector<T> _elems;

   
    Compare higherPriority;

   
    size_t leftChild(size_t currentIdx) const;

   
    size_t rightChild(size_t currentIdx) const;

    size_t parent(size_t currentIdx) const;

    
    bool hasAChild(size_t currentIdx) const;

    
    size_t maxPriorityChild(size_t currentIdx) const;

    
    void heapifyDown(size_t currentIdx);

   
    void heapifyUp(size_t currentIdx);
};