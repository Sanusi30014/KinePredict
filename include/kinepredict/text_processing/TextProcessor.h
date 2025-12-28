#pragma once

#include <string>
#include <vector>
#include <string_view>

namespace kinepredict {

/**
 * @brief Text processing utilities for marketing content analysis
 */
class TextProcessor {
public:
    /**
     * @brief Tokenize text into words
     * @param text Input text
     * @return Vector of tokens
     */
    static std::vector<std::string> tokenize(std::string_view text);
    
    /**
     * @brief Convert text to lowercase
     * @param text Input text
     * @return Lowercase version
     */
    static std::string toLowerCase(std::string_view text);
    
    /**
     * @brief Remove punctuation from text
     * @param text Input text
     * @return Text without punctuation
     */
    static std::string removePunctuation(std::string_view text);
    
    /**
     * @brief Extract n-grams from tokens
     * @param tokens Input tokens
     * @param n N-gram size (1=unigram, 2=bigram, etc.)
     * @return Vector of n-grams
     */
    static std::vector<std::string> extractNGrams(
        const std::vector<std::string>& tokens, size_t n);
    
    /**
     * @brief Calculate word count
     * @param text Input text
     * @return Number of words
     */
    static size_t wordCount(std::string_view text);
    
    /**
     * @brief Calculate character count (excluding spaces)
     * @param text Input text
     * @return Number of characters
     */
    static size_t charCount(std::string_view text);
};

} // namespace kinepredict
