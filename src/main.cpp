#include <iostream>
#include "kinepredict/data_structures/Trie.h"
#include "kinepredict/data_structures/BloomFilter.h"
#include "kinepredict/data_structures/PriorityQueue.h"

using namespace kinepredict;

int main() {
    std::cout << "========================================" << std::endl;
    std::cout << "  KinePredict v1.0.0 - Day 3 Demo" << std::endl;
    std::cout << "========================================\n" << std::endl;
    
    // Demo Trie
    std::cout << "📊 Trie Demo:" << std::endl;
    Trie trie;
    trie.insert("marketing");
    trie.insert("market");
    trie.insert("markets");
    trie.insert("content");
    
    std::cout << "  Inserted: marketing, market, markets, content" << std::endl;
    std::cout << "  Search 'marketing': " << (trie.search("marketing") ? "✓ Found" : "✗ Not found") << std::endl;
    std::cout << "  Starts with 'mark': " << (trie.startsWith("mark") ? "✓ Yes" : "✗ No") << std::endl;
    std::cout << "  Words with prefix 'mark': ";
    auto words = trie.getWordsWithPrefix("mark");
    for (const auto& w : words) std::cout << w << " ";
    std::cout << "\n" << std::endl;
    
    // Demo Bloom Filter
    std::cout << "🌸 Bloom Filter Demo:" << std::endl;
    BloomFilter bloom(1000, 0.01);
    bloom.add("headline1");
    bloom.add("headline2");
    bloom.add("headline3");
    
    std::cout << "  Added 3 headlines" << std::endl;
    std::cout << "  Contains 'headline1': " << (bloom.contains("headline1") ? "✓ Probably" : "✗ No") << std::endl;
    std::cout << "  Contains 'headline99': " << (bloom.contains("headline99") ? "Probably" : "✗ Definitely not") << std::endl;
    std::cout << "  Memory usage: " << bloom.getMemoryUsage() << " bytes\n" << std::endl;
    
    // Demo Priority Queue
    std::cout << "🏆 Priority Queue Demo (Content Ranking):" << std::endl;
    struct ContentScore {
        std::string content;
        double score;
        bool operator<(const ContentScore& other) const { return score < other.score; }
        bool operator>(const ContentScore& other) const { return score > other.score; }
    };
    
    PriorityQueue<ContentScore, std::greater<ContentScore>> rankings;
    rankings.push({"Buy Now - 50% Off!", 0.85});
    rankings.push({"Limited Time Offer", 0.92});
    rankings.push({"Check This Out", 0.67});
    
    std::cout << "  Ranked by predicted CTR:" << std::endl;
    int rank = 1;
    while (!rankings.empty()) {
        auto top = rankings.pop();
        std::cout << "    " << rank++ << ". \"" << top.content 
                  << "\" (score: " << top.score << ")" << std::endl;
    }
    
    std::cout << "\n========================================" << std::endl;
    std::cout << "✅ All data structures working!" << std::endl;
    std::cout << "========================================" << std::endl;
    
    return 0;
}
