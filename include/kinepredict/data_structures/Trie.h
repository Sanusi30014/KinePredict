#pragma once

#include <string>
#include <memory>
#include <vector>
#include <unordered_map>

namespace kinepredict {

/**
 * @brief Trie (Prefix Tree) for efficient keyword matching and autocomplete
 * 
 * Used for:
 * - Fast keyword lookup in marketing content
 * - SEO keyword matching
 * - Pattern detection
 * 
 * Time Complexity:
 * - Insert: O(m) where m is key length
 * - Search: O(m)
 * - StartsWith: O(m)
 */
class Trie {
public:
    Trie();
    ~Trie();
    
    /**
     * @brief Insert a word into the trie
     * @param word The word to insert
     */
    void insert(const std::string& word);
    
    /**
     * @brief Search for exact word match
     * @param word The word to search for
     * @return true if word exists, false otherwise
     */
    bool search(const std::string& word) const;
    
    /**
     * @brief Check if any word starts with given prefix
     * @param prefix The prefix to check
     * @return true if prefix exists, false otherwise
     */
    bool startsWith(const std::string& prefix) const;
    
    /**
     * @brief Get all words with given prefix (autocomplete)
     * @param prefix The prefix
     * @return Vector of words matching prefix
     */
    std::vector<std::string> getWordsWithPrefix(const std::string& prefix) const;
    
    /**
     * @brief Clear all data from trie
     */
    void clear();
    
    /**
     * @brief Get number of words in trie
     * @return Word count
     */
    size_t size() const;

private:
    struct TrieNode {
        std::unordered_map<char, std::unique_ptr<TrieNode>> children;
        bool isEndOfWord;
        
        TrieNode() : isEndOfWord(false) {}
    };
    
    std::unique_ptr<TrieNode> root_;
    size_t wordCount_;
    
    // Helper for getWordsWithPrefix
    void collectWords(const TrieNode* node, const std::string& prefix, 
                      std::vector<std::string>& results) const;
};

} // namespace kinepredict
