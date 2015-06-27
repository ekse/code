#include <iostream>
#include <string>
#include <cctype>
#include "bob.h"

using namespace std;

namespace bob {

string hey(string const& text) {
    char last_char = ' ';  // this variable ignores whitespace characters
    bool is_yelled_at = true;
    bool at_least_one_letter = false;

    for (char c : text) {
        if (!isspace(c) && !isblank(c)) {
            last_char = c;
        }

        if (isalpha(c)) {
            at_least_one_letter = true;
            
            if (!isupper(c)) {
                is_yelled_at = false;
            }
        }
    }
 
    if (at_least_one_letter && is_yelled_at) {
        return string("Whoa, chill out!");
    }

    if (last_char == '?') {
        return ("Sure.");
    }

    if (last_char == ' ') {
        return ("Fine. Be that way!");
    }

    return string("Whatever.");
}
}

