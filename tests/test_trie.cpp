#include "kinepredict/data_structures/Trie.h"
#include <iostream>
#include <cassert>

using namespace kinepredict;

void testTrieBasic() {
    Trie trie;
    
    // Test insert and search
    trie.insert("hello");
    trie.insert("world");
    trie.insert("help");
    
    assert(trie.search("hello") == true);
    assert(trie.search("world") == true);
    assert(trie.search("help") == true);
    assert(trie.search("hell") == false);
    assert(trie.search("helicopter") == false);
    
    std::cout << "✓ Basic Trie insert/search test passed" << std::endl;
}

void testTriePrefix() {
    Trie trie;
    
    trie.insert("app");
    trie.insert("apple");
    trie.insert("application");
    
    assert(trie.startsWith("app") == true);
    assert(trie.startsWith("appl") == true);
    assert(trie.startsWith("banana") == false);
    
    std::cout << "✓ Trie prefix test passed" << std::endl;
}

void testTrieAutoComplete() {
    Trie trie;
    
    trie.insert("cat");
    trie.insert("car");
    trie.insert("card");
    trie.insert("dog");
    
    auto words = trie.getWordsWithPrefix("ca");
    assert(words.size() == 3);
    
    std::cout << "✓ Trie autocomplete test passed" << std::endl;
}

void testTrieSize() {
    Trie trie;
    
    assert(trie.size() == 0);
    trie.insert("test");
    assert(trie.size() == 1);
    trie.insert("test");  // Duplicate
    assert(trie.size() == 1);
    trie.insert("testing");
    assert(trie.size() == 2);
    
    std::cout << "✓ Trie size test passed" << std::endl;
}

int main() {
    std::cout << "Running Trie tests..." << std::endl;
    
    testTrieBasic();
    testTriePrefix();
    testTrieAutoComplete();
    testTrieSize();
    
    std::cout << "\n✅ All Trie tests passed!" << std::endl;
    return 0;
}
