#include "kinepredict/data_structures/BloomFilter.h"
#include <iostream>
#include <cassert>

using namespace kinepredict;

void testBloomFilterBasic() {
    BloomFilter bloom(100, 0.01);
    
    bloom.add("marketing");
    bloom.add("content");
    bloom.add("prediction");
    
    assert(bloom.contains("marketing") == true);
    assert(bloom.contains("content") == true);
    assert(bloom.contains("prediction") == true);
    assert(bloom.contains("nonexistent") == false);
    
    std::cout << "✓ Basic Bloom Filter test passed" << std::endl;
}

void testBloomFilterFalsePositive() {
    BloomFilter bloom(1000, 0.01);
    
    // Add many elements
    for (int i = 0; i < 100; i++) {
        bloom.add("item" + std::to_string(i));
    }
    
    // Check false positive rate
    int falsePositives = 0;
    int testCases = 1000;
    
    for (int i = 100; i < 100 + testCases; i++) {
        if (bloom.contains("item" + std::to_string(i))) {
            falsePositives++;
        }
    }
    
    double actualRate = static_cast<double>(falsePositives) / testCases;
    std::cout << "  False positive rate: " << actualRate << std::endl;
    
    // Should be around 1% or less
    assert(actualRate < 0.05);
    
    std::cout << "✓ Bloom Filter false positive test passed" << std::endl;
}

int main() {
    std::cout << "Running Bloom Filter tests..." << std::endl;
    
    testBloomFilterBasic();
    testBloomFilterFalsePositive();
    
    std::cout << "\n✅ All Bloom Filter tests passed!" << std::endl;
    return 0;
}
