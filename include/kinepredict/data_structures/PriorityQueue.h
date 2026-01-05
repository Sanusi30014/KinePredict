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
    void push(const T& element) {
        heap_.push_back(element);
        heapifyUp(heap_.size() - 1);
    }
    
    void push(T&& element) {
        heap_.push_back(std::move(element));
        heapifyUp(heap_.size() - 1);
    }
    
    /**
     * @brief Remove and return top element
     * @return Top element (min or max depending on comparator)
     */
    T pop() {
        if (empty()) {
            throw std::runtime_error("PriorityQueue::pop() called on empty queue");
        }
        
        T topElement = std::move(heap_[0]);
        heap_[0] = std::move(heap_.back());
        heap_.pop_back();
        
        if (!empty()) {
            heapifyDown(0);
        }
        
        return topElement;
    }
    
    /**
     * @brief View top element without removing
     * @return Reference to top element
     */
    const T& top() const {
        if (empty()) {
            throw std::runtime_error("PriorityQueue::top() called on empty queue");
        }
        return heap_[0];
    }
    
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
    
    void heapifyUp(size_t index) {
        while (index > 0) {
            size_t parentIdx = parent(index);
            
            // If current element has higher priority than parent, swap
            if (comp_(heap_[index], heap_[parentIdx])) {
                std::swap(heap_[index], heap_[parentIdx]);
                index = parentIdx;
            } else {
                break;
            }
        }
    }
    
    void heapifyDown(size_t index) {
        while (true) {
            size_t leftIdx = leftChild(index);
            size_t rightIdx = rightChild(index);
            size_t smallest = index;
            
            // Find smallest among current, left, and right
            if (leftIdx < heap_.size() && comp_(heap_[leftIdx], heap_[smallest])) {
                smallest = leftIdx;
            }
            
            if (rightIdx < heap_.size() && comp_(heap_[rightIdx], heap_[smallest])) {
                smallest = rightIdx;
            }
            
            // If smallest is not current, swap and continue
            if (smallest != index) {
                std::swap(heap_[index], heap_[smallest]);
                index = smallest;
            } else {
                break;
            }
        }
    }
    
    size_t parent(size_t i) const { return (i - 1) / 2; }
    size_t leftChild(size_t i) const { return 2 * i + 1; }
    size_t rightChild(size_t i) const { return 2 * i + 2; }
};

} // namespace kinepredict
