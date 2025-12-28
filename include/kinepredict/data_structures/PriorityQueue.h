#pragma once

#include <vector>
#include <functional>
#include <stdexcept>

namespace kinepredict {

/**
 * @brief Generic Priority Queue (Min-Heap by default)
 * 
 * Used for:
 * - Ranking content by predicted performance
 * - K-best predictions
 * - Top-N recommendations
 * 
 * Time Complexity:
 * - Insert: O(log n)
 * - ExtractMin/Max: O(log n)
 * - Peek: O(1)
 */
template<typename T, typename Compare = std::less<T>>
class PriorityQueue {
public:
    PriorityQueue() = default;
    
    /**
     * @brief Insert element into queue
     * @param element The element to insert
     */
    void push(const T& element);
    void push(T&& element);
    
    /**
     * @brief Remove and return top element
     * @return Top element (min or max depending on comparator)
     */
    T pop();
    
    /**
     * @brief View top element without removing
     * @return Reference to top element
     */
    const T& top() const;
    
    /**
     * @brief Check if queue is empty
     * @return true if empty
     */
    bool empty() const { return heap_.empty(); }
    
    /**
     * @brief Get number of elements
     * @return Size of queue
     */
    size_t size() const { return heap_.size(); }
    
    /**
     * @brief Remove all elements
     */
    void clear() { heap_.clear(); }

private:
    std::vector<T> heap_;
    Compare comp_;
    
    void heapifyUp(size_t index);
    void heapifyDown(size_t index);
    size_t parent(size_t i) const { return (i - 1) / 2; }
    size_t leftChild(size_t i) const { return 2 * i + 1; }
    size_t rightChild(size_t i) const { return 2 * i + 2; }
};

} // namespace kinepredict
