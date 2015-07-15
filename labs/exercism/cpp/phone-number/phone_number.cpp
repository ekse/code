#include <algorithm>
#include <cstring>
#include <string>
#include <iterator>

#include "phone_number.h"

using namespace std;

phone_number::phone_number(const string number) {
    const string BAD_NUMBER = string("0000000000");

    for (auto c : number) {
        if (isdigit(c)) {
            number_.push_back(c);
        }
    }

    if (number_.length() < 10) {
        number_ = BAD_NUMBER;
        return;
    }

    // strip 1 at the beginning when international calling code
    // eg. 1-555-666-7777
    if (number_.length() == 11) {
        if (number_.at(0) == '1') {
            number_.erase(0, 1);
        } else {
            number_ = BAD_NUMBER;
        }
    }
}

phone_number::operator string() const {
    return (boost::str(boost::format("( %1%) %2%-%3% ") % area_code() %
                       number_.substr(3, 3) % number_.substr(6, 9)));
}

string phone_number::number() const { return (number_); }

string phone_number::area_code() const { return (number_.substr(0, 3)); }

