#include "kinepredict/data_structures/PriorityQueue.h"
#include <iostream>
#include <cassert>

using namespace kinepredict;

void testPriorityQueueMinHeap() {
    PriorityQueue<int> pq;
    
    pq.push(5);
    pq.push(2);
    pq.push(8);
    pq.push(1);
    pq.push(9);
    
    assert(pq.size() == 5);
    assert(pq.top() == 1);
    
    assert(pq.pop() == 1);
    assert(pq.pop() == 2);
    assert(pq.pop() == 5);
    assert(pq.pop() == 8);
    assert(pq.pop() == 9);
    
    assert(pq.empty() == true);
    
    std::cout << "✓ Min-Heap Priority Queue test passed" << std::endl;
}

void testPriorityQueueMaxHeap() {
    PriorityQueue<int, std::greater<int>> pq;
    
    pq.push(5);
    pq.push(2);
    pq.push(8);
    pq.push(1);
    
    assert(pq.top() == 8);
    assert(pq.pop() == 8);
    assert(pq.pop() == 5);
    assert(pq.pop() == 2);
    assert(pq.pop() == 1);
    
    std::cout << "✓ Max-Heap Priority Queue test passed" << std::endl;
}

struct Prediction {
    std::string headline;
    double score;
    
    bool operator<(const Prediction& other) const {
        return score < other.score;
    }
    
    bool operator>(const Prediction& other) const {
        return score > other.score;
    }
};

void testPriorityQueueCustomType() {
    PriorityQueue<Prediction, std::greater<Prediction>> pq;
    
    pq.push({"Headline A", 0.85});
    pq.push({"Headline B", 0.92});
    pq.push({"Headline C", 0.78});
    
    auto best = pq.pop();
    assert(best.score == 0.92);
    
    std::cout << "✓ Custom type Priority Queue test passed" << std::endl;
}

int main() {
    std::cout << "Running Priority Queue tests..." << std::endl;
    
    testPriorityQueueMinHeap();
    testPriorityQueueMaxHeap();
    testPriorityQueueCustomType();
    
    std::cout << "\n✅ All Priority Queue tests passed!" << std::endl;
    return 0;
}
