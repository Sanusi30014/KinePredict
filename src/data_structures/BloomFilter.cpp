#include "kinepredict/data_structures/BloomFilter.h"
#include <cmath>
#include <algorithm>

namespace kinepredict {

    BloomFilter::BloomFilter(size_t expectedElements, double falsePositiveRate)
    : elementCount_(0) {

        // Calculate optimal bit array size
        bitArraySize_ = calculateBitArraySize(expectedElements, falsePositiveRate);

        // Calculate optimal number of hash functions
        numHashFunctions_ = calculateNumHashFunctions(bitArraySize_, expectedElements);

        // Initialize bit array
        bitArray_.resize(bitArraySize_, false);
    }

    void BloomFilter::add(const std::string& element) {
        uint64_t h1 = hash1(element);
        uint64_t h2 = hash2(element);

        // Set k bits using double hashing
        for (size_t i = 0; i < numHashFunctions_; ++i) {
            size_t index = nthHash(i, h1, h2) % bitArraySize_;
            bitArray_[index] = true;
        }

        elementCount_++;
    }

    bool BloomFilter::contains(const std::string& element) const {
        uint64_t h1 = hash1(element);
        uint64_t h2 = hash2(element);

        // Check if all k bits are set
        for (size_t i = 0; i < numHashFunctions_; ++i) {
            size_t index = nthHash(i, h1, h2) % bitArraySize_;
            if (!bitArray_[index]) {
                return false;  // Definitely not in set
            }
        }

        return true;  // Possibly in set
    }

    void BloomFilter::clear() {
        std::fill(bitArray_.begin(), bitArray_.end(), false);
        elementCount_ = 0;
    }

    double BloomFilter::getFalsePositiveRate() const {
        if (elementCount_ == 0) return 0.0;

        // Formula: (1 - e^(-kn/m))^k
        // k = numHashFunctions, n = elementCount, m = bitArraySize
        double exponent = -static_cast<double>(numHashFunctions_ * elementCount_) / bitArraySize_;
        double base = 1.0 - std::exp(exponent);
        return std::pow(base, numHashFunctions_);
    }

    size_t BloomFilter::getMemoryUsage() const {
        // Bit array size in bytes + overhead
        return (bitArraySize_ / 8) + sizeof(*this);
    }

    // Hash function 1: FNV-1a hash
    uint64_t BloomFilter::hash1(const std::string& element) const {
        uint64_t hash = 14695981039346656037ULL;  // FNV offset basis
        for (char c : element) {
            hash ^= static_cast<uint64_t>(c);
            hash *= 1099511628211ULL;  // FNV prime
        }
        return hash;
    }

    // Hash function 2: DJB2 hash
    uint64_t BloomFilter::hash2(const std::string& element) const {
        uint64_t hash = 5381;
        for (char c : element) {
            hash = ((hash << 5) + hash) + static_cast<uint64_t>(c);
        }
        return hash;
    }

    // Generate nth hash using double hashing
    uint64_t BloomFilter::nthHash(size_t n, uint64_t hash1, uint64_t hash2) const {
        return hash1 + n * hash2;
    }

    // Calculate optimal bit array size
    // Formula: m = -n * ln(p) / (ln(2)^2)
    size_t BloomFilter::calculateBitArraySize(size_t n, double p) {
        return static_cast<size_t>(
            -static_cast<double>(n) * std::log(p) / (std::log(2) * std::log(2))
        );
    }

    // Calculate optimal number of hash functions
    // Formula: k = (m/n) * ln(2)
    size_t BloomFilter::calculateNumHashFunctions(size_t m, size_t n) {
        if (n == 0) return 1;
        size_t k = static_cast<size_t>(
            (static_cast<double>(m) / n) * std::log(2)
        );
        return std::max(size_t(1), k);
    }

}