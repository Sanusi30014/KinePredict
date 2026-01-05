#include "kinepredict/data_structures/Trie.h"

namespace kinepredict {

    Trie::Trie() : root_(std::make_unique<TrieNode>()), wordCount_(0) {

    }

    Trie::~Trie() = default;

    void Trie::insert(const std::string& word) {
        // Your algorithm here
        // Hint: loop through characters, navigate/create nodes

        if (word.empty()) return;

        TrieNode* current = root_.get();

        for (char c : word) {
            if (current->children.find(c) == current->children.end()) {
                current->children[c] = std::make_unique<TrieNode>();
            }
            current = current->children[c].get();
        }

        if (!current->isEndOfWord) {
            current->isEndOfWord = true;
            ++wordCount_;
        }
    }

    bool Trie::search(const std::string& word) const {
        // Your algorithm here
        // Hint: similar to insert, but just check, don't create
        if (word.empty()) return false;

        const TrieNode* current = root_.get();

        for (char c : word) {
            auto it = current->children.find(c);
            if (it == current->children.end()) {
                return false;  // Character not found
            }
            current = it->second.get();
        }

        return current->isEndOfWord;
    }


    bool Trie::startsWith(const std::string& prefix) const {
        if (prefix.empty()) return true;

        const TrieNode* current = root_.get();

        for (char c : prefix) {
            auto it = current->children.find(c);
            if (it == current->children.end()) {
                return false;
            }
            current = it->second.get();
        }

        return true;  // All characters in prefix found
    }

    std::vector<std::string> Trie::getWordsWithPrefix(const std::string& prefix) const {
        std::vector<std::string> results;

        // Navigate to the prefix node
        const TrieNode* current = root_.get();
        for (char ch : prefix) {
            auto it = current->children.find(ch);
            if (it == current->children.end()) {
                return results;  // Prefix not found, return empty
            }
            current = it->second.get();
        }

        // Collect all words starting from this node
        collectWords(current, prefix, results);

        return results;
    }

    void Trie::collectWords(const TrieNode* node, const std::string& prefix,
                        std::vector<std::string>& results) const {
        if (!node) return;

        if (node->isEndOfWord) {
            results.push_back(prefix);
        }

        // Recursively explore all children
        for (const auto& [ch, childNode] : node->children) {
            collectWords(childNode.get(), prefix + ch, results);
        }
    }

    void Trie::clear() {
        root_ = std::make_unique<TrieNode>();
        wordCount_ = 0;
    }

    size_t Trie::size() const {
        return wordCount_;
    }



}