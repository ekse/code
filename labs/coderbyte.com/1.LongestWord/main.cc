#include <iostream>
#include <cctype>
#include <cstddef>
using std::string;
using std::cout;

string LongestWord(string sen) {
    string longest = "";
    int stringLen = 0;
    int stringStartPos = 0;
    for (int i = 0; i < sen.length(); i++) {
        if (isalpha(sen.at(i))) {
            stringLen += 1;
        } else {
            if (stringLen > longest.length()) {
                longest = sen.substr(stringStartPos, stringLen);
            }
            stringStartPos = i + 1;
            stringLen = 0;
        }
    }

    if (stringLen > longest.length()) {
        longest = sen.substr(stringStartPos, stringLen);
    }
    return longest;
}

int main() {
    // keep this function call here
    cout << LongestWord("hello world!");
    return 0;
}

