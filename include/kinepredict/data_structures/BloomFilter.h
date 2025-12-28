#pragma once

#include <vector>
#include <string>
#include <cstdint>
#include <functional>

namespace kinepredict {

/**
 * @brief Bloom Filter for fast duplicate detection with space efficiency
 * 
 * Used for:
 * - Detecting duplicate marketing content
 * - Fast membership testing
 * - Reducing unnecessary processing
 * 
 * Trade-off: Space efficient but allows false positives (no false negatives)
 * 
 * Time Complexity: O(k) where k is number of hash functions
 * Space Complexity: O(m) where m is bit array size
 */
class BloomFilter {
public:
    /**
     * @brief Construct Bloom Filter
     * @param expectedElements Expected number of elements
     * @param falsePositiveRate Desired false positive rate (0.0 to 1.0)
     */
    BloomFilter(size_t expectedElements, double falsePositiveRate = 0.01);
    
    /**
     * @brief Add element to filter
     * @param element The string to add
     */
    void add(const std::string& element);
    
    /**
     * @brief Check if element might be in set
     * @param element The string to check
     * @return true if possibly in set, false if definitely not
     */
    bool contains(const std::string& element) const;
    
    /**
     * @brief Clear all data
     */
    void clear();
    
    /**
     * @brief Get false positive probability
     * @return Current estimated false positive rate
     */
    double getFalsePositiveRate() const;
    
    /**
     * @brief Get memory usage in bytes
     * @return Memory consumption
     */
    size_t getMemoryUsage() const;

private:
    std::vector<bool> bitArray_;
    size_t numHashFunctions_;
    size_t bitArraySize_;
    size_t elementCount_;
    
    // Hash functions
    uint64_t hash1(const std::string& element) const;
    uint64_t hash2(const std::string& element) const;
    uint64_t nthHash(size_t n, uint64_t hash1, uint64_t hash2) const;
    
    // Calculate optimal parameters
    static size_t calculateBitArraySize(size_t n, double p);
    static size_t calculateNumHashFunctions(size_t m, size_t n);
};

} // namespace kinepredict
