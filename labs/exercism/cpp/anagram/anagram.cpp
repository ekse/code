#include <algorithm>
#include <vector>
#include <string>
#include <boost/algorithm/string.hpp>

#include "anagram.h"

using namespace std;

anagram::anagram(string word)
    : word_(word), word_lowercase_(boost::algorithm::to_lower_copy(word)) {
    word_lowercase_sorted_ = word_lowercase_;
    sort(word_lowercase_sorted_.begin(), word_lowercase_sorted_.end());
}

vector<string> anagram::matches(const vector<string>& words) {
    vector<string> result;

    for (auto word : words) {
        // words of different length can't be anagrams
        if (word.length() != word_.length()) {
            continue;
        }

        auto word_lowercase = boost::algorithm::to_lower_copy(word);

        // a word is not an anagram of itself
        if (word_lowercase.compare(word_lowercase_) == 0) {
            continue;
        }

        // compare words in lowercase and alphabetical order
        auto word_lowercase_sorted = word_lowercase;
        sort(word_lowercase_sorted.begin(), word_lowercase_sorted.end());

        if (word_lowercase_sorted.compare(word_lowercase_sorted_) == 0) {
            result.push_back(word);
        }
    }

    return result;
}
