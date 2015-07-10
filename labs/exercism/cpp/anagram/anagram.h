#include <vector>
#include <string>

using namespace std;


class anagram {
   public:
    anagram(const string word);
    vector<string> matches(const vector<string>& words);
   private:
    string word_;
    string word_lowercase_;
    string word_lowercase_sorted_;

};
